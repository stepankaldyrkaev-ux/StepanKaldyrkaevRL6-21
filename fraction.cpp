#include "fraction.h"
#include <iostream>
#include <stdio.h>
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
ostream& operator<<(ostream& out, const Fraction& fr){
	return out << fr._numerator << "/" << fr._denominator;
}
Fraction::Fraction(){
	_numerator = 1;
	_denominator = 1;
}
Fraction::Fraction(int numerator, int denominator){
	_numerator = numerator;
	_denominator = denominator;
}

