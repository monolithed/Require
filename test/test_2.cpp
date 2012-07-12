#include <iostream>
#include <list>
#include "../require.hpp"

int main()
{
	Require require;

	std::string path("./files/");
	std::string name("file_1.js;file_2.js;");

	// Set file names
	std::list<std::string> file;
	require.split(name, ';', std::back_inserter(file));

	// load the file
	if (require.load(file, path))
	{
		// Get data
		std::string data(require.data(true));

		// Save data to the file
		if (require.save(path + "file.js"))
			std::cout << data << std::endl;

		// Adding data to the end of a File
		//require.save(path + "file.js", std::ios::app)
	}

	return 0;
}
