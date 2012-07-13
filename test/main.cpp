#include <iostream>
#include <list>
#include "../require.hpp"

int main()
{
	Require require;

	// File path
	std::string path("./files/");

	// File names
	std::string name("file_1.js;file_2.js;");

	// Split file names and insert into any STL container
	std::list<std::string> file;
	require.split(name, ';', std::back_inserter(file));

	/*
	Or you can add the file names explicity:
	file.push_back("file_1.js");	file.push_back("file_2.js");
	*/

	// load the file
	if (require.load(file, path))
	{
		// Get the data
		std::string data(require.data(true /* Optional minification */));

		// Save data to the file
		if (require.save(path + "file.js"))
			std::cout << data << std::endl;

		// Adding data to the end of a File
		//require.save(path + "./file.js", std::ios::app)
	}

	return 0;
}
