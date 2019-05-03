#include "systemc.h"
#include "fulladder.cpp"

SC_MODULE(nBitAdder){

	sc_core::sc_vector<fulladder> fulladderVec;
	sc_core::sc_vector< sc_in<bool> > A, B;
	sc_in<bool> Clk;
	sc_core::sc_vector< sc_out<bool> > Sum;
	sc_core::sc_vector< sc_signal<bool> > internalCarry;
	sc_in<bool> carryIn;
	sc_out<bool> carryOut;

	nBitAdder(sc_core::sc_module_name, unsigned bitWidth) :
		fulladderVec("fulladders",bitWidth),
		A("A"),
		B("B"),
		Sum("Sum"),
		Clk("Clk"),
		carryIn("carryIn"),
		carryOut("carryOut") {

		A.init(bitWidth);
		B.init(bitWidth);
		Sum.init(bitWidth);
		internalCarry.init(bitWidth);

		for(unsigned int i = 0; i < bitWidth; i++)
		{
			fulladderVec[i].X(A[i]);
			fulladderVec[i].Y(B[i]);
			fulladderVec[i].Clk(Clk);
			fulladderVec[i].Sum(Sum[i]);

			if( i != (bitWidth - 1) )
				fulladderVec[i].Carry_Out(internalCarry[i]);

			if(i == 0)
			{
				fulladderVec[0].Carry_In(carryIn);
				fulladderVec[1].Carry_In(internalCarry[0]);
			}
			else if(i < (bitWidth - 1))
			{
				fulladderVec[i+1].Carry_In(internalCarry[i]);
			}
			else
			{
				fulladderVec[i].Carry_Out(carryOut);
			}
		}

	}
};
