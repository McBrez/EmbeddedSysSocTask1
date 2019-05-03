#include "fulladder.h"

#ifndef NBITADDER_H
#define NBITADDER_H

SC_MODULE(nBitAdder){

	sc_vector<fulladder> fulladderVec;							// sc_vector of type fulladderVec
	sc_vector< sc_in<bool> > A, B;				                // input ports for two n-bit vectors
	sc_in<bool> Clk;							                // clock input
	sc_vector< sc_out<bool> > Sum;				                // output ports for Sum
	sc_vector< sc_signal<bool> > internalCarry;	                // internal sc_signal connections ("wires")
	sc_in<bool> carryIn;						                // input port for the carry
	sc_out<bool> carryOut;						                // output for the carry

	nBitAdder(sc_core::sc_module_name, unsigned bitWidth) :		// constructor for the nBitAdder
		fulladderVec("fulladders",bitWidth),
		A("A"),
		B("B"),
		Sum("Sum"),
		Clk("Clk"),
		carryIn("carryIn"),
		carryOut("carryOut") {

		A.init(bitWidth);										// initialise the sc_vectors with the desired bitWidth
		B.init(bitWidth);
		Sum.init(bitWidth);
		internalCarry.init(bitWidth);

		for(unsigned int i = 0; i < bitWidth; i++)				// Connect the internal carry out signals from the one fulladder carry out to the next fulladder carry in
		{
			fulladderVec[i].X(A[i]);							// Associate input and output ports of the single fulladders with the above defined sc_ins and sc_outs
			fulladderVec[i].Y(B[i]);
			fulladderVec[i].Clk(Clk);
			fulladderVec[i].Sum(Sum[i]);

			if( i != (bitWidth - 1) )
				fulladderVec[i].Carry_Out(internalCarry[i]);

			if(i == 0)											// Special case first and last fulladder: carry in -> carry in of the first fulladder
			{
				fulladderVec[0].Carry_In(carryIn);
				fulladderVec[1].Carry_In(internalCarry[0]);
			}
			else if(i < (bitWidth - 1))
			{
				fulladderVec[i+1].Carry_In(internalCarry[i]);	// carry out of the last fulladder -> carry in of the next fulladder
			}
			else
			{
				fulladderVec[i].Carry_Out(carryOut);			// carry out of the last fulladder -> carry out
			}
		}

	}
};

#endif
