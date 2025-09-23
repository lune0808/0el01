#include <iostream>
#include <string>
#include "multimedia.hpp"

int main()
{
	using namespace std::string_literals;
	multimedia example("example"s, "path/to/example.type"s);
	example.display(std::cout);
	std::cout << '\n';
	multimedia *ex1 = new multimedia("ex1"s, "path1"s);
	multimedia *ex2 = new multimedia("ex2"s, "path2"s);
	ex1->set_path("path1.1"s);
	ex2->display(std::cout);
	std::cout << '\n';
	ex1->display(std::cout);
	std::cout << '\n';
}

