#pragma once

#ifndef __REQUIRE_HPP__
#define __REQUIRE_HPP__

#include <fstream>
#include <functional>
#include <algorithm>
#include <sstream>
#include <deque>

class Require
{
	public:
		explicit Require(const bool &minificate = false) : minificate(minificate) {};
		std::string load(std::string &file, const std::string &path);

		static char delimiter;

	private:
		Require(const Require&);
		const Require& operator=(const Require&);

		template <typename T> struct find_equal;

		template <typename T>
		void split (const std::string &value, const char &token, T result);

		template <typename T>
		std::string erase(std::string &value, const T &token);

		inline std::string read(std::ifstream &file) const;
		inline std::string minify(std::string &file);
		bool clean(std::string &file, std::deque<std::string> &names);
		const bool minificate;
};

// Delimiter for file names
char Require::delimiter = ';';

/*
The find_equal<T>() provides a logical predicate to compare the specified values

@param {const &T} value - equal value
@use: find_equal<char>(' ');
@return {bool}
*/
template <typename T>
struct Require::find_equal : std::binary_function <T, T, bool>
{
	find_equal(const T &value) : value(value) {};

	bool operator()(const T &left, const T &right) const {
		return left == value && right == value;
	}

	private:
		T value;
};

/*
The split<T>() is used to split a string into an array of substrings

@param {const std::string &} value - The string to be split
@param {const char &} token - Specifies the character to use for splitting the string
@param {T} result - Generic form of iterator like std::back_inserter
@return {void}
*/
template <typename T>
void Require::split (const std::string &value, const char &token, T result)
{
	register std::string::size_type start = 0, end = 0;

	while ((end = value.find(token, start)) != std::string::npos) {
		*result++ = value.substr(start, end - start);
		start = end + 1;
	}

	*result++ = value.substr(start);
}

/*
The erase<T>() is used to specified characters from a string

@param {std::string &} value - The string to be erase
@param {const T &} token - Specifies the character to use for erase the string
@return {std::string} - As a result, the original string is modified
*/
template <typename T>
std::string Require::erase(std::string &value, const T &token)
{
	register std::string::size_type i = 0;

	while((i = value.find_first_of(token, i)) != std::string::npos)
		value.erase(i, 1);

	return value;
}

/*
The Require::read() method is used to get a file stream as a string

@param {std::ifstream &} file - input file stream
@see {Require::load}
@return {std::string}
*/
std::string Require::read(std::ifstream &file) const
{
	typedef std::istreambuf_iterator<char> file_iterator;
	std::string stream((file_iterator(file)), file_iterator());

	return stream;
}

/*
The Require::minify() method provides a minification for file content

@param {std::string &} file - input file stream
@see {Require::load}
@return {std::string}
*/
std::string Require::minify(std::string &file)
{
	if (!this->minificate)
		return file;

	// Erase line feeds (LF, CR, HT)
	this->erase(file, "\n\t\r");

	// Erase spaces (leaving only single spaces)
	file.erase(std::unique(file.begin(), file.end(), find_equal<char>(' ')), file.end());

	return file;
}

/*
The Require::clean method is used to clean up the tokens in the file names

@param {std::string &} file - file stream
@see {Require::load}
@return {bool}
*/
bool Require::clean(std::string &file, std::deque<std::string> &name)
{
	// Erase line feeds (LF, CR, HT) and spaces
	this->erase(file, "\n\t\r ");

	std::string::size_type size = file.size() - 1;

	// Remove the last <;> character
	if (file.at(size) == this->delimiter)
		file.erase(size);

	// Remove the first <;> character
	if (file.at(0) == this->delimiter)
		file.erase(0, 1);

	// Split the names
	this->split(file, this->delimiter, std::back_inserter(name));

	return name.empty();
}

/*
The Require::load method is used to obtain the result

@param {std::string &} file - A string with comma-separated values.
This param is used to get real file names and file paths.

For example: 'file1.js;file2.js'
Also you can use semicolon at the beginning and end of file:

For example: ';file1.js;file2.js;'

@param {std::string &} file - A string with comma-separated values.
@return {const std::string &} path - Is a optional param.
You can specify a common path to the files.
*/
std::string Require::load(std::string &file, const std::string &path = "")
{
	std::deque<std::string> name;

	if (file.empty() || this->clean(file, name))
		return "";

	std::deque<std::string>::const_iterator i = name.begin();

	std::string stream;
	std::ifstream infile;

	while (i != name.end())
	{
		infile.open((path + *i).c_str(), std::ios::binary);

		if(infile.is_open())
			stream.append(this->read(infile) + "\n");

		infile.close();

		i++;
	}

	return this->minify(stream);
}

#endif
