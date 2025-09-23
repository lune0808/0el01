#include <iostream>
#include <string>
#include "multimedia.hpp"
#include "photo.hpp"
#include "video.hpp"

void test_base_inst()
{
	// cannot make instances of the base class anymore
	// because it has pure virtual methods
	// multimedia m;
}

void test_array_access()
{
	// type-erasure allows to access different types through a pointer to a common type
	// in C++ we make the array have pointer-to-base elements
	// in Java we just make an array of the base class, since internally Java already
	// uses pointers to represent all objects
	multimedia *arr[6];
	std::string names = "123456";
	std::string paths = "abcdef";
	for (size_t i = 0; i < std::size(arr); ++i) {
		if (i % 2) {
			arr[i] = new photo(names.substr(i, 1), paths.substr(i, 1) + ".png"s, 1920, 1080);
		} else {
			arr[i] = new video(names.substr(i, 1), paths.substr(i, 1) + ".mp4"s, 100 + i*4);
		}
	}
	for (auto mm : arr) {
		mm->display(std::cout);
		std::cout << '\n';
	}
	for (auto mm : arr) {
		delete mm;
	}
}

int main()
{
	using namespace std::string_literals;
	test_base_inst();
	test_array_access();
}

