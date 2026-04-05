#include "fraction.h"
#include <iostream>
#include <stdio.h>
int fracReduction(Fraction& frac){
	int a = abs(frac._numerator);
	int b = abs(frac._denominator);
	while((a!=b)&&(a!=0)){
		if(a>b){
			a = a - b;
		}
		else{
			b = b - a;
		}
	}
	if (a == 0){
		return -1;
	}
	else{
		frac._numerator = frac._numerator/a;
		frac._denominator = frac._denominator/a;
		return 0;
	}
}