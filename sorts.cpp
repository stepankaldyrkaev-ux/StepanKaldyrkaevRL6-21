#include "sorts.h"

int getMin_Max(int*ar ,int size, bool (*comp)(int,int)){
	int ind_min_max = 0;
	for(int i = 0; i<size;i++){
		if(comp(ar[ind_min_max],ar[i]))
			ind_min_max = i;
	}
	return ind_min_max;
}
int getMin(int*ar ,int size){
	int ind_min = 0;
	for(int i = 0; i<size;i++){
		if(ar[ind_min] > ar[i])
			ind_min = i;
	}
	return ar[ind_min];
}
int getMax(int*ar ,int size){
	int ind_max = 0;
	for(int i = 0; i<size;i++){
		if(ar[ind_max] < ar[i])
			ind_max = i;
	}
	return ar[ind_max];
}
int part(int* ar, int suke, bool (*comp)(int,int)){
	int i = 0;
	int j = suke;
	while(i < j){
		if(!comp(ar[i], ar[j]) && i == j-1){
			std::swap(ar[i], ar[j]);
			j--;
		}
		else if(!comp(ar[i], ar[j])){
			std::swap(ar[j - 1], ar[j]);
			std::swap(ar[i], ar[j]);
			j--;
		}
		else i++;
	}
	return j;
}
void merge(int* ar, int suke, int mid, bool (*comp)(int,int)){
	int* mergedar = new int [suke+1];
	int i, j, k;
	i = 0;
	k = 0;
	j = mid + 1;
	while ((i <= mid)&&(j <= suke)){
		if (comp(ar[i],ar[j])){
			mergedar[k] = ar[i];
			k++;
			i++;
		}
		else{
			mergedar[k] = ar[j];
			k++;
			j++;
		}
	}
	
	while (i <= mid){
		mergedar[k] = ar[i];
		k++;
		i++;
	}
	
	while (j <= suke){
		mergedar[k] = ar[j];
		k++;
		j++;
	}
	for (i = 0; i < k; i++){
		ar[i] = mergedar[i];
	}
	delete[] mergedar;
}
bool comp_asc(int a, int b){
	return(b>=a);
}
bool comp_des(int a, int b){
	return(a>=b);
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

void bubbleSort(int* ar, int size, bool (*comp)(int, int)){
	int s = size;
	while(s--){
		for(int i = 0; i < s; i++){
			if(!comp(ar[i],ar[i + 1]))
				std::swap(ar[i], ar[i + 1]);
		}
	}
}

void selectionSort(int* ar, int size, bool (*comp)(int,int)){
	for(int i=0;i<size;i++){
		int ind = getMin_Max(ar,size - i, comp);
		std::swap(ar[size - i - 1], ar[ind]);
	}
}
void insertionSort(int* ar, int size, bool (*comp)(int,int)){
	for(int i = 1; i < size; i++){
		int j = i - 1;
		while(j >= 0 && comp(ar[j+1],ar[j])){
			std::swap(ar[j], ar[j + 1]);
			j--;
		}
	}
}
void mergeSort(int* ar, int size, bool (*comp)(int,int)){
	int mid=(size-1)/2;
	if ((mid<size)&&(mid>0)){
		mergeSort(&ar[0],mid+1,comp);
		mergeSort(&ar[mid+1],size-mid-1,comp);
		merge(&ar[0],size-1,mid,comp);
	}
	if((mid==0)&&(size==2)){
		merge(&ar[0],size-1,mid,comp);
	}
}
void quickSort(int* ar, int size, bool (*comp)(int,int)){
	int op = part(ar,size-1,comp);
	if(op==0){
		quickSort(&ar[op + 1], size-op-1, comp);
	}
	if(op>0){
		quickSort(&ar[0], op, comp);
		quickSort(&ar[op + 1], size-op-1, comp);
	}
}
void sortShell(int* ar, int size, bool (*comp)(int,int)){
	for(int step = size/2; step > 0; step /= 2)
	{
		for (int i = step; i < size; i += 1)
        {       
			int j = i;
			while((j >= step) &&(!comp(ar[j - step],ar[j])))
			{
				std::swap(ar[j], ar[j - step]);
				j-=step;
			}
        }
	}
}
void countSort(int* ar, int size, bool (*comp)(int,int)){
	int k = getMax(ar,size);
	int min = getMin(ar,size);
	k = k - min;
	int* count = new int [k+1];
	for (int i = 0; i < k+1; i++) {
        count[i] = 0;
    }
	for(int i = 0; i < size; i++){
        count[ar[i] + (min<0? -min : min)]++;
    }
	int i = (comp(0,1)? 0 : k);
	int j = 0;
	while(comp(0,1)? i<k+1 : i>=0){
		while(count[i]>0){
			ar[j] = i + min;
			j++;
			count[i]--;
		}
		(comp(0,1)? i++ : i--);
	}
	delete[] count;
}	
	