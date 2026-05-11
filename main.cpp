#include "HW1.h"
#include "sorts.h"
#include "RingBuffer.h"
#include <iostream>
#include <bitset>
#include <string.h>
int main(int argc, char* argv[]){
	double max_time=1000;
	int min_size=50;
	int max_size=300;
	int step_size=40;
	if(argc>2){
		for(int i=0;i<argc;i++){
			if(strcmp("--max_time", argv[i])==0)
				max_time = atoi(argv[i+1]);
			if(strcmp("--min_size", argv[i])==0)
				min_size = atoi(argv[i+1]);
			if(strcmp("--max_size", argv[i])==0)
				max_size = atoi(argv[i+1]);
			if(strcmp("--step_size", argv[i])==0)
				step_size = atoi(argv[i+1]);
		}
	}
	int* out_time = new int[7];
	for(int i = 0; i<7; i++){
		out_time[i] = 0;
	}
	const char* buffer[7] = {"---", "---", "---", "---", "---", "---", "---"};
	char file_name[] = "C:/Users/stepa/Education/C++_works/test.txt";
	FILE* f = fopen(file_name, "w");
    if(f)
    {
        fprintf(f,"%s", "\n");
        fclose(f);
    }
	else{
		std::cout<<"file didn't open";
	}
	for(int size=min_size; size<=max_size ;size = size + step_size){
		writeStringToFile(file_name, convertIntToStr(size));
		writeStringToFile(file_name, "\t");
		if(out_time[0]==0){
			int *ar = new int[size];
			randomFillAr(ar, size);
			double start = getTime(milli);
			bubbleSort(ar, size ,comp_asc);
			double end = getTime(milli);
			delete[] ar;
			double clock = end - start;
			out_time[0]=(clock<=max_time? 0 : 1);
			buffer[0]=(out_time[0]==1? "---" : convertDoubleToStr(clock));
		}
		if(out_time[1]==0){
			int *ar = new int[size];
			randomFillAr(ar, size);
			double start = getTime(milli);
			selectionSort(ar, size ,comp_asc);
			double end = getTime(milli);
			delete[] ar;
			double clock = end - start;
			out_time[1]=(clock<=max_time? 0 : 1);
			buffer[1]=(out_time[1]==1? "---" : convertDoubleToStr(clock));
		}
		if(out_time[2]==0){
			int *ar = new int[size];
			randomFillAr(ar, size);
			double start = getTime(milli);
			insertionSort(ar, size ,comp_asc);
			double end = getTime(milli);
			delete[] ar;
			double clock = end - start;
			out_time[2]=(clock<=max_time? 0 : 1);
			buffer[2] = (out_time[2]==1? "---" : convertDoubleToStr(clock));
		}
		if(out_time[3]==0){
			int *ar = new int[size];
			randomFillAr(ar, size);
			double start = getTime(milli);
			mergeSort(ar, size ,comp_asc);
			double end = getTime(milli);
			delete[] ar;
			double clock = end - start;
			out_time[3]=(clock<=max_time? 0 : 1);
			buffer[3] = (out_time[3]==1? "---" : convertDoubleToStr(clock));
		}
		if(out_time[4]==0){
			int *ar = new int[size];
			randomFillAr(ar, size);
			double start = getTime(milli);
			quickSort(ar, size ,comp_asc);
			double end = getTime(milli);
			delete[] ar;
			double clock = end - start;
			out_time[4]=(clock<=max_time? 0 : 1);
			buffer[4] = (out_time[4]==1? "---" : convertDoubleToStr(clock));
		}
		if(out_time[5]==0){
			int *ar = new int[size];
			randomFillAr(ar, size);
			double start = getTime(milli);
			sortShell(ar, size ,comp_asc);
			double end = getTime(milli);
			delete[] ar;
			double clock = end - start;
			out_time[5]=(clock<=max_time? 0 : 1);
			buffer[5] = (out_time[5]==1? "---" : convertDoubleToStr(clock));
		}
		if(out_time[6]==0){
			int *ar = new int[size];
			randomFillAr(ar, size);
			double start = getTime(milli);
			countSort(ar, size ,comp_asc);
			double end = getTime(milli);
			delete[] ar;
			double clock = end - start;
			out_time[6]=(clock<=max_time? 0 : 1);
			buffer[6] = (out_time[6]==1? "---" : convertDoubleToStr(clock));
		}
		for(int j=0;j<7;j++){
			writeStringToFile(file_name, buffer[j]);
			writeStringToFile(file_name, "\t");
		}
		writeStringToFile(file_name, "\n");
	}
	return 0;
}