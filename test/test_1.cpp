#include <iostream>
#include <list>
#include "../require.hpp"

int main()
{
	Require require;

	std::string path("./files/");

	// Set file names
	std::list<std::string> file;
	file.push_back("file_1.js");
	file.push_back("file_2.js");

	// load the file
	if (require.load(file, path))
	{
		// Get data
		std::string data(require.data(true));

		// Save data into the file
		if (require.save("./file.js"))
			std::cout << data << std::endl;
	}

	return 0;
}
