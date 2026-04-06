#include "rk_1.h"
#include <iostream>
#include <stdio.h>
void writeToFile(const char* fileName, const struct Box& box){
	FILE *file;
	file = fopen(fileName,"w");
	if(file){
		fprintf(file,"%i %i %i %i",box._len,box._width,box._height,box._color);
		fclose(file);
	}
}
void readFromFile(const char* fileName, struct Box* box){
	if(box == NULL){
		return;
	}
	FILE *file;
    file = fopen(fileName,"r");
	if(file){
		fscanf(file,"%i %i %i %i", &box->_len, &box->_width, &box->_height, &box->_color);
        fclose(file);
	}
}
int fracReduction(Fraction& frac){
	int a = abs(frac._numerator);
	int b = abs(frac._denominator);
	while((a!=b)&&(a*b!=0)){
		if(a>b){
			a = a - b;
		}
		else{
			b = b - a;
		}
	}
	if (a*b == 0){
		return -1;
	}
	else{
		frac._numerator = frac._numerator/a;
		frac._denominator = frac._denominator/a;
		return 0;
	}
}
Fraction sum(const Fraction& fr1, const Fraction& fr2){
	Fraction fr3;
	fr3._numerator = fr1._numerator*fr2._denominator + fr2._numerator*fr1._denominator;
	fr3._denominator = fr2._denominator*fr1._denominator;
	int res = fracReduction(fr3);
	return fr3;
}
Fraction sub(const Fraction& fr1, const Fraction& fr2){
	Fraction fr3;
	fr3._numerator = fr1._numerator*fr2._denominator - fr2._numerator*fr1._denominator;
	fr3._denominator = fr2._denominator*fr1._denominator;
	int res = fracReduction(fr3);
	return fr3;
}
Fraction div(const Fraction& fr1, const Fraction& fr2){
	Fraction fr3;
	fr3._numerator = fr1._numerator*fr2._denominator;
	fr3._denominator = fr1._denominator*fr2._numerator;
	int res = fracReduction(fr3);
	return fr3;
}
Fraction mul(const Fraction& fr1, const Fraction& fr2){
	Fraction fr3;
	fr3._numerator = fr1._numerator*fr2._numerator;
	fr3._denominator = fr1._denominator*fr2._denominator;
	int res = fracReduction(fr3);
	return fr3;
}