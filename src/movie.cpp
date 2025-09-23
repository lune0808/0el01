#include "movie.hpp"
#include <string.h>


using chapters_t = movie::chapters_t;

static size_t cumulative_sum(chapters_t list)
{
	size_t sum = 0;
	for (const auto elem : list) {
		sum += elem;
	}
	return sum;
}

static size_t *dupe(chapters_t list)
{
	auto *memory = new size_t[list.size()];
	memcpy(memory, list.data(), list.size() * sizeof *memory);
	return memory;
}

movie::movie(std::string &&name, std::string &&path, chapters_t chapters) :
	video(std::move(name), std::move(path), cumulative_sum(chapters)),
	nchapters(chapters.size()),
	chapters(dupe(chapters))
{
}

chapters_t movie::get_chapters() const
{
	return { chapters, nchapters };
}

bool movie::set_chapters(chapters_t chapters)
{
	if (cumulative_sum(chapters) != get_duration())
		return false;
	size_t *new_storage = dupe(chapters);
	delete[] this->chapters;
	this->chapters = new_storage;
	this->nchapters = chapters.size();
	return true;
}

void movie::display(std::ostream &os) const
{
	video::display(os);
	os << '[';
	for (size_t chap = 0; chap < nchapters; ++chap) {
		if (chap != 0)
			os << ", ";
		os << std::to_string(chapters[chap]) << 's';
	}
	os << ']';
}

