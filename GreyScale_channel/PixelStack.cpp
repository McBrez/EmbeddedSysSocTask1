/*
 * PixelStack.cpp
 *
 *  Created on: May 3, 2019
 *      Author: osboxes
 */

#include "PixelStack.h"

PixelStack::PixelStack(sc_module_name nm) :
  sc_module(nm),
  top(0) {
}


bool PixelStack::nb_write(
	  unsigned int r,
	  unsigned int g,
	  unsigned int b ) {

	if ( top < STACK_DEPTH ) {
		r_value[top] = r;
		g_value[top] = g;
		b_value[top] = b;
		top++;
		return true;
	}
	return false;
}

void PixelStack::reset()
{
	top = 0;
}

bool PixelStack::nb_read(
	unsigned int& r,
	unsigned int& g,
	unsigned int& b ) {

	if (top > 0) {
		top--;
		r = r_value[top];
		g = g_value[top];
		b = b_value[top];
		return true;
	}
	return false;
}

void PixelStack::register_port(
	  sc_port_base& port_,
	  const char* if_typename_) {

	cout << "binding    " << port_.name() << " to "
		 << "interface: " << if_typename_ << endl;
}
