#include "halfadder.h"


void halfadder::do_halfadder()
{
	Sum.write( ( X.read() && !(Y.read()) ) || ( !(X.read()) && Y.read() ) );		// boolean equation for the SUM
	Carry.write ( X.read() && Y.read() );											// boolean equation for the CARRY
}
