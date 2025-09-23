#pragma once

#include "multimedia.hpp"
#include <stddef.h>
#include <utility>


class video : public multimedia
{
	size_t duration;

public:
	video() : duration
	(0) {}
	video(std::string &&name, std::string &&path, size_t duration) :
		multimedia(std::move(name), std::move(path)),
		duration(duration) {}
	~video() = default;

	size_t get_duration() const { return duration; }
	void set_duration(size_t duration) { this->duration = duration; }

	void display(std::ostream &os) const override
	{
		multimedia::display(os);
		os << ": " << duration << "s video";
	}
};



