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
	managed_t p1 = make_managed<photo>("pig"s, "pig.jpg"s, 1280, 720);
	managed_t v1 = make_managed<video>("nyan cat"s, "nyan_cat.mp4"s, 180);
	managed_t p2 = make_managed<photo>("burger"s, "beesechurger.png"s, 1920, 1080);
	managed_t m1 = make_managed<movie>("rango", "rango_movie_blabla.mkv"s, movie::chapters_t{{600, 700, 550, 810, 300, 920, 470}});
	managed_t v2 = make_managed<video>("conference"s, "abcd_conference_recording_25041996.mp4"s, 5492);
	managed_t v3 = make_managed<video>("idk"s, "sbdhajdkasds.mp4", 2199);

	managed_t arr[] = { p1, v1, p2, m1, v2, v3 };
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

