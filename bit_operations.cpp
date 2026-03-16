#include "bit_operations.h"
void swapHalfWord(unsigned int* words){
	unsigned int a,b;
	a = *words;
	b = *words;
	a = a>>16;
	b = b<<16;
	*words = a+b;
}