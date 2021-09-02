/*
Joel Burkert
8/31/2021
This project explains how bitwise operators set and clear bits and how they can be used to do simple math.
*/
#pragma once
#include <stdio.h>;
#include <stdint.h>;

#ifndef BINARY_UTILS

#define BINARY_UTILS

void setbit(uint32_t* addr, uint8_t whichbit);
void clearbit(uint32_t* addr, uint8_t whichbit);
void setbits(uint32_t* addr, uint32_t bitmask);
void clearbits(uint32_t* addr, uint32_t bitmask);
void display_binary(uint32_t num);

#endif
