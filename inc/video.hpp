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

protected:
	friend class all_media;
	//! full constructor giving a complete description of a video
	video(std::string &&name, std::string &&path, size_t duration) :
		multimedia(std::move(name), std::move(path)),
		duration(duration) {}

public:
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
	//! returns a string representation of the object
	void serialize(std::ostream &os) const override
	{
		os << "V ";
		multimedia::serialize(os);
		os << ' ' << duration;
	}
	//! creates an object matching the string representation given
	static managed_t deserialize(std::istream &is, std::map<std::string, managed_t> &seen, std::string &&name, std::string &&path)
	{
		size_t duration;
		is >> duration;
		const auto it = seen.find(name);
		if (it != seen.end()) {
			return it->second;
		} else {
			std::string cname{name};
			return seen.insert({
				std::move(cname),
				std::shared_ptr<video>{new video{std::move(name), std::move(path), duration}}
			}).first->second;
		}
	}
};



