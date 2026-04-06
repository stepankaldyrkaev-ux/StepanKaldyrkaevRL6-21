#ifndef _box_h_
#define _box_h_
using namespace std;
#include <iostream>
struct Box {
	int _len;
	int _width;
	int _height;
	int _color;
};
void writeToFile(const char* fileName, const struct Box& box);
void readFromFile(const char* fileName, struct Box& box);

#endif