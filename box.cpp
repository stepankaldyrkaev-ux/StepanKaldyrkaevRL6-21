#include "box.h"
#include <iostream>
#include <stdio.h>
void writeToFile(const char* fileName, const struct Box& box){
	FILE *file;
	file = fopen(fileName,"w");
	if(file){
		fprintf(file,"%i %i %i %i",box._len,box._width,box._height,box._color);
		fclose(file);
	}
}
void readFromFile(const char* fileName, struct Box* box){
	if(box == NULL){
		return;
	}
	FILE *file;
    file = fopen(fileName,"r");
	if(file){
		fscanf(file,"%i %i %i %i", &box->_len, &box->_width, &box->_height, &box->_color);
        fclose(file);
	}
}