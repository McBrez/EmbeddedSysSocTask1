#include "systemc.h"
#include "nBitAdder.cpp"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

void getRand(sc_vector<sc_signal<bool> >& vector) {
	for(int i = 0; i < 8 ; i++) {
		if( (rand() % 100) < 50 ) {
			vector[i].write(false);
		}
		else {
			vector[i].write(true);
		}
	}
}

int sc_main(int argc, char* argv[])
{
	sc_signal<bool> Carry_In;										// input signal Carry_In
	sc_core::sc_vector< sc_signal<bool> > A, B;						// input vectors A and B
	sc_core::sc_vector< sc_signal<bool> > Sum;						// output vectors Sum
	sc_signal<bool> Carry_Out;										// output signal Carry_Out
	sc_time clkPeriod(10,SC_MS)	;
	sc_clock clock ("testClock",clkPeriod,0.5);						// clock input
	
	nBitAdder Dut("DUT",8);											// Instantiate the Device Under Test
	char wfText[5];
	
	A.init(8);
	B.init(8);
	Sum.init(8);

	for(unsigned int i = 0; i < 8; i++)
	{
		Dut.A[i](A[i]);
		Dut.B[i](B[i]);
		Dut.Sum[i](Sum[i]);
	}
	
	Dut.carryIn(Carry_In);
	Dut.carryOut(Carry_Out);
	Dut.Clk(clock);

	sc_trace_file *wf = sc_create_vcd_trace_file("nadder");		// Open VCD files
	
	wf->set_time_unit(1,SC_MS);

	for(unsigned int i = 0; i < 8; i++)
	{
		sprintf(wfText, "A(%i)", i);
		sc_trace(wf, A[i], wfText);								// Store the signals in the VCD files
		sprintf(wfText, "B(%i)", i);
		sc_trace(wf, B[i], wfText);
		sprintf(wfText, "S(%i)", i);
		sc_trace(wf, Sum[i], wfText);
	}


	sc_trace(wf, Carry_In, "Carry_In");
	sc_trace(wf, Carry_Out, "Carry_Out");
	sc_trace(wf, clock, "CLK");
	
	getRand(A);
	getRand(B);
	Carry_In.write(false);
	sc_start(100,SC_MS);
	
	getRand(A);
	getRand(B);
	Carry_In.write(true);
	sc_start(100,SC_MS);
	
	getRand(A);
	getRand(B);
	Carry_In.write(false);
	sc_start(100,SC_MS);
	
	getRand(A);
	getRand(B);
	Carry_In.write(true);
	sc_start(100,SC_MS);
	
	cout << "@" << sc_time_stamp() <<" Terminating simulation\n" << endl;
	sc_close_vcd_trace_file(wf);
	sc_stop();

	return 0;
}
	
	
	
