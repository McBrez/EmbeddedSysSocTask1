#include "systemc.h"
#include "nBitAdder.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

void getRand(sc_vector<sc_signal<bool> >& vector) {			// random number generator
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
	sc_signal<bool> Carry_In;								// input signal Carry_In
	sc_vector< sc_signal<bool> > A, B;						// input vectors A and B
	sc_vector< sc_signal<bool> > Sum;						// output vectors Sum
	sc_signal<bool> Carry_Out;								// output signal Carry_Out
	sc_time clkPeriod(10,SC_MS)	;							// clock time
	sc_clock clock ("testClock",clkPeriod,0.5);				// clock input (0.5 = duty cycle)
	
	nBitAdder Dut("DUT",8);									// Instantiate the Device Under Test as an 8-bit ripple carry adder
	char wfText[5];											// Define text to name every single bus line of the 8-bit number for the vcd-file
	
	A.init(8);												// Initialise sc_vectors with 8 bit width
	B.init(8);
	Sum.init(8);

	for(unsigned int i = 0; i < 8; i++)						// Loop over the DUT ports A,B (inputs) and Sum (outputs) to associate them with sc_vectors of type sc_signals
	{
		Dut.A[i](A[i]);
		Dut.B[i](B[i]);
		Dut.Sum[i](Sum[i]);
	}
	
	Dut.carryIn(Carry_In);									// Associate the other input ports sc_signals and sc_clock
	Dut.carryOut(Carry_Out);
	Dut.Clk(clock);

	sc_trace_file *wf = sc_create_vcd_trace_file("nadder");		// Open VCD files
	
	wf->set_time_unit(1,SC_MS);

	for(unsigned int i = 0; i < 8; i++)
	{
		sprintf(wfText, "A(%i)", i);                            // Store the signals in the VCD files and build strings to name them properly in the GTKwave viewer
		sc_trace(wf, A[i], wfText);
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
	
	
	
