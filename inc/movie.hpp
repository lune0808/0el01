#pragma once

#include "video.hpp"
#include <span>


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

	//! default constructor
	movie() : nchapters(0), chapters(nullptr) {}
	//! full constructor computing the correct video duration for a movie
	movie(std::string &&name, std::string &&path, chapters_t chapters);
	//! destructor for movie
	~movie() = default;

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
};

