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
void readFromFile(const char* fileName, struct Box& box){
	FILE *file;
    file = fopen(fileName,"r");
	if(file){
		fscanf(file,"%i %i %i %i", &box._len, &box._width, &box._height, &box._color);
        fclose(file);
	}
}
ostream& operator<<(std::ostream& out, const Box& box) {
	out << " len = " << box._len << ", width = " << box._width << ", height = " << box._height << ", volume = "  << box.volume << "\n" << std::endl; 
	return out;
}
Box::Box(){
	_len = 10;
	_width = 10;
	_height = 10;
	volume = _len*_width*_height;
}
Box::Box(int a){
	_len = a;
	_width = a;
	_height = a;
	volume = _len*_width*_height;
}
Box::Box(int a, int b, int c){
	_len = a;
	_width = b;
	_height = c;
	volume = _len*_width*_height;
}