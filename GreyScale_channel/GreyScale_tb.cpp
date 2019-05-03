#include "systemc.h"
#include "GreyScale.h"
#include "EasyBMP.h"
#include "PixelStack.h"

int sc_main(int argc, char* argv[]) {
	sc_signal<sc_uint<8> > R_tb, G_tb, B_tb, Grey_tb;
	sc_time clockPeriod(10, SC_MS);
	sc_clock clk("sys_clk", clockPeriod, 0.5);
	unsigned int R_temp, G_temp, B_temp;

	BMP testImage, writeImage;
	RGBApixel temp, gsTemp;

	testImage.ReadFromFile("testimage.bmp");
	writeImage.SetSize(testImage.TellWidth(), testImage.TellHeight());

	PixelStack InputChannel_tb("InputChannel_tb");
	PixelStack OutputChannel_tb("OutputChannel_tb");
	GreyScale DUT("DUT");

	DUT.InputChannel(InputChannel_tb);
	DUT.OutputChannel(OutputChannel_tb);
	DUT.Clk(clk);

	sc_trace_file *pTraceFile = sc_create_vcd_trace_file("traceFile");
	sc_trace(pTraceFile, R_tb, "R");
	sc_trace(pTraceFile, G_tb, "G");
	sc_trace(pTraceFile, B_tb, "B");
	sc_trace(pTraceFile, Grey_tb, "Grey");

	for(unsigned int i = 0; i < (unsigned int) testImage.TellWidth(); i++)
	{
		for(unsigned int j = 0; j < (unsigned int) testImage.TellHeight(); j++)
		{

			temp = testImage.GetPixel(i,j);
			InputChannel_tb.nb_write(
					(unsigned int)temp.Red,
					(unsigned int)temp.Green,
					(unsigned int)temp.Blue );
			sc_start(10,SC_MS);

			OutputChannel_tb.nb_read(
					R_temp,
					G_temp,
					B_temp );
			gsTemp.Red   = R_temp;
			gsTemp.Green = G_temp;
			gsTemp.Blue  = B_temp;
			writeImage.SetPixel(i,j,gsTemp);

		}
	}

	writeImage.WriteToFile("result.bmp");

	sc_close_vcd_trace_file(pTraceFile);
	sc_stop();

	return 0;
}
