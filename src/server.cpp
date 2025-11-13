//
//  server.cpp
//  TP C++
//  Eric Lecolinet - Telecom ParisTech - 2016.
//

#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include "tcpserver.h"
#include "photo.hpp"
#include "video.hpp"
#include "movie.hpp"
#include "group.hpp"
#include "all_media.hpp"

const int PORT = 3331;


static all_media database;

using namespace std::string_literals;

static std::string cmd_find(std::istream &is)
{
	std::stringstream output;
	std::string name;
	is >> name;
	database.display(name, output);
	return output.str();
}

static std::string cmd_play(std::istream &is)
{
	std::string name;
	is >> name;
	const auto ok = database.play(name);
	return ok ? "Y"s : "N"s;
}

static std::string cmd_prefixed(std::istream &is)
{
	std::stringstream output;
	std::string pattern;
	is >> pattern;
	for (auto &&name : database.prefixed(pattern)) {
		output << name << ' ';
	}
	return output.str();
}

static std::string cmd_type(std::istream &is)
{
	std::stringstream output;
	std::string type;
	is >> type;
	std::vector<std::string> names;
	if (type.length() != 0) switch (type[0]) {
	case 'P':
		names = database.type<photo>();
		break;
	case 'V':
		names = database.type<video>();
		break;
	case 'M':
		names = database.type<movie>();
		break;
	case 'G':
		names = database.type<group>();
		break;
	default:
		break;
	}
	for (auto &&name : names) {
		output << name << ' ';
	}
	return output.str();
}

static std::string cmd_all(std::istream &)
{
	std::stringstream output;
	for (auto&& name : database.all()) {
		output << name << ' ';
	}
	return output.str();
}

static std::string cmd_remove(std::istream &is)
{
	std::string name;
	is >> name;
	const auto ok = database.remove(name);
	return ok ? "Y"s : "N"s;
}

static std::string cmd_help(std::istream &is)
{
	const std::map<std::string, std::string> message{
		{ "find"s, "usage: find <name> (returns text representation of corresponding object)"s },
		{ "play"s, "usage: play <name> (returns Y if the object was played successfully, N on failure)"s },
		{ "prefixed"s, "usage: prefixed <pattern> (returns a list of prefix matches)"s },
		{ "type"s, "usage: type <inital> (returns all files with the type corresponding to initial: P for Photo, V for Video, M for Movie, G for Group)"s },
		{ "all"s, "usage: all (returns the entire database)"s },
		{ "remove"s, "usage: remove <name> (removes an object from the database, returns Y/N depending on success)"s },
	};
	std::string name;
	is >> name;
	const auto it = message.find(name);
	std::string response;
	if (it != message.end()) {
		response = it->second;
	} else {
		response = "unknown command request. available commands are: find, play, prefixed, type, all, remove."s;
	}
	return response;
}

static bool server_main(std::string const &request, std::string &response)
{
	using command_t = std::string(*)(std::istream&);
	const std::map<std::string, command_t> execute{
		{ "find"s, cmd_find },
		{ "play"s, cmd_play },
		{ "prefixed"s, cmd_prefixed },
		{ "type"s, cmd_type },
		{ "all"s, cmd_all },
		{ "remove"s, cmd_remove },
		{ "help"s, cmd_help },
	};
	std::stringstream input(request);
	std::string command;
	input >> command;
	const auto it = execute.find(command);
	if (it != execute.end()) {
		response = it->second(input);
	} else {
		response = "unknown command. ask help for more details"s;
	}
	return true;
}

int main(int argc, char* argv[])
{
	database.create_media<photo>("pig"s, "pig.jpg"s, 1280lu, 720lu);
	database.create_media<video>("nyan_cat"s, "nyan_cat.mp4"s, 180lu);
	database.create_media<video>("nyan_cat2"s, "nyan_cat.mp4"s, 180lu);
	database.create_media<movie>("rango"s, "rango_movie_blabla.mkv"s, movie::chapters_t{{600lu, 700lu, 550lu, 810lu, 300lu, 920lu, 470lu}});
	database.create_group("MyMovies"s, "rango"s, "nyan cat"s);

	std::cout << "Starting Server on port " << PORT << std::endl;
	TCPServer sv(server_main);
	int status = sv.run(PORT);
	if (status < 0) {
		std::cerr << "Could not start Server on port " << PORT << std::endl;
		return 1;
	}
	return 0;
}

