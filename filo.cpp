#include "filo.h"
#include <iostream>
FILO::FILO() {
	buffer = new int [16];
	size = 16;
	dataLen = 0;
}

FILO::FILO(int _size) {
	buffer = new int [_size];
	size = _size;
	dataLen = 0;
}

FILO::~FILO() {
	delete [] buffer;
}

int FILO::putToEnd(int element) {
	if (dataLen >= size) {
		return ErrorFilo::full;
	}

	buffer[dataLen++] = element;

	return ErrorFilo::ok;
}

int FILO::getFromEnd(int* element) {
	if (dataLen == 0) {
		if (element != nullptr) {
			*element = -1;
		}
		return ErrorFilo::empty;
	}	

	if (element == nullptr) {
		dataLen--;
		return ErrorFilo::ok;
	}
	*element = buffer[--dataLen];

	return ErrorFilo::ok;
}
int FILO::showLastElement(int* element) const {
	if (dataLen == 0) {
		if (element != nullptr) {
			*element = -1;
		}
		return ErrorFilo::empty;
	}
	
	if (element == nullptr) {
		return ErrorFilo::ok;
	}
	*element = buffer[dataLen-1];
	
	return ErrorFilo::ok;
}
void FILO::flush() {
	dataLen = 0;
}

void FILO::showElements() const {
	std::cout << "{";
	for (int i = 0; i < dataLen; std::cout << buffer[i++] << ", ");
	std::cout << "}" << std::endl;
}