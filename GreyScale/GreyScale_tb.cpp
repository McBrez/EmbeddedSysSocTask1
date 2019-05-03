#include "systemc.h"
#include "GreyScale.h"
#include "EasyBMP.h"

int sc_main(int argc, char* argv[]) {
	sc_signal<sc_uint<8> > R_tb, G_tb, B_tb, Grey_tb;
	sc_time clockPeriod(10, SC_MS);
	sc_clock clk("sys_clk", clockPeriod, 0.5);

	BMP testImage, writeImage;
	RGBApixel temp, gsTemp;

	testImage.ReadFromFile("testimage.bmp");
	writeImage.SetSize(testImage.TellWidth(), testImage.TellHeight());


	GreyScale DUT("DUT");
	DUT.R(R_tb);
	DUT.G(G_tb);
	DUT.B(B_tb);
	DUT.Grey(Grey_tb);
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
			R_tb.write( (int) temp.Red );
			G_tb.write( (int) temp.Green );
			B_tb.write( (int) temp.Blue );
			sc_start(10,SC_MS);

			gsTemp.Red = Grey_tb.read().to_uint();
			gsTemp.Green = Grey_tb.read().to_uint();
			gsTemp.Blue = Grey_tb.read().to_uint();
			writeImage.SetPixel(i,j,gsTemp);

		}
	}

	writeImage.WriteToFile("result.bmp");

	sc_close_vcd_trace_file(pTraceFile);
	sc_stop();

	return 0;
}
