#pragma once

#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <type_traits>
#include "multimedia.hpp"
#include "group.hpp"


/**
  \brief owns all the multimedia objects

  owns all the multimedia objects and offers operations on them through their name
 */
class all_media
{
	std::map<std::string, managed_t> media; //!< associative map between names and media
	std::map<std::string, group> groups; //!< associative map between names and groups
public:
	//! creates a new managed media object of any type
	template <typename T, typename ...Args>
	managed_t create_media(std::string &&name, Args&& ...args)
	{
		auto [position, inserted] = media.try_emplace(name, nullptr);
		if (inserted) {
			position->second =
				std::shared_ptr<T>(new T{std::move(name), std::forward<Args>(args)...});
			return position->second;
		} else {
			return nullptr;
		}
	}

	//! creates a new managed group based on the name of its elements
	template <typename ...Args>
		requires (std::constructible_from<std::string, Args> && ... && true)
	group *create_group(std::string &&name, Args&& ...elements)
	{
		auto key(name);
		auto [position, inserted] =
			groups.try_emplace(std::move(key), std::move(name));
		if (inserted) {
			std::string names[] = { elements... };
			for (auto &&name : names) {
				auto obj = media.find(std::move(name));
				if (obj != media.end()) {
					position->second.push_back(obj->second);
				}
			}
			return &position->second;
		} else {
			return nullptr;
		}
	}

	//! finds a media object from its name, returns nullptr if the object is not found
	managed_t find(std::string const &name)
	{
		auto position = media.find(name);
		if (position != media.end()) {
			return position->second;
		} else {
			return nullptr;
		}
	}

	//! prints a human-readable representation of the media called 'name' or an error if absent
	void display(std::string const &name, std::ostream &os)
	{
		auto obj = find(name);
		if (obj) {
			obj->display(os);
		} else {
			os << "(\"" << name << "\" not found)";
		}
	}

	//! plays the media object called 'name' and returns `true` if it exists else `false`
	bool play(std::string const &name)
	{
		auto obj = find(name);
		if (obj) {
			obj->play();
			return true;
		} else {
			return false;
		}
	}
};

