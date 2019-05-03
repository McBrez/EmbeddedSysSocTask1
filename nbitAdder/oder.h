#include "systemc.h"

#ifndef ODER_H
#define ODER_H

SC_MODULE(oder)							// declaration of the sc_module oder
{
	sc_in<bool> X, Y;					// input signal ports
	sc_out<bool> Res;					// output signal port

	void do_oder();						// declaration of methode do_or()

	SC_CTOR(oder)
	{
		SC_METHOD(do_oder);				// register process do_or with kernel
		sensitive << X << Y;			// sensitivity list
	}
};

#endif
