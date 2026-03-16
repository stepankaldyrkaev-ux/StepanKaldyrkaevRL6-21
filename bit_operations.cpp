#include "bit_operations.h"
void swapHalfWord(unsigned int* words){
	a = *words;
	a = a>>16;
	b = a<<16;
	*words = a+b;
}