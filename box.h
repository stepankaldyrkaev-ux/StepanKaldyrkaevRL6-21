#ifndef _box_h_
#define _box_h_
using namespace std;
#include <iostream>
struct Box {
	int _len;
	int _width;
	int _height;
	int _color;
	int _volume;
	Box(){
		_len = 10;
		_width = 10;
		_height = 10;
		_volume = _len*_width*_height;
	}
	Box(int a){
		_len = a;
		_width = a;
		_height = a;
		_volume = _len*_width*_height;
	}
	Box(int a, int b, int c){
		_len = a;
		_width = b;
		_height = c;
		_volume = _len*_width*_height;
	}
	friend ostream& operator<<(std::ostream& out, const Box& box) {
	out << " len = " << box._len << ", width = " << box._width << ", height = " << box._height << ", volume = "  << box._volume << "\n" << std::endl; 
	return out;
	}
};
void writeToFile(const char* fileName, const struct Box& box);
void readFromFile(const char* fileName, struct Box* box);

#endif