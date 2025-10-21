#include "multimedia.hpp"
#include "photo.hpp"
#include "video.hpp"
#include "movie.hpp"
#include <utility>
#include <iostream>


multimedia::multimedia(std::string &&name, std::string &&path)
	: name(std::move(name)), path(std::move(path))
{
}

multimedia::~multimedia()
{
}

std::string const &multimedia::get_name() const
{
	return name;
}

std::string const &multimedia::get_path() const
{
	return path;
}

void multimedia::set_name(std::string &&name)
{
	this->name = std::move(name);
}

void multimedia::set_path(std::string &&path)
{
	this->path = std::move(path);
}

void multimedia::display(std::ostream &os) const
{
	os << name << " (" << path << ")";
}

void multimedia::serialize(std::ostream &os) const
{
	os << ' ' << name << " ( " << path << " ) ";
}

managed_t multimedia::deserialize(std::istream &is, std::map<std::string, managed_t> &seen)
{
	using namespace std::string_literals;
	char type;
	is >> type;
	// parse name(path)
	std::string name;
	bool first_segment = true;
	char paren;
	while (!(is >> paren) || paren != '(') {
		is.unget();
		if (first_segment) {
			first_segment = false;
		} else {
			name += " "s;
		}
		std::string name_segment;
		is >> name_segment;
		name += name_segment;
	}
	std::string path;
	is >> path;
	is >> paren;
	// paren == )
	switch (type) {
	case 'P':
		return photo::deserialize(is, seen, std::move(name), std::move(path));
	case 'V':
		return video::deserialize(is, seen, std::move(name), std::move(path));
	case 'M':
		return movie::deserialize(is, seen, std::move(name), std::move(path));
	default:
		return nullptr;
	}
}

