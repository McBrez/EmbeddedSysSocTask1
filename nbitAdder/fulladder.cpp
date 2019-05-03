#include "systemc.h"
#include "halfadder.cpp"
#include "oder.cpp"

SC_MODULE(fulladder){
	sc_in<bool> X, Y, Carry_In;																	// input signal ports
	sc_out<bool> Sum, Carry_Out;																// output signal ports
	sc_in<bool> Clk;
	
	halfadder hadd1, hadd2;
	oder or1;
	
	sc_signal<bool> Sum_Hadd1_Out, Carry_Hadd1_Out, Carry_Hadd2_Out;
	sc_signal<bool> Sum_buffer, Carry_out_buffer;
	
	void do_fulladderOutput()
	{
		Sum.write(Sum_buffer.read());
		Carry_Out.write(Carry_out_buffer.read());
	}

	SC_CTOR(fulladder) : hadd1("HADD1"), hadd2("HADD2"), or1("OR1")
	{

		hadd1.Carry(Carry_Hadd1_Out);
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
		sensitive << Clk.pos();

	}
};
		
