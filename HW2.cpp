#include "Gnuplot.h"
#include "research_cond.h"
#include <iostream>
#include <bitset>
#include <string.h>
#include <cmath>
#include <vector>
#include <utility>
#include <fstream>
#include <cstdio>
struct Prist{
	double p = pow(10,-12);
	double n = pow(10,-9);
	double u = pow(10,-6);
	double k = pow(10,3);
	double m = pow(10,6);
	double g = pow(10,9);
};
double Pristavochka(char s){
	Prist Pr;
	if(std::isdigit(s))
		return 1;
	switch(s){
		case 'p':
		return(Pr.p);
		break;
		case 'n':
		return(Pr.n);
		break;
		case 'u':
		return(Pr.u);
		break;
		case 'k':
		return(Pr.k);
		break;
		case 'm':
		return(Pr.m);
		break;
		case 'g':
		return(Pr.g);
		break;
	}
};
int main(int argc, char* argv[]){
	enum TypeSignal signal = sinus;
	Gnuplot plot;
	double R1 = 1000;
	double R2 = 10;
	double C1 = 0.001;
	double E1 = 10;
	double stepTime = 0.001;
	double T = 8*3.142;
	bool jpeg = false;
	bool charge = true;
	bool discharge = true;
	bool constant = false;
	if(argc>1){
		for(int i=0;i<argc;i++){
			const char* buf = argv[i];
			double chis;
			if(strncmp("-R1=", argv[i],4)==0){
				char* end;
				chis = strtod(&buf[4], &end);
				R1 = chis*(Pristavochka(buf[strlen(argv[i])-1]));
			}
			if(strncmp("-R2=", argv[i],4)==0){
				char* end;
				chis = strtod(&buf[4], &end);
				R2 = chis*(Pristavochka(buf[strlen(argv[i])-1]));
			}
			if(strncmp("-C1=", argv[i],4)==0){
				char* end;
				chis = strtod(&buf[4], &end);
				C1 = chis*(Pristavochka(buf[strlen(argv[i])-1]));
			}
			if(strncmp("--signal=", argv[i],9)==0){
				if(strcmp(&buf[9], "sin")==0)
					signal = sinus;
				if(strcmp(&buf[9], "constV")==0){
					signal = constV;
					constant = true;
				}
				if(strcmp(&buf[9], "meandr")==0)
					signal = meandr;
				if(strcmp(&buf[9], "triangle")==0)
					signal = triangle;
				if(strcmp(&buf[9], "sawtooth")==0)
					signal = sawtooth;
				if(strcmp(&buf[9], "halfSinus")==0)
					signal = halfSinus;
				if(strcmp(&buf[9], "doubleHalfSinus")==0)
					signal = doubleHalfSinus;
			}
			if(strncmp("-E1=", argv[i],4)==0){
				char* end;
				chis = strtod(&buf[4], &end);
				E1 = chis*(Pristavochka(buf[strlen(argv[i])-1]));
			}
			if(strncmp("--step=", argv[i],7)==0){
				char* end;
				chis = strtod(&buf[7], &end);
				stepTime = chis*(Pristavochka(buf[strlen(argv[i])-1]));
			}
			if(strncmp("--jpeg=", argv[i],7)==0)
				jpeg = (strcmp(&buf[7], "true")==0? true : false);
			if(strncmp("-T=", argv[i],3)==0){
				char* end;
				chis = strtod(&buf[3], &end);
				T = chis*(Pristavochka(buf[strlen(argv[i])-1]));
			}
			if(strncmp("--charge=", argv[i],9)==0){
				charge = (strcmp(&buf[9], "false")==0? false : true);
			}
			if(strncmp("--discharge=", argv[i],12)==0){
				discharge = (strcmp(&buf[12], "false")==0? false : true);
			}
		}
	}
	CircuitWork* circuit = WorkCreate(C1, R1, R2, E1, signal, T, stepTime);
	plot.buildGraph(circuit,constant,jpeg,charge,discharge);
	return 1;
}