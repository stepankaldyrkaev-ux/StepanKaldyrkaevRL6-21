#include "sorts.h"

int getMin(int*ar, int size){
	int ind_min = 0;
	for(int i = 0; i<size;i++){
		if(ar[ind_min]>ar[i])
			ind_min = i;
	}
	return ind_min;
}
	