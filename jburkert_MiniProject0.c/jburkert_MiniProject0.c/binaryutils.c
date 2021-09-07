#include "binaryutils.h"

void setbit(uint32_t* addr, uint8_t whichbit)
{
	uint32_t new_addr = 1;
	new_addr = new_addr << whichbit;
	*addr = *addr | new_addr;
}

void clearbit(uint32_t* addr, uint8_t whichbit)
{
	uint32_t new_addr = 1;
	new_addr = new_addr << whichbit;
	new_addr = ~new_addr;
	*addr = *addr & new_addr;
}

void setbits(uint32_t* addr, uint32_t bitmask)
{
	*addr = *addr | bitmask;
}

void clearbits(uint32_t* addr, uint32_t bitmask)
{
	bitmask = ~bitmask;
	*addr = *addr & bitmask;
}

void display_binary(uint32_t num)
{
	uint32_t num1 = num;
	int temp = 0;
	char binary[128];
	for (unsigned i= (1 << 31); i > 0; i = i/2) { //dividing i by 2 is the same as shifting i to the right 1 bit. therefor every iteration is just comparing a 1 to a index of num and if they are both one then 1 gets added to array "binary"
		binary[temp++] = (num & i) ? '1' : '0'; //if i'th bit is greater than 0 then it must be a one, if not set to 0
	}
	binary[temp] = '\0';
	printf("%s\n", binary);
}
