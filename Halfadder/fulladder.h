#include "halfadder.h"
#include "oder.h"

SC_MODULE(fulladder)
{
	sc_in<bool> X, Y, Carry_In;												// input signal ports
	sc_out<bool> Sum, Carry_Out;											// output signal ports

	halfadder hadd1, hadd2;													// halfadder instantiation
	oder or1;																// or instantiation

	sc_signal<bool> Sum_Hadd1_Out, Carry_Hadd1_Out, Carry_Hadd2_Out;		// sc_signals to connect the ports internal ("wires")

	SC_CTOR(fulladder) : hadd1("HADD1"), hadd2("HADD2"), or1("OR1")
	{
		hadd1.X(X);
		hadd1.Y(Y);
		hadd1.Carry(Carry_Hadd1_Out);
		hadd1.Sum(Sum_Hadd1_Out);

		hadd2.X(Sum_Hadd1_Out);
		hadd2.Y(Carry_In);
		hadd2.Carry(Carry_Hadd2_Out);
		hadd2.Sum(Sum);

		or1.X(Carry_Hadd1_Out);
		or1.Y(Carry_Hadd2_Out);
		or1.Res(Carry_Out);
	}
};
