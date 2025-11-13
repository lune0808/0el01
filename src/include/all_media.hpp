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
	managed_t find_media(std::string const &name);
	//! finds a group object from its name, returns nullptr if the object is not found
	group *find_group(std::string const &name);
	//! prints a human-readable representation of the media/group called 'name' or an error if absent
	void display(std::string const &name, std::ostream &os);
	//! plays the media object called 'name' and returns `true` if it exists else `false`
	bool play(std::string const &name);
	//! removes a media or group and updates its references
	bool remove(std::string const &name);
	//! finds all media/groups whose name matches `prefix`
	std::vector<std::string> prefixed(std::string const &prefix) const;

	//! returns all objects matching the requested type
	template <typename T> std::vector<std::string> type() const
	{
		std::vector<std::string> result;
		if constexpr (!std::is_same_v<T, group>) for (const auto &[name, obj] : media) {
			if (dynamic_cast<T*>(obj.get())) {
				result.push_back(name);
			}
		} else for (const auto &[name, _] : groups) {
			result.push_back(name);
		}
		return result;
	}

	//! returns all objects in the database
	std::vector<std::string> all() const;
	//! returns a string representation of the database
	void serialize(std::ostream &os) const;
	//! builds a database from a string representation
	static all_media deserialize(std::istream &is);
};

