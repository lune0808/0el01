#include "all_media.hpp"


managed_t all_media::find_media(std::string const &name)
{
	auto position = media.find(name);
	if (position != media.end()) {
		return position->second;
	} else {
		return nullptr;
	}
}

group *all_media::find_group(std::string const &name)
{
	auto position = groups.find(name);
	if (position != groups.end()) {
		return &position->second;
	} else {
		return nullptr;
	}
}

void all_media::display(std::string const &name, std::ostream &os)
{
	if (auto obj = find_media(name); obj) {
		obj->display(os);
	} else if (auto obj = find_group(name); obj) {
		obj->display(os);
	} else {
		os << "(\"" << name << "\" not found)";
	}
}

bool all_media::play(std::string const &name)
{
	auto obj = find_media(name);
	if (obj) {
		obj->play();
		return true;
	} else {
		return false;
	}
}

bool all_media::remove(std::string const &name)
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

std::vector<std::string> all_media::prefixed(std::string const &prefix) const
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

std::vector<std::string> all_media::all() const
{
	std::vector<std::string> result;
	for (const auto &[name, _] : media) {
		result.push_back(name);
	}
	for (const auto &[name, _] : groups) {
		result.push_back(name);
	}
	return result;
}
