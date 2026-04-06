#include "rk_1.h"
#include <iostream>
#include <stdio.h>
void writeToFile(const char* fileName, const struct Box& box){
	FILE *file;
	file = fopen(fileName,"w");
	fprintf(file,"%i", box._len);
	fprintf(file,"%s","\n");
	fprintf(file,"%i", box._width);
	fprintf(file,"%s","\n");
	fprintf(file,"%i", box._height);
	fprintf(file,"%s","\n");
	fprintf(file,"%i", box._color);
	fprintf(file,"%s","\n");
	fclose(file);
}
void readFromFile(const char* fileName, struct Box& box){
	FILE *file;
    file = fopen(fileName,"r");
    fscanf(file,"%i", &box._len);
    fscanf(file,"%i", &box._width);
    fscanf(file,"%i", &box._height);
    fscanf(file,"%i", &box._color);
    fclose(file);
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