#pragma once

#include "multimedia.hpp"
#include <stddef.h>
#include <utility>


/**
  \brief represents a photograph

  represents a photograph by its dimensions to
  stay simple, and inherits from the multimedia
  base class
 */
class photo : public multimedia
{
	size_t width; //!< width of the image
	size_t height; //!< height of the image

public:
	//! default constructor
	photo() : width(0), height(0) {}
	//! full constructor giving a complete description of a photograph
	photo(std::string &&name, std::string &&path, size_t width, size_t height) :
		multimedia(std::move(name), std::move(path)),
		width(width),
		height(height)
	{}
	//! destructor for photo
	~photo() = default;

	//! getter for width
	size_t get_width() const { return width; }
	//! getter for height
	size_t get_height() const { return height; }
	//! setter for width
	void set_width(size_t width) { this->width = width; }
	//! setter for height
	void set_height(size_t height) { this->height = height; }

	//! displays the underlying object as text
	void display(std::ostream &os) const override
	{
		multimedia::display(os);
		os << ": " << width << "x" << height << " photo";
	}
	//! displays the underlying object using the appropriate program
	void play() const override
	{
		using namespace std::string_literals;
		std::string command = "imagej "s + get_path() + " &"s;
		system(command.c_str());
	}
};

