#ifndef _box_h_
#define _box_h_
using namespace std;
#include <iostream>
struct Box {
	static int _count;
	int _name;
	int _len;
	int _width;
	int _height;
	int _color;
	int volume;
	Box(){
		_count++;
		_name = _count;
		_len = 10;
		_width = 10;
		_height = 10;
		volume = _len*_width*_height;
	}
	Box(int a){
		_count++;
		_name = _count;
		_len = a;
		_width = a;
		_height = a;
		volume = _len*_width*_height;
	}
	Box(int a, int b, int c){
		_count++;
		_name = _count;
		_len = a;
		_width = b;
		_height = c;
		volume = _len*_width*_height;
	}
	~Box(){
		if(_name==_count){
			_count--;
		}
	}
	friend ostream& operator<<(std::ostream& out, const Box& box) {
		if(box.volume>=0){
			out << "[" << box._name << "] = {" << box._height << "," << box._len << ","  << box._width << "} = " << box.volume << std::endl;
		}
        else{
			out << "v<0"<< std::endl;
		}		
	return out;
	}
};
void writeToFile(const char* fileName, const struct Box& box);
void readFromFile(const char* fileName, struct Box& box);

#endif