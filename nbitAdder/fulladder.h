#include "halfadder.h"
#include "oder.h"

#ifndef FULLADDER_H
#define FULLADDER_H

SC_MODULE(fulladder){
	sc_in<bool> X, Y, Carry_In;												// input signal ports
	sc_out<bool> Sum, Carry_Out;											// output signal ports
	sc_in<bool> Clk;

	halfadder hadd1, hadd2;													// instantiation of two halfadders
	oder or1;																// instantiation of an or

	sc_signal<bool> Sum_Hadd1_Out, Carry_Hadd1_Out, Carry_Hadd2_Out;		// sc_signals to internally connect the ports of the instantiated logic blocks
	sc_signal<bool> Sum_buffer, Carry_out_buffer;

	void do_fulladderOutput();

	SC_CTOR(fulladder) : hadd1("HADD1"), hadd2("HADD2"), or1("OR1")
	{

		hadd1.Carry(Carry_Hadd1_Out);				// connect the ports with the sc_signals ("wires")
		hadd1.Sum(Sum_Hadd1_Out);

		hadd2.X(Sum_Hadd1_Out);
		hadd2.Carry(Carry_Hadd2_Out);

		or1.X(Carry_Hadd1_Out);
		or1.Y(Carry_Hadd2_Out);

		hadd1.X(X);
		hadd1.Y(Y);

		hadd2.Y(Carry_In);
		hadd2.Sum(Sum_buffer);

		or1.Res(Carry_out_buffer);

		SC_METHOD(do_fulladderOutput);
		sensitive << Clk.pos();						// sensitivity of process to a clock

	}
};

#endif
