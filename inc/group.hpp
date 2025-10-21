#pragma once

#include <map>
#include <list>
#include "multimedia.hpp"


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
		os << "G " << name << "\n";
		for (const auto &el : *this) {
			os << '\t' << el->get_name() << '\n';
		}
		os << '\n';
	}
	//! creates an object matching the string representation given
	static group deserialize(std::istream &is, std::map<std::string, managed_t> &seen)
	{
		char G;
		is >> G; // G == 'G'
		std::string name;
		is >> name;
		group g(std::move(name));
		for (;;) {
			if (is >> G) {
				is.unget();
				// TODO: media cannot be called just 'G'
				if (G == 'G') {
					break;
				}
			} else if (!is.good() || is.eof()) {
				break;
			}
			std::string name;
			std::getline(is, name);
			const auto it = seen.find(name);
			// TODO: it != seen.end() ?
			g.push_back(it->second);
		}
		return g;
	}
};

