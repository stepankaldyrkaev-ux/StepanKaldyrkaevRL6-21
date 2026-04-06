#ifndef _fraction_h_
#define _fraction_h_
using namespace std;
#include <iostream>
struct Fraction {
	int _numerator;
	int _denominator;
	Fraction(){
		_numerator = 1;
		_denominator = 1;
	}
	Fraction(int numerator, int denominator){
		_numerator = numerator;
		_denominator = denominator;
	}
};
int fracReduction(Fraction& frac);
#endif