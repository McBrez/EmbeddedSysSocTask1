#include "systemc.h"

SC_MODULE(halfadder){																	// declaration of the sc_module halfadder
	sc_in<bool> X, Y;																	// input signal ports
	sc_out<bool> Sum, Carry;															// output signal ports
	
	void do_halfadder()
	{
		Sum.write( ( X.read() && !(Y.read()) ) || ( !(X.read()) && Y.read() ) );		// boolean equation for the SUM
		Carry.write ( X.read() && Y.read() );											// boolean equation for the CARRY
	}
	
	SC_CTOR(halfadder)
	{
		SC_METHOD(do_halfadder);														// register process do_halfadder with kernel
		sensitive << X << Y;															// sensitivity list
	}
};
