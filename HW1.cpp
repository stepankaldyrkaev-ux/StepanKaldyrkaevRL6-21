#include "HW1.h"
#include <iostream>
#include <stdio.h>
#include <chrono>
double getTime(enum meas time){
	auto start = std::chrono::steady_clock::now();
    auto dura = start.time_since_epoch();
    switch (time)
    {
	case meas::milli:
		return std::chrono::duration<double,std::milli>(dura).count();
    case meas::micro:
        return std::chrono::duration<double,std::micro>(dura).count();
    case meas::nano:
        return std::chrono::duration<double,std::nano>(dura).count();
    case meas::pico:
        return std::chrono::duration<double,std::pico>(dura).count();
    }
}
void writeStringToFile(const char* fileName, const char* data){
	FILE* f = fopen(fileName, "a");
    if(f)
    {
        fprintf(f,"%s", data);
        fclose(f);
    }
	else{
		std::cout<<"file didn't open";
	}
	delete f;
}
char* convertDoubleToStr(double number){
	char* buf=new char[50];
    std::sprintf(buf,"%.2f",number);
    return buf;
}
char* convertIntToStr(int number){
	char* buf=new char[50];
    std::sprintf(buf,"%d",number);
    return buf;
}
void randomFillAr(int* ar, int size, int min, int max){
	srand(time(NULL));
    for(int i=0;i<size;i++)
    {
        ar[i]=min + rand()%(max-min);
    }
}