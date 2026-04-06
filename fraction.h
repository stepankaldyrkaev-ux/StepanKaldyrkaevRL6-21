#ifndef _fraction_h_
#define _fraction_h_
using namespace std;
#include <iostream>
struct Fraction {
	int _numerator;
	int _denominator;
	friend ostream& operator<<(ostream& out, const Fraction& fr){
		return out << fr._numerator << "/" << fr._denominator;
	}
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
Fraction sum(const Fraction& fr1, const Fraction& fr2);
Fraction sub(const Fraction& fr1, const Fraction& fr2);
Fraction div(const Fraction& fr1, const Fraction& fr2);
Fraction mul(const Fraction& fr1, const Fraction& fr2);
#endif