/*
 * PixelStack.h
 *
 *  Created on: May 3, 2019
 *      Author: osboxes
 */

#ifndef PIXELSTACK_H_
#define PIXELSTACK_H_

#define STACK_DEPTH 20

#include "systemc.h"
#include "Interfaces.h"

// this class implements the virtual functions
// in the interfaces
class PixelStack
: public sc_module,
  public stack_write_if, public stack_read_if
{
private:
  unsigned int r_value[STACK_DEPTH];
  unsigned int g_value[STACK_DEPTH];
  unsigned int b_value[STACK_DEPTH];

  int top; // pointer to top of stack

public:
  // constructor
  PixelStack(sc_module_name nm);

  bool nb_write(
	unsigned int r,
	unsigned int g,
	unsigned int b );

  void reset();

  bool nb_read(
	unsigned int& r,
	unsigned int& g,
	unsigned int& b );

  void register_port(
	sc_port_base& port_,
	const char* if_typename_);

};

#endif /* PIXELSTACK_H_ */
