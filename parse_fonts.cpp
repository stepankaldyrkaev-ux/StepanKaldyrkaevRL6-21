#include "verdana_8_font.h"
#include "verdana_8_font.c"
#include "parse_fonts.h"
#include <iostream>
#include <bitset>
#include <string.h>
extern const unsigned char  font_verdana_8[FONT_VERDANA_8_ARRAY_LENGTH];
void parse_font(char symbol, char fill, char background){
	int ind = (symbol - 32)*32;
	unsigned char low, high;
	unsigned short res;
	int *ar = new int[16];
    for(int i = 0; i<31; i+=2){
		low = font_verdana_8[ind + i];
		high = font_verdana_8[ind + i + 1];
		res = (high<<8)|low;
		DigToArr(res, ar);
		for(int j = 0; j<16; j++){
		std::cout<<((ar[j]==0)? background : fill);
		}
		std::cout<<"\n";
	}	
}
void DigToArr(unsigned short a, int* arr){
	for(int i = 0; i<16; i++){
		arr[i] = (((a>>i)%2)==0?0:1);
	}
}