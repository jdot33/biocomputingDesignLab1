#include "binaryutils.h"

void setbit(uint32_t* addr, uint8_t whichbit)
{
	uint32_t new_addr = 1;

	printf("new_addr = %d\n", new_addr);
	printf("addr = %d\n", *addr);

	new_addr = new_addr << whichbit;
	addr = *addr | new_addr;
	printf("setbit addr = %d\n", addr);
}

void clearbit(uint32_t* addr, uint8_t whichbit)
{
	uint32_t new_addr = 1;

	printf("new_addr = %d\n", new_addr);
	printf("addr = %d\n", *addr);

	new_addr = new_addr << whichbit;
	new_addr = ~new_addr;
	addr = *addr & new_addr;
	printf("clearbit addr = %d\n", addr);
}

void setbits(uint32_t* addr, uint32_t bitmask)
{
	printf("bitmask = %d\n", bitmask);
	printf("addr = %d\n", *addr);

	addr = *addr | bitmask;
	printf("setbits addr = %d\n", addr);
}

void clearbits(uint32_t* addr, uint32_t bitmask)
{
	printf("bitmask = %d\n", bitmask);
	printf("addr = %d\n", *addr);
	bitmask = ~bitmask;
	addr = *addr & bitmask;
	printf("clearbits addr = %d\n", addr);
	
}

void display_binary(uint32_t num)
{
	uint32_t num1 = num;
	int size = sizeof(num);
	printf("%d\n", num1);
	printf("Size: %d\n", size);
	for (int i=0; i < 32; i++) {
		// print last bit and shift left.
		printf("%u ", num);
		num = num << 1;
	}
}
