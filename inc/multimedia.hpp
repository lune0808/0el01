#pragma once

#include <string>
#include <iostream>


class multimedia
{
	std::string name;
	std::string path;

public:
	multimedia() = default;
	multimedia(std::string &&name, std::string &&path);
	~multimedia() = default;

	std::string const &get_name() const;
	std::string const &get_path() const;
	void set_name(std::string &&name);
	void set_path(std::string &&path);

	void display(std::ostream &os) const;
};


