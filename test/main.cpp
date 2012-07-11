#include <iostream>
#include "../require.hpp"

int main ()
{

/*
	std::string str("s  om e");

	erase(str, " ");

	std::cout << str << std::endl;

*/
	Require require(true);

	std::string path("./");
	std::string file("file_1.js;file_2.js;");

	std::cout << require.load(file, path) << std::endl;

	return 0;
}
