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
	*number = a;
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
	if (left==1){
		for(int i=0; i<N; i++){
			for(int j = 0; j<size; j++){
				if(j==0)
					a = ((array[j]>>31)%2==0? 0 : 1);
				array[j] = (array[j]<<1) + ((j==size-1)? a : ((array[j+1]>>31)%2==0? 0 : 1));	
			}
		}
	}
	if (left==0){
		for(int i=0; i<N; i++){
			for(int j = size-1; j>=0; j--){
				if(j==size-1)
					a = (array[j]%2==0? 0<<31 : 1<<31);
				array[j] = (array[j]>>1) + ((j==0)? a : (array[j-1]%2==0? 0<<31 : 1<<31));	
			}
		}
	}
}
void setBit(int* number, int numBit){
	*number = *number|(1<<numBit);
}
void clearBit(int* number, int numBit){
	*number = ((*number>>numBit)%2==1? *number - (1<<numBit) : *number); 
}
bool isPalindromNumber(const int number){
	unsigned int n1 = number;
	unsigned int n2 = 0;
	for(int i = 0; i < 16; i++){
		n2 = n2 + ((n1>>i)%2==1? abs((1<<(31-i))) : 0) + ((n1>>(31-i))%2==1? abs((1<<i)) : 0);
	}
	std::cout << hex<< n2 << "\n";
	if((n1-n2)==0)
		return 1;
	else
		return 0;
}