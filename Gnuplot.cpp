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
Gnuplot::Gnuplot(const char* ImageName){
	_ImageName = ImageName;
}
void Gnuplot::buildGraph(CircuitWork* voltage, bool constant, bool Jpeg, bool charge, bool discharge){
	FILE* file = fopen("test.dat", "w");
	double _T = voltage->getPeriod();
	double _stepTime = voltage->getStep();
	const char* v1 = "'test.dat' using 1:4:(2) with lines, 'test.dat' using 1:5:(3) with lines";
	const char* v2 = "'test.dat' using 1:2:(0) with lines, 'test.dat' using 1:3:(1) with lines,'test.dat' using 1:4:(2) with lines, 'test.dat' using 1:5:(3) with lines";
	const char* v3 = "'test.dat' using 1:2:(0) with lines,'test.dat' using 1:3:(1) with lines, 'test.dat' using 1:5:(3) with lines";
	const char* v4 = "'test.dat' using 1:2:(0) with lines,'test.dat' using 1:3:(1) with lines, 'test.dat' using 1:4:(3) with lines";
	const char* v5 = "'test.dat' using 1:2:(0) with lines,'test.dat' using 1:3:(1) with lines";
	const int size = 4*_T/_stepTime;
    for (int i = 0; i < size; i++) {
		double time = i*_stepTime;
        double E1 = voltage->getVoltageE1(time);
        double C1 = voltage->getVoltageC(time);
		double Cha = voltage->getVoltageCharge(time);
        double Dis = voltage->getVoltageDischarge(time);
        fprintf(file, "%f\t%f\t%f\t%f\t%f\n",time, E1, C1, Cha, Dis);
    }
    fclose(file);
	FILE* script = fopen("plot.gp", "w");
    //fprintf(script, "set terminal wxt\n");
	if(Jpeg){
	fprintf(script, "set terminal jpeg size 1024,768\n");
	fprintf(script, "set output '%s.jpg'\n",_ImageName);
	fprintf(script, "set multiplot\n");
    fprintf(script, "set title 'Circuit Work'\n");
	fprintf(script, "set palette defined (0 'green', 1 'blue', 2 'red', 3 'orange')\n");
    fprintf(script, "plot %s\n", (constant==true? v1 : (charge&&discharge == true? v2 : (charge + discharge==false? v5 : (charge==true? v4 : v3)))));
	fprintf(script, "unset multiplot\n");
	fprintf(script, "replot\n");
	}
	fprintf(script, "set terminal wxt\n");
	fprintf(script, "set multiplot\n");
    fprintf(script, "set title 'Circuit Work'\n");
	fprintf(script, "set palette defined (0 'green', 1 'blue', 2 'red', 3 'orange')\n");
    fprintf(script, "plot %s\n", (constant==true? v1 : (charge&&discharge == true? v2 : (charge + discharge==false? v5 : (charge==true? v4 : v3)))));
	fprintf(script, "unset multiplot\n");
    fprintf(script, "pause -1 'Press enter to close window'\n");
    fclose(script);
    system("gnuplot plot.gp");
}