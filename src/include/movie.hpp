#pragma once

#include "video.hpp"
#include <span>
#include <vector>


/**
  \brief represents a movie with chapters

  represents a movie segmented by chapters of
  independent lengths, all measured in seconds
 */
class movie : public video
{
	size_t nchapters; //!< number of chapters
	size_t *chapters; //!< individual duration in seconds of each chapter, sorted in order

public:
	using chapters_t = std::span<const size_t>; //!< represents a buffer of chapters for message passing

protected:
	friend class all_media;
	//! full constructor computing the correct video duration for a movie
	movie(std::string &&name, std::string &&path, chapters_t chapters);

public:
	//! copy constructor
	movie(movie const &other);
	//! destructor for movie
	~movie();

	/*!
	  getter for chapters
	  the result is only valid until the next call to set_chapters
	 */
	chapters_t get_chapters() const;
	/*!
	  setter for chapters
	  only accepts a chapter list that maintains the duration of the video
	 */
	bool set_chapters(chapters_t chapters);

	//! displays the underlying object as text
	void display(std::ostream &os) const;
	//! returns a string representation of the object
	void serialize(std::ostream &os) const override
	{
		os << "M ";
		multimedia::serialize(os);
		os << ' ' << nchapters << ' ';
		for (size_t chap = 0; chap < nchapters; ++chap) {
			os << ' ' << chapters[chap];
		}
	}
	//! creates an object matching the string representation given
	static managed_t deserialize(std::istream &is, std::map<std::string, managed_t> &seen, std::string &&name, std::string &&path)
	{
		std::vector<size_t> chapters;
		size_t nchap;
		is >> nchap;
		for (size_t ichap = 0; ichap < nchap; ++ichap) {
			size_t duration;
			is >> duration;
			chapters.push_back(duration);
		}
		const auto it = seen.find(name);
		if (it != seen.end()) {
			return it->second;
		} else {
			std::string cname{name};
			std::span<size_t> chapters_span{chapters.begin(), chapters.size()};
			return seen.insert({
				std::move(cname),
				std::shared_ptr<movie>{new movie{std::move(name), std::move(path), chapters_span}}
			}).first->second;
		}
	}
};

