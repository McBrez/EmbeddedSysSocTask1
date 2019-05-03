/*
 * Interfaces.h
 *
 *  Created on: May 3, 2019
 *      Author: osboxes
 */
#include "systemc.h"

#ifndef INTERFACES_H_
#define INTERFACES_H_


class stack_write_if: virtual public sc_interface
{
public:
  virtual bool nb_write(
		  unsigned int,
		  unsigned int,
		  unsigned int) = 0; // write RGB

  virtual void reset() = 0;         // empty the stack
};

class stack_read_if: virtual public sc_interface
{
public:
  virtual bool nb_read(
		  unsigned int&,
		  unsigned int&,
		  unsigned int&) = 0;  // read RGB
};

#endif /* INTERFACES_H_ */
