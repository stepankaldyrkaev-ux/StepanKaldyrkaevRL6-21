#include "filo.h"
#include "parse_fonts.h"
#include "double_linked_list.h"
#include <iostream>
#include <bitset>
#include <fstream>
#include <string.h>
#include <cstdio>
/*int main(){
	const char* filename = "C:/Users/stepa/Education/C++_works/current_pulse.bin";
	ProcessPulses pulse(filename);
	DoubleLinkedList list;
	Gnuplot plot;
	plot.buildPulse(pulse.getPulse(7,1), show);
	//std::cout<<pulse.getRiseTime(7);
	plot.buildPulse(pulse.diffPulse(7), show);
	return 0;
}*/
int main(int argc, char* argv[]){
	const char* filename = "C:/Users/stepa/Education/C++_works/current_pulse.bin";
	ProcessPulses pulse(filename);
	DoubleLinkedList list;
	Gnuplot plot;
	bool diff = false;
	bool aver = false;
	bool normal = false;
	int numNode = 1;
	int start = 10;
	int end = 90;
	int kolNode = 3;
	enum SaveTo save = show;
	if(argc>2){
		for(int i=0;i<argc;i++){
			if(strcmp("--diff", argv[i])==0)
				diff = (strcmp("true", argv[i+1])==0? true : false);
			if(strcmp("--number", argv[i])==0)
				numNode = atoi(argv[i+1]);
			if(strcmp("--aver", argv[i])==0)
				aver = (strcmp("true", argv[i+1])==0? true : false);
			if(strcmp("--start", argv[i])==0)
				start = atoi(argv[i+1]);
			if(strcmp("--end", argv[i])==0)
				end = atoi(argv[i+1]);
			if(strcmp("--normalize", argv[i])==0)
				normal = (strcmp("true", argv[i+1])==0? true : false);
			if(strcmp("--kolNode", argv[i])==0)
				kolNode = atoi(argv[i+1]);
			if(strcmp("--SaveTo", argv[i])==0){
				if(strcmp("png", argv[i+1])==0)
					save = png;
				if(strcmp("jpeg", argv[i+1])==0)
					save = jpeg;
				if(strcmp("show", argv[i+1])==0)
					save = show;
			}
		}
	}
	plot.buildPulse(pulse.getPulse(numNode,normal), save, "Pulse");
	if(diff){
		plot.buildPulse(pulse.diffPulse(numNode), save, "Diff_Pulse");
	}
	if(aver){
		plot.buildPulse(pulse.averPulse(numNode, kolNode), save, "Aver_Pulse");
	}
	std::cout<<"Rise time duration: "<<pulse.getRiseTime(numNode)<<"\n";
	std::cout<<"Fail time duration: "<<pulse.getFailTime(numNode)<<"\n";
	std::cout<<"Duration of pulse from "<<start<<"% to "<<end<<"%: "<<pulse.getDurPulse(numNode,start,end)<<"\n";
	std::cout<<"Integration of pulse from "<<start<<"% to "<<end<<"%: "<<pulse.intPulse(numNode,start,end)<<"\n";
}