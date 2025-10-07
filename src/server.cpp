//
//  server.cpp
//  TP C++
//  Eric Lecolinet - Telecom ParisTech - 2016.
//

#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include "tcpserver.h"
#include "photo.hpp"
#include "video.hpp"
#include "movie.hpp"
#include "group.hpp"
#include "all_media.hpp"

const int PORT = 3331;


static all_media database;

using namespace std::string_literals;

bool server_main(std::string const &request, std::string &response)
{
	const auto len = request.length();
	std::stringstream input(request);
	std::string arg;
	input >> arg;
	if (arg == "find"s) {
		std::stringstream output;
		input >> arg;
		database.display(arg, output);
		response = output.str();
	} else if (arg == "play"s) {
		input >> arg;
		const auto found = database.play(arg);
		response = (found? "Y": "N");
	} else {
		response = "<unknown command>";
	}
	return true;
}

int main(int argc, char* argv[])
{
	database.create_media<photo>("pig"s, "pig.jpg"s, 1280lu, 720lu);
	database.create_media<video>("nyan_cat"s, "nyan_cat.mp4"s, 180lu);
	database.create_media<movie>("rango"s, "rango_movie_blabla.mkv"s, movie::chapters_t{{600lu, 700lu, 550lu, 810lu, 300lu, 920lu, 470lu}});

	std::cout << "Starting Server on port " << PORT << std::endl;
	TCPServer sv(server_main);
	int status = sv.run(PORT);
	if (status < 0) {
		std::cerr << "Could not start Server on port " << PORT << std::endl;
		return 1;
	}
	return 0;
}

