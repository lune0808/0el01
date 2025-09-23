#pragma once

#include "multimedia.hpp"
#include <stddef.h>
#include <utility>


class photo : public multimedia
{
	size_t width;
	size_t height;

public:
	photo() : width(0), height(0) {}
	photo(std::string &&name, std::string &&path, size_t width, size_t height) :
		multimedia(std::move(name), std::move(path)),
		width(width),
		height(height)
	{}
	~photo() = default;

	size_t get_width() const { return width; }
	size_t get_height() const { return height; }
	void set_width(size_t width) { this->width = width; }
	void set_height(size_t height) { this->height = height; }

	void display(std::ostream &os) const override
	{
		multimedia::display(os);
		os << ": " << width << "x" << height << " photo";
	}
};

