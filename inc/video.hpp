#pragma once

#include "multimedia.hpp"
#include <stddef.h>
#include <utility>


/**
  \brief represents a video

  represents a video just by its duration
  to keep the code simple, and inherits from
  the multimedia base class
 */
class video : public multimedia
{
	size_t duration; //!< duration of the video in seconds

public:
	//! default constructor
	video() : duration(0) {}
	//! full constructor giving a complete description of a video
	video(std::string &&name, std::string &&path, size_t duration) :
		multimedia(std::move(name), std::move(path)),
		duration(duration) {}
	//! description for video
	~video() = default;

	//! getter for duration
	size_t get_duration() const { return duration; }
	//! setter for duration
	void set_duration(size_t duration) { this->duration = duration; }

	//! displays the underlying object as text
	void display(std::ostream &os) const override
	{
		multimedia::display(os);
		os << ": " << duration << "s video";
	}
	//! displays the underlying object using the appropriate program
	void play() const override
	{
		using namespace std::string_literals;
		std::string command = "mpv "s + get_path() + " &"s;
		system(command.c_str());
	}
};



