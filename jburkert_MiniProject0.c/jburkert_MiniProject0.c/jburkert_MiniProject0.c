#include "binaryutils.h";

void main()
{
	uint32_t solo = 9;

	//setbit(&solo, 24);
	//clearbit(&solo, 0);
	//setbits(&solo, 3584);
	clearbits(&solo, 8);
	display_binary(solo);
}