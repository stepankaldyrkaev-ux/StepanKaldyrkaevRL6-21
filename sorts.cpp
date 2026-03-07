#include "sorts.h"

int getMin(int*ar, int size){
	int ind_min = 0;
	for(int i = 0; i<size;i++){
		if(ar[ind_min]>ar[i])
			ind_min = i;
	}
	return ind_min;
}
void selectionSort(int* ar, unsigned int size, bool asc){
	for(int i=0;i<size;i++){
		int ind_Min = getMin(&ar[asc==true? i : 0],size - i);
		std::swap(ar[asc==true? i : size - i - 1], ar[asc==true? ind_Min + i : ind_Min]);
	}
}
int isSorted(int* ar, unsigned int size){
	unsigned int ar_up,ar_down;
    int n;
    ar_up = 0;
    ar_down = 0;
    for(unsigned int i=0;i<size-1;i++){
        n = ar[i]-ar[i+1];
        ar_up = ar_up + (n<=0? 1 : 0);
        ar_down = ar_down + (n>=0? 1 : 0);
    }
    if(ar_up==size-1)
        n = 1;
    if(ar_down==size-1)
        n = -1;
    if((ar_up!=size-1)&&(ar_down!=size-1))
        n=0;
    return n;
}	
	