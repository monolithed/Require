/*
* <Require> is a cross-platform file loader module.
* The main objective of this module is to concatenate multiple files into one.
* Using a modular file loader you will improve the speed and quality of your code.
* Also the <Require> provides a minification for file content.
*
* NOTE: The code tested with GCC 4.2.1
*
* @author: Alexander Guinness
* @version: 1.2
* @license: MIT
* @date: 7/20/12 9:28 PM
*/

#pragma once

#ifndef __REQUIRE_HPP__
#define __REQUIRE_HPP__

#include <fstream>
#include <string>
#include <functional>
#include <algorithm>
#include <iterator>

class Require
{
	public:
		Require() {};
		~Require() {};

	private:
		Require(const Require&);
		const Require& operator=(const Require&);

		/*
		The find_equal<T>() provides a logical predicate to compare the specified values

		@param {const &T} value - equal value
		@use: find_equal<char>(' ');
		@return {bool}
		*/
		template <typename T>
		struct find_equal : std::binary_function <T, T, bool>
		{
			find_equal(const T &value) : value(value) {};

			bool operator()(const T &left, const T &right) const {
				return left == value && right == value;
			}

			private:
				T value;
		};

		/*
		The erase<T>() is used to specified characters from a string

		@param {std::string &} value - The string to be erase
		@param {const T &} token - Specifies the character to use for erase the string
		@return {std::string} - As a result, the original string is modified
		*/
		template <typename T>
		std::string erase (std::string &value, const T &token)
		{
			std::string::size_type i = 0;

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
		std::string read (std::ifstream &file) const
		{
			typedef std::istreambuf_iterator<char> file_iterator;
			std::string stream((file_iterator(file)), file_iterator());

			return stream;
		}

		std::string minify (const bool &minificate);

	public:
		/*
		The Require::load method is used to obtain the result

		@param {const T &} file - An array of strings with file names
		@param {std::string &} path - Optional param to specify a common path to the files.
		@return {bool}
		*/
		template <typename T>
		bool load (const T &file, const std::string &path = "")
		{
			if (file.empty())
				return false;

			std::ifstream infile;

			typename T::const_iterator i = file.begin();

			while (i != file.end())
			{
				infile.open((path + *i).c_str(), std::ios::binary);

				if(infile.is_open())
					this->stream.append(this->read(infile) + "\n");

				infile.close();

				i++;
			}
	 		return infile.good();
		}

		/*
		The split<T>() is used to split a string into an array of substrings

		@param {const std::string &} value
		@param {const char &} token - Specifies the character to use for splitting the string
		@param {T} result - Generic form of iterator like std::back_inserter
		@return {void}
		*/
		template <typename T>
		void split (std::string value, const char &token, T result)
		{
			// Erase line feeds (LF, CR, HT) and spaces
			this->erase(value, "\n\t\r ");

			std::string::size_type size = value.size() - 1, start = 0, end = 0;

			// Remove the last <delimiter> character
			if (value.at(size) == token)
				value.erase(size);

			// Remove the first <delimiter> character
			if (value.at(0) == token)
				value.erase(0, 1);

			while ((end = value.find(token, start)) != std::string::npos) {
				*result++ = value.substr(start, end - start);
				start = end + 1;
			}

			*result++ = value.substr(start);
		}

		/*
		The Require::data() method is used to get data

		@param {const bool &minificate &} minificate - Minification for file content
		@return {std::string}
		*/
		std::string data (const bool &minificate = false)
		{
			return this->minify(minificate);
		}

		/*
		The Require::save() method provides data saving into a file

		@param name - File path (/files/file.js)
		@param {const std::ios_base::openmode} mode - Bitmask type T3 that describes an object that can store the opening mode.
		@return {bool} - Completion status
		*/
		bool save (const std::string &name, const std::ios_base::openmode &mode = std::ios::binary)
		{
			std::ofstream file(name.c_str(), mode);
			file << this->stream;
			file.close();

			return file.good();
		}

		std::string stream;
};

/*
The Require::minify() method provides a minification for file content

@param {const bool &minificate}
@see {Require::data}
@return {std::string}
*/
std::string Require::minify (const bool &minificate)
{
	if (!minificate)
		return this->stream;

	std::string::const_iterator i = this->stream.begin(), quote;
	std::string result;

	// Remove comments
	while (i != this->stream.end())
	{
		//	/ RegExp / : Literal regular expression
		//	/* */      : Multi-line block comment
		//	/*@...@*/  : Conditional compilation comment
		//	\          : Escape sequences
		//	//         : Sigle-line comment
		//	''         : Single-quote delimited string
		//	""         : Double-quote delimited string

		// Double/Single-quote delimited string
		if (*i == '\'' || *i == '"')
		{
			quote = i;

			do {
				result.push_back(*i);

				// Escape sequences
				if (*i == '\\')
					result.push_back(*++i);
			}
			while (*++i != *quote);
		}

		// Sequences: //, /* */
		if (*i == '/')
		{
			// Single-line sequences
			if (*(i + 1) == '/')
			{
				// Escape sequences
				if (*(i - 1) == '\\')
					result.push_back(*i++);

				// Regular expression + single-line comment (/ ///)
				else if (*(i + 2) == '/' && *(i + 1) != '/');

				// Sigle-line comments
				else {
					while (*++i != '\n');
						continue;
				}
			}

			// Multi-line block comments /* */
			else if (*(i + 1) == '*')
			{
				do {
					while (*++i != '*');
						++i;
				}
				while (*i++ != '/');
			}
		}
		result.push_back(*i++);
	}

	// Erase line feeds (LF, CR, HT)
	this->erase(result, "\n\t\r");

	// Erase spaces (leaving only single spaces)
	result.erase(std::unique(result.begin(), result.end(), find_equal<char>(' ')), result.end());

	return result;
}

#endif
