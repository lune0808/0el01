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

protected:
	friend class all_media;
	//! full constructor giving a complete description of a photograph
	photo(std::string &&name, std::string &&path, size_t width, size_t height) :
		multimedia(std::move(name), std::move(path)),
		width(width),
		height(height)
	{}

public:
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
	//! returns a string representation of the object
	void serialize(std::ostream &os) const override
	{
		os << "P ";
		multimedia::serialize(os);
		os << ' ' << width << ' ' << height;
	}
	//! creates an object matching the string representation given
	static managed_t deserialize(std::istream &is, std::map<std::string, managed_t> &seen, std::string &&name, std::string &&path)
	{
		size_t width;
		size_t height;
		is >> width >> height;
		const auto it = seen.find(name);
		if (it != seen.end()) {
			return it->second;
		} else {
			std::string cname{name};
			return seen.insert({
				std::move(cname),
				std::shared_ptr<photo>{new photo{std::move(name), std::move(path), width, height}}
			}).first->second;
		}
	}
};

