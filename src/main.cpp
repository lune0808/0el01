#include <iostream>
#include <string>
#include "multimedia.hpp"
#include "photo.hpp"
#include "video.hpp"
#include "movie.hpp"
#include "group.hpp"


using namespace std::string_literals;

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

void test_film()
{
	auto *m = new movie("star wars"s, "star_wars_movie_remastered_4k.mkv"s, {{1203, 2301, 1491, 1002, 801, 1010, 300}});
	multimedia *pm = m;
	pm->display(std::cout);
	std::cout << '\n';
	multimedia *copy = new movie(*m);
	delete pm;
	copy->display(std::cout);
	std::cout << '\n';
	delete copy;
}

void test_group()
{
	std::shared_ptr<multimedia> p1 = std::make_shared<photo>("pig"s, "pig.jpg"s, 1280, 720);
	std::shared_ptr<multimedia> v1 = std::make_shared<video>("nyan cat"s, "nyan_cat.mp4"s, 180);
	std::shared_ptr<multimedia> p2 = std::make_shared<photo>("burger"s, "beesechurger.png"s, 1920, 1080);
	std::shared_ptr<multimedia> m1 = std::make_shared<movie>("rango", "rango_movie_blabla.mkv"s, movie::chapters_t{{600, 700, 550, 810, 300, 920, 470}});
	std::shared_ptr<multimedia> v2 = std::make_shared<video>("conference"s, "abcd_conference_recording_25041996.mp4"s, 5492);
	std::shared_ptr<multimedia> v3 = std::make_shared<video>("idk"s, "sbdhajdkasds.mp4", 2199);

	std::shared_ptr<multimedia> arr[] = { p1, v1, p2, m1, v2, v3 };
	std::cout << '\n';
	for (const auto elem : arr) {
		elem->display(std::cout);
		std::cout << '\n';
	}
	std::cout << '\n';

	{
		group g( "MyMovies"s, v2, m1, v1, v3 );
		g.display(std::cout);
		std::cout << "\n\n";
	}
}

int main()
{
	test_base_inst();
	test_array_access();
	test_film();
	test_group();
}

