#ifndef _HW1_h_
#define _HW1_h_
using namespace std;
#include <iostream>
enum meas {
	milli = 1,
	micro = 2,
	nano = 3,
	pico = 4
};
double getTime(enum meas time);
void writeStringToFile(const char* fileName, const char* data);
char* convertDoubleToStr(double number);
char* convertIntToStr(int number);
void randomFillAr(int* ar, int size, int min = -100, int max = 100);

#endif