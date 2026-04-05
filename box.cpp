#include "box.h"
#include <iostream>
#include <stdio.h>
void writeToFile(const char* fileName, const struct Box& box){
	FILE *file;
	file = fopen(fileName,"w");
	fprintf(file,"%i", box._len);
	fprintf(file,"%s","\n");
	fprintf(file,"%i", box._width);
	fprintf(file,"%s","\n");
	fprintf(file,"%i", box._height);
	fprintf(file,"%s","\n");
	fprintf(file,"%i", box._color);
	fprintf(file,"%s","\n");
	fclose(file);
}
void readFromFile(const char* fileName, struct Box& box){
	FILE *file;
    file = fopen(fileName,"r");
    fscanf(file,"%i", &box._len);
    fscanf(file,"%i", &box._width);
    fscanf(file,"%i", &box._height);
    fscanf(file,"%i", &box._color);
    fclose(file);
}