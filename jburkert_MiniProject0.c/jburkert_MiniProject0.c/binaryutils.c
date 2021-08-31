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
	printf("setbits addr = %p\n", addr);
}

void clearbits(uint32_t* addr, uint32_t bitmask)
{
	printf("bitmask = %d\n", bitmask);
	printf("addr = %d\n", *addr);
	bitmask = ~bitmask;
	addr = *addr & bitmask;
	printf("clearbits addr = %p\n", addr);
}

void display_binary(uint32_t num)
{

}
