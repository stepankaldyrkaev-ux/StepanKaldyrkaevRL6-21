#include "filo.h"
#include "parse_fonts.h"
#include "double_linked_list.h"
#include <iostream>
#include <bitset>
#include <fstream>
#include <string.h>
#include <cstdio>
int main(){
	const char* filename = "C:/Users/stepa/Education/C++_works/current_pulse.bin";
	ProcessPulses pulse(filename);
	DoubleLinkedList list;
	Gnuplot plot;
	plot.buildPulse(pulse.getPulse(7,1), show);
	//std::cout<<pulse.getRiseTime(7);
	plot.buildPulse(pulse.diffPulse(7), show);
	return 0;
}