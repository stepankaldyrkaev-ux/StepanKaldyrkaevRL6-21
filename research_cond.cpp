#include "research_cond.h"
#include <iostream>
#include <bitset>
#include <string.h>
#include <cmath>
#include <vector>
#include <utility>
#include <fstream>
#include <cstdio>
double CircuitWork::getVoltageE1(double curTime){
	double palka = 1000;
	double pi = 3.142;
	switch(voltageSource->_signalForm){
		case constV:
		return(voltageSource->_E1);
		break;
		case sinus:
		{
			double E1 = (voltageSource->_E1)*sin((2*pi*curTime)/_T);
			return E1;
		}
		break;
		case triangle:
		{
			double E1;
			if(std::fmod(curTime, _T)<=(_T/2)){
				E1 = (2*(voltageSource->_E1)*2*(std::fmod(curTime, _T)))/_T - voltageSource->_E1;
			}
			if(std::fmod(curTime, _T)>(_T/2)){
				E1 = -((2*(voltageSource->_E1)*2*(std::fmod(curTime, _T)))/_T) + 3*voltageSource->_E1;
			}
			return E1;
		}
		break;
		case sawtooth:
		{
			double E1;
			double x = (2*voltageSource->_E1)/palka;
			if(std::fmod(curTime, _T)<=_T-x){
				E1 = (2*(voltageSource->_E1)*(std::fmod(curTime, _T)))/(_T-x) - voltageSource->_E1;
			}
			if(std::fmod(curTime, _T)>_T-x){
				E1 = (-palka*(std::fmod(curTime, _T))) + voltageSource->_E1 + palka*(_T-x);
			}
			return E1;
		}
		break;
		case halfSinus:
		{
			double E1;
			if(std::fmod(curTime, _T)<=(_T/2)){
				E1 = (voltageSource->_E1)*sin((2*pi*curTime)/_T);
			}
			if(std::fmod(curTime, _T)>(_T/2)){
				E1 = 0;
			}
			return E1;
		}
		break;
		case doubleHalfSinus:
		{
			double E1;
			if(std::fmod(curTime, _T)<=(_T/2)){
				E1 = (voltageSource->_E1)*sin((2*pi*curTime)/_T);
			}
			if(std::fmod(curTime, _T)>(_T/2)){
				E1 = (-1)*(voltageSource->_E1)*sin((2*pi*curTime)/_T);
			}
			return E1;
		}
		break;
		case meandr:
		{
			double E1;
			double x = (voltageSource->_E1)/palka;
			if(std::fmod(curTime, _T)<=x){
				E1 = palka*(std::fmod(curTime, _T));
			}
			if((std::fmod(curTime, _T)>x)&&(std::fmod(curTime, _T)<=(_T/2)-x)){
				E1 = voltageSource->_E1;
			}
			if((std::fmod(curTime, _T)>(_T/2)-x)&&(std::fmod(curTime, _T)<=(_T/2)+x)){
				E1 = (-palka*(std::fmod(curTime, _T))) + voltageSource->_E1 + palka*((_T/2)-x);
			}
			if((std::fmod(curTime, _T)>(_T/2)+x)&&(std::fmod(curTime, _T)<=_T-x)){
				E1 = (-1)*voltageSource->_E1;
			}
			if(std::fmod(curTime, _T)>_T-x){
				E1 = (palka*(std::fmod(curTime, _T))) - voltageSource->_E1 - palka*(_T-x);
			}
			return E1;
		}
	}
}
double CircuitWork::getVoltageCharge(double curTime){
	double VoltageCharge = voltageSource->_E1*(1 - exp(-curTime/(schemeParam->_C1*schemeParam->_R1)));
	return VoltageCharge;
}
double CircuitWork::getVoltageDischarge(double curTime){
	double VoltageDischarge = voltageSource->_E1*exp(-curTime/(schemeParam->_C1*schemeParam->_R2));
	return VoltageDischarge;
}
double CircuitWork::getVoltageC(double curTime){
	int start = integr.size();
	if(curTime<start*_stepTime){
		double res = integr[curTime/_stepTime].second;
		return res;
	}
	double result = (start==0?(this->getVoltageE1(0)*_stepTime)/(schemeParam->_C1*schemeParam->_R1) : integr[start-1].second);
	for(int i = start; i<=(curTime/_stepTime); i++){
		result += ((this->getVoltageE1(i*_stepTime) - result)*_stepTime)/(schemeParam->_C1*schemeParam->_R1);
		integr.push_back(std::pair<double, double>(i*_stepTime, result));
	}
	return result;
}
double CircuitWork::getPeriod(){
	return _T;
}
double CircuitWork::getStep(){
	return _stepTime;
}
CircuitWork* WorkCreate(double C1, double R1, double R2,double E1, enum TypeSignal signal,  double per, double step){
	CircuitWork::ParamCircuit param(C1, R1, R2);
	CircuitWork::ParamVoltSource volt(E1,signal);
	return new CircuitWork(param, volt, per, step);
}