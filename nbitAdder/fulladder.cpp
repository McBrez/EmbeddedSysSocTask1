#include "fulladder.h"

void fulladder::do_fulladderOutput()
{
	Sum.write(Sum_buffer.read());
	Carry_Out.write(Carry_out_buffer.read());
}
