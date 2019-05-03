#include "oder.h"

void oder::do_oder()
{
	Res.write( X.read() || Y.read() );											// boolean equation for the SUM
}
