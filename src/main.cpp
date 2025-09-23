#include <iostream>
#include <string>
#include "multimedia.hpp"

int main()
{
	using namespace std::string_literals;
	multimedia example("example"s, "path/to/example.type"s);
	example.display(std::cout);
	std::cout << '\n';
}

