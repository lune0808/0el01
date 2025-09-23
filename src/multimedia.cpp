#include "multimedia.hpp"
#include <utility>
#include <iostream>


multimedia::multimedia(std::string &&name, std::string &&path)
	: name(std::move(name)), path(std::move(path))
{
}

multimedia::~multimedia()
{
	std::cout << "~multimedia()\n";
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

