#include "file_operations.h"
#include <iostream>
#include <time.h>
#include <stdio.h>
using namespace std;
void fillFile(const char* fileName, int min, int max, char delimeter, int cols, int countElements){
	srand(time(nullptr));
	int a;
	int* ar = new int [countElements];
	for (int i = 0; i < countElements; i++) {
		a = rand();
		a = a%(max+1) + ((a%(max+1))+min > max? 0 : min);
		ar[i]=a;
	}
	FILE *file;
	file = fopen(fileName,"w");
	int str = ((countElements%cols)==0? countElements/cols : countElements/cols + 1);
	int n = 0;
	for (int i = 0; i < str; i++) {
		cols = ((i==(str-1))&&((countElements%cols)!=0)? countElements%cols : cols);
		for (int j = 0; j < cols; j++) {
			fprintf(file,"%i",ar[n]);
			if(j!=(cols-1)){
				fprintf(file,"%c",delimeter);
			}
			n++;
		}
		if(i!=(str-1)){
			fprintf(file,"%s","\n");
		}
	}
	fclose(file);
	delete [] ar;
}