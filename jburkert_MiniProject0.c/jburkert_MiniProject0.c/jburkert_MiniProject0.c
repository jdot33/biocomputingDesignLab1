#include "binaryutils.h";

void main()
{
	uint32_t solo = 0;
	printf("setbit 24:\n\r");
	setbit(&solo, 24);
	display_binary(solo);

	printf("setbit 16 & 17:\n\r");
	setbit(&solo, 16);
	setbit(&solo, 17);
	display_binary(solo);

	printf("setbits 0 - 11 (4095):\n\r");
	setbits(&solo, 4095);
	display_binary(solo);

	printf("clearbit 11:\n\r");
	clearbit(&solo, 11);
	display_binary(solo);

	printf("clearbits 4-7 (240):\n\r");
	clearbits(&solo, 240);
	display_binary(solo);

	printf("Solo: %d\n", solo);
	printf("Binary Solo:\n\r");
	display_binary(solo);
}