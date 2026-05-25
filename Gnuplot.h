#ifndef _Gnuplot_h_
#define _Gnuplot_h_
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
class Gnuplot {
	private :
	const char* _ImageName; 
	public :
	Gnuplot(const char* ImageName);
	
	void buildGraph(CircuitWork* voltage, bool constant = false, bool Jpeg = false, bool charge = true, bool discharge = true);
};



#endif