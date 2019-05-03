#include "systemc.h"
#include "Interfaces.h"

SC_MODULE(GreyScale) {
	sc_port<stack_read_if >   InputChannel;
	sc_port<stack_write_if > OutputChannel;
	sc_in<bool> Clk;

	//sc_out<bool> Ready;
	//sc_out<bool> Valid;

	void doGreyScale();

	SC_CTOR(GreyScale) {
		SC_METHOD(doGreyScale);
		sensitive << Clk;
	}
};
