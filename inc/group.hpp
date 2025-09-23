#pragma once

#include <list>
#include <memory>
#include "multimedia.hpp"


/**
  any multimedia object with automatic memory management
 */
using managed_t = std::shared_ptr<multimedia>;

/**
  factory function for managed multimedia objects
 */
template <typename T, typename ...Args>
static inline managed_t make_managed(Args&& ...args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}

/**
  \brief a group of multimedia objects

  a group of multimedia objects that will only delete
  objects that are not referenced by any other group
 */
class group : public std::list<managed_t>
{
	std::string name; //!< the user-readable name of the group

public:
	/*!
	  constructor for a group
	  call be called like this: group("myName"s, elem_1, elem_2, elem_3)
	 */
	template <typename ...Args>
	group(std::string &&name, Args&& ...args) :
		std::list<managed_t>{ std::forward<Args>(args)... },
		name(std::move(name))
	{
	}

	//! getter for the name of the group
	std::string const &get_name() const { return name; }

	//! displays the group as text with all its elements
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

