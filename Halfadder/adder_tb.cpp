#include "systemc.h"
#include "fulladder.cpp"

int sc_main(int argc, char* argv[])
{
	sc_signal<bool> X, Y, Carry_In;									// input signals for testing both adders
	sc_signal<bool> SumHadder, Carry_OutHadder;						// output signals for testing the halfadder
	sc_signal<bool> SumFadder, Carry_OutFadder;						// output signals for testing the fulladder
	
	halfadder DutHadder("duthadder");								// Instantiate the Devices Under Test
	fulladder DutFadder("dutfadder");
	
	DutHadder.X(X);													// Connect the Devices Under Test
	DutHadder.Y(Y);
	DutHadder.Sum(SumHadder);
	DutHadder.Carry(Carry_OutHadder);
	
	DutFadder.X(X);											
	DutFadder.Y(Y);
	DutFadder.Carry_In(Carry_In);
	DutFadder.Sum(SumFadder);
	DutFadder.Carry_Out(Carry_OutFadder);

	
	sc_trace_file *wfHadder = sc_create_vcd_trace_file("hadder");		// Open VCD files
	sc_trace_file *wfFadder = sc_create_vcd_trace_file("Fadder");
	
	wfHadder->set_time_unit(1,SC_MS);
	wfFadder->set_time_unit(1,SC_MS);

	sc_trace(wfHadder, X, "X");										// Store the signals in the VCD files
	sc_trace(wfHadder, Y, "Y");
	sc_trace(wfHadder, SumHadder, "SumHadder");
	sc_trace(wfHadder, Carry_OutHadder, "Carry_OutHadder");

	sc_trace(wfFadder, X, "X");
	sc_trace(wfFadder, Y, "Y");
	sc_trace(wfFadder, Carry_In, "Carry_In");
	sc_trace(wfFadder, SumFadder, "SumFadder");
	sc_trace(wfFadder, Carry_OutFadder, "Carry_OutFadder");
	
	sc_start(100,SC_MS);
	X.write(false);
	Y.write(false);
	Carry_In.write(false);
	cout << "@" << sc_time_stamp() <<" Asserting X = 0 and Y = 0\n" << endl;
	
	sc_start(100,SC_MS);
	X.write(true);
	Y.write(false);
	Carry_In.write(false);
	cout << "@" << sc_time_stamp() <<" Asserting X = 1 and Y = 0\n" << endl;
	
	sc_start(100,SC_MS);
	X.write(false);
	Y.write(true);
	Carry_In.write(false);
	cout << "@" << sc_time_stamp() <<" Asserting X = 0 and Y = 1\n" << endl;
	
	sc_start(100,SC_MS);
	X.write(true);
	Y.write(true);
	Carry_In.write(false);
	cout << "@" << sc_time_stamp() <<" Asserting X = 1 and Y = 1\n" << endl;
	
	sc_start(100,SC_MS);
	X.write(false);
	Y.write(false);
	Carry_In.write(true);
	cout << "@" << sc_time_stamp() <<" Asserting X = 0, Y = 0 and Carry_In = 1 for Full Adder\n" << endl;
	
	sc_start(100,SC_MS);
	X.write(true);
	Y.write(false);
	Carry_In.write(true);
	cout << "@" << sc_time_stamp() <<" Asserting X = 1, Y = 0 and Carry_In = 1 for Full Adder\n" << endl;
	
	sc_start(100,SC_MS);
	X.write(false);
	Y.write(true);
	Carry_In.write(true);
	cout << "@" << sc_time_stamp() <<" Asserting X = 0, Y = 1 and Carry_In = 1 for Full Adder\n" << endl;
	
	sc_start(100,SC_MS);
	X.write(true);
	Y.write(true);
	Carry_In.write(true);
	cout << "@" << sc_time_stamp() <<" Asserting X = 1, Y = 1 and Carry_In = 1 for Full Adder\n" << endl;
	
	sc_start(100,SC_MS);
	cout << "@" << sc_time_stamp() <<" Terminating simulation\n" << endl;
	sc_close_vcd_trace_file(wfHadder);
	sc_close_vcd_trace_file(wfFadder);
	sc_start(100,SC_MS);
	cout << "@" << sc_time_stamp() <<" Terminating simulation2\n" << endl;
	sc_start(100,SC_MS);				// Start the simulation
	sc_stop();

	return 0;
}
	
	
	
