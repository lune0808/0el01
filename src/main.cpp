#include <iostream>
#include <string>
#include "multimedia.hpp"
#include "photo.hpp"
#include "video.hpp"

int main()
{
	using namespace std::string_literals;
	multimedia *p1 = new photo("photo1"s, "photo/path/1"s, 1920, 1080);
	multimedia *v1 = new video("video1"s, "video/path/1"s, 123);
	p1->set_path("photo/path/1.1"s);
	p1->display(std::cout);
	std::cout << '\n';
	v1->display(std::cout);
	std::cout << '\n';
	delete p1;
	delete v1;
}

