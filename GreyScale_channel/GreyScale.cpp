#include "GreyScale.h"
#include "Interfaces.h"

void GreyScale::doGreyScale() {
	sc_uint<10> sum, R, G, B, quot, rem, divisor;
	unsigned int R_int, G_int, B_int;

	if ( InputChannel->nb_read(R_int, G_int, B_int) ) {
		R = R_int;
		G = G_int;
		B = B_int;

		sum = R + G + B;
		divisor = 3;
		rem = sum;
		quot = 0;

		while( rem >= divisor ) {
			quot++;
			rem = rem- divisor;
		}

		OutputChannel->nb_write(
			quot.range(7,0).to_uint(),
			quot.range(7,0).to_uint(),
			quot.range(7,0).to_uint() );
	}
}
