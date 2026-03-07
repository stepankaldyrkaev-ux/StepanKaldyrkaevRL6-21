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
	