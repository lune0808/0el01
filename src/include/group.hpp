#pragma once

#include <map>
#include <list>
#include <optional>
#include "multimedia.hpp"

// this symbol can never be in a file name
// so we use it in the serialized format as a sentinel
#define GROUP_SYMBOL '/'

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
	//! returns a string representation of the object
	void serialize(std::ostream &os) const
	{
		os << GROUP_SYMBOL << ' ' << name << "\n";
		for (const auto &el : *this) {
			os << '\t' << el->get_name() << '\n';
		}
		os << '\n';
	}
	//! creates an object matching the string representation given
	static std::optional<group> deserialize(std::istream &is, std::map<std::string, managed_t> &seen)
	{
		char G = GROUP_SYMBOL^1; // anything different from GROUP_SYMBOL
		is >> G; // G == GROUP_SYMBOL
		if (G != GROUP_SYMBOL) {
			return std::nullopt;
		}

		std::string name;
		is >> name;
		if (!allowed_name(name)) {
			return std::nullopt;
		}

		group g(std::move(name));
		for (;;) {
			if (is >> G) {
				is.unget();
				if (G == GROUP_SYMBOL) {
					break;
				}
			} else if (!is.good() || is.eof()) {
				break;
			}
			std::string name;
			std::getline(is, name);
			const auto it = seen.find(name);
			// ignores unknown names
			if (it != seen.end()) {
				g.push_back(it->second);
			}
		}
		return g;
	}
};

