#pragma once

#include <list>
#include <memory>
#include "multimedia.hpp"


class group : public std::list<std::shared_ptr<multimedia>>
{
	std::string name;

public:
	template <typename ...Args>
	group(std::string &&name, Args&& ...args) :
		std::list<std::shared_ptr<multimedia>>{ std::forward<Args>(args)... },
		name(std::move(name))
	{
	}

	std::string const &get_name() const { return name; }

	void display(std::ostream &os) const
	{
		os << name << '{';
		bool first = true;
		for (const auto elem : *this) {
			if (!first)
				os << ", ";
			first = false;
			elem->display(os);
		}
		os << '}';
	}
};

