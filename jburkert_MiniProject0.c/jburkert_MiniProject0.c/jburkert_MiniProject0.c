#include "binaryutils.h";

void main()
{
	uint32_t solo = 0;
	setbit(&solo, 24);
	/*printf("setbit 24:\n\r");
	display_binary(solo);*/

	setbit(&solo, 16);
	setbit(&solo, 17);
	/*printf("setbit 16 & 17:\n\r");
	display_binary(solo);*/

	setbits(&solo, 4095);
	/*printf("setbits 0 - 11 (4095):\n\r");
	display_binary(solo);*/

	clearbit(&solo, 11);
	/*printf("clearbit 11:\n\r");
	display_binary(solo);*/

	clearbits(&solo, 240);
	/*printf("clearbits 4-7 (240):\n\r");
	display_binary(solo);*/

	//printf("Solo: %d\n", solo);
	printf("Binary Solo:\n\r");
	display_binary(solo);
}