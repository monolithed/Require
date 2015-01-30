/*
* <Require> is a cross-platform file concatenator.
*
* @author: Alexander Abashkin
* @version: 0.0.5
* @license: MIT
* @date: 7/20/12 9:28 PM
*/

#pragma once

#ifndef __REQUIRE_HPP__
#define __REQUIRE_HPP__

#include <fstream>
#include <string>
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
		The erase<T>() erases specified characters in a string

		@param {std::string &} value - Input string
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
					this->data.append(this->read(infile) + "\n");

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
		The Require::save() method provides data saving into a file

		@param name - File path (/files/file.js)
		@param {const std::ios_base::openmode} mode - Bitmask type T3 that describes an object that can store the opening mode.
		@return {bool} - Completion status
		*/
		bool save (const std::string &name, const std::ios_base::openmode &mode = std::ios::binary)
		{
			std::ofstream file(name.c_str(), mode);
			file << this->data;
			file.close();

			return file.good();
		}

		std::string data;
};

#endif
