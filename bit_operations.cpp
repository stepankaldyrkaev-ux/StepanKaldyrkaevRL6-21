#include "bit_operations.h"
#include <iostream>
using namespace std;
void swapHalfWord(unsigned int* words){
	unsigned int a,b;
	a = *words;
	b = *words;
	a = a>>16;
	b = b<<16;
	*words = a+b;
}
void cycleShift(int* number, int N, int left){
	int a;
	int b;
	a = *number;
	a = (a<0? ~(a-1) : a);
	if (left==1){
		for(int i=0; i<N; i++){
			b = ((a>>31)%2==0? 0 : 1);
			a = (a<<1) + b;
		}
	}
	if (left==0){
		for(int i=0; i<N; i++){
			b = (a%2==0? 0 : 1);
			a = (a>>1) + (b<<31);
		}
	}
	*number = (a<0? ~a + 1 : a);
}
int getMaxBit(const int* array, int N){
	int one = 0;
	unsigned int a;
	int ind_max;
	int max = -1;
	for(int i=0; i<N; i++){
		if(array[i]>=0){
			a=array[i];
			for(int j=0; j<32; j++){
				one = one + (a%2==0? 0 : 1);
				a = a>>1;
			}
			ind_max = (max<one? i : ind_max);
			max = (max<one? one : max);
			one = 0;
		}
	}
	if(max = -1)
		return(-1);
	else
		return(ind_max);
}
unsigned char getCount1Bit(int number){
	unsigned char one = 0;
	unsigned int a = number;
	for(int j=0; j<32; j++){
		one = one + (a%2==0? 0 : 1);
		a = a>>1;
	}
	return(one);
}
void cycleShiftArray(int* array, int size, int N, bool left){
	int a;
	int b;
	for(int j=0; j<size; j++){
		a = array[j];
		a = (a<0? ~(a-1) : a);
		if (left==1){
			for(int i=0; i<N; i++){
				b = ((a>>31)%2==0? 0 : 1);
				a = (a<<1) + b;
			}
		}
		if (left==0){
			for(int i=0; i<N; i++){
				b = (a%2==0? 0 : 1);
				a = (a>>1) + (b<<31);
			}
		}
		array[j] = (a<0? ~a + 1 : a);
	}
}