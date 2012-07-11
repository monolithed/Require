#include <iostream>
#include "../require.hpp"

int main ()
{
	Require require(true);    // optional, minify
	Require::delimiter = ';'; // optional, delimiter

	std::string path("./");   // optional, path
	std::string file("file_1.js;file_2.js;");

	std::cout << require.load(file, path) << std::endl;

	return 0;
}
