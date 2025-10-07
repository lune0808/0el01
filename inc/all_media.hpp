#pragma once

#include <map>
#include <string>
#include <utility>
#include <type_traits>
#include <vector>
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
	managed_t find_media(std::string const &name)
	{
		auto position = media.find(name);
		if (position != media.end()) {
			return position->second;
		} else {
			return nullptr;
		}
	}

	//! finds a group object from its name, returns nullptr if the object is not found
	group *find_group(std::string const &name)
	{
		auto position = groups.find(name);
		if (position != groups.end()) {
			return &position->second;
		} else {
			return nullptr;
		}
	}

	//! prints a human-readable representation of the media/group called 'name' or an error if absent
	void display(std::string const &name, std::ostream &os)
	{
		if (auto obj = find_media(name); obj) {
			obj->display(os);
		} else if (auto obj = find_group(name); obj) {
			obj->display(os);
		} else {
			os << "(\"" << name << "\" not found)";
		}
	}

	//! plays the media object called 'name' and returns `true` if it exists else `false`
	bool play(std::string const &name)
	{
		auto obj = find_media(name);
		if (obj) {
			obj->play();
			return true;
		} else {
			return false;
		}
	}

	//! removes a media or group and updates its references
	bool remove(std::string const &name)
	{
		if (auto position = media.find(name); position != media.end()) {
			media.erase(position);
			for (auto &[_, gp] : groups) {
				gp.remove(position->second);
			}
			return true;
		} else if (auto position = groups.find(name); position != groups.end()) {
			groups.erase(position);
			return true;
		} else {
			return false;
		}
	}

	//! finds all media/groups whose name matches `prefix`
	std::vector<std::string> prefixed(std::string const &prefix)
	{
		std::vector<std::string> result;
		for (const auto &[name, _] : media) {
			if (name.starts_with(prefix)) {
				result.push_back(name);
			}
		}
		for (const auto &[name, _] : groups) {
			if (name.starts_with(prefix)) {
				result.push_back(name);
			}
		}
		return result;
	}
};

