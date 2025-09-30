#pragma once

#include <string>
#include <iostream>
#include <memory>


/**
  \brief base class for multimedia objects

  represents a common type for all multimedia objects,
  storing a user-readable name and a system path
 */
class multimedia
{
	std::string name; //!< user-readable name
	std::string path; //!< system path of the underlying file

public:
	//! full constructor that subclasses should call
	multimedia(std::string &&name, std::string &&path);
	//! virtual destructor necessary because multimedia is polymorphic
	virtual ~multimedia();

	//! getter for name
	std::string const &get_name() const;
	//! getter for path
	std::string const &get_path() const;
	//! setter for name
	void set_name(std::string &&name);
	//! setter for path
	void set_path(std::string &&path);

	//! displays the underlying object as text
	virtual void display(std::ostream &os) const;
	//! displays the underlying object using the appropriate program
	virtual void play() const = 0;
};

/**
  any multimedia object with automatic memory management
 */
using managed_t = std::shared_ptr<multimedia>;

