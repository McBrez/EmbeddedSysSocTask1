#include "systemc.h"

SC_MODULE(GreyScale) {
	sc_in<sc_uint<8> > R, G, B;
	sc_out<sc_uint<8> > Grey;
	sc_in<bool> Clk;

	//sc_out<bool> Ready;
	//sc_out<bool> Valid;

	void doGreyScale();

	void doLookupTable();

	SC_CTOR(GreyScale) {
		SC_METHOD(doLookupTable);
		sensitive << Clk;
	}
};
