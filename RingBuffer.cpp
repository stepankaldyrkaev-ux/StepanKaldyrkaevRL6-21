#include "RingBuffer.h"
#include <iostream>
RingBuffer::RingBuffer() {
	size = 16;
	buffer = new int [size];
	dataLen = 0;
	pBegin = 0;
	pEnd = pBegin;
}
RingBuffer::RingBuffer(int _size) {
	size = _size;
	buffer = new int [size];
	dataLen = 0;
	pBegin = 0;
	pEnd = pBegin;
}
RingBuffer::~RingBuffer() {
	delete [] buffer;
}
int RingBuffer::pop_front() {
	if (dataLen == 0) {
		return ErrorFilo::empty;
	}

	pBegin++;
	dataLen--;
	if (pBegin == size) {
		pBegin = 0;
	}

	return ErrorFilo::ok;
}
int RingBuffer::pop_back() {
	if (dataLen == 0) {
		return ErrorFilo::empty;
	}

	dataLen--;
	pEnd--;

	if (pEnd < 0) {
		pEnd = size - 1;
	}

	return ErrorFilo::ok;
}
int RingBuffer::push_back(int element) {
	if (dataLen == size) {
		return  ErrorFilo::full;
	}

	buffer[pEnd] = element;
	++pEnd;
	dataLen++;

	if (pEnd == size) {
		pEnd = 0;
	}

	return ErrorFilo::ok;
}
int RingBuffer::push_front(int element) {
	if (dataLen == size) {
		return ErrorFilo::full;
	}
	--pBegin;
	if (pBegin < 0) {
		pBegin = size - 1;
	}
	buffer[pBegin] = element;
	dataLen++;

	return ErrorFilo::ok;
}
int RingBuffer::get_front(int* element){
	if (dataLen == 0) {
		return ErrorFilo::empty;
	}
	int el;
	el = buffer[pBegin];
	*element = el;
	pBegin++;
	dataLen--;
	if (pBegin == size) {
		pBegin = 0;
	}
	
	return ErrorFilo::ok;
}
int RingBuffer::get_back(int* element){
	if (dataLen == 0) {
		return ErrorFilo::empty;
	}
	int el;
	if(pEnd>0){
		el = buffer[pEnd-1];
	}
	if(pEnd==0){
		el = buffer[size-1];
	}
	*element = el;

	dataLen--;
	pEnd--;

	if (pEnd < 0) {
		pEnd = size - 1;
	}

	return ErrorFilo::ok;
}
void RingBuffer::flush(){
	dataLen = 0;
	pBegin = 0;
	pEnd = pBegin;
}
int RingBuffer::resize(int new_size){
	int dif = new_size - size;
	int* buffer_new = new int[new_size];
	if(pBegin<=pEnd){
		for(int i=pBegin; i<pEnd; i++){
			buffer_new[i] = buffer[i];
		}
		delete [] buffer;
		int* buffer = new int[new_size];
		for(int i=pBegin; i<pEnd; i++){
			buffer[i] = buffer_new[i];
		}
	}
	else{
		pBegin = pBegin+dif;
		for(int i=pBegin; i<size; i++){
			buffer_new[i+dif] = buffer[i];
		}
		for(int i=0; i<pEnd; i++){
			buffer_new[i] = buffer[i];
		}
		delete [] buffer;
		int* buffer = new int[new_size];
		pBegin = pBegin + dif;
		for(int i=pBegin; i<new_size; i++){
			buffer[i] = buffer_new[i];
		}
		for(int i=0; i<pEnd; i++){
			buffer[i] = buffer_new[i];
		}
	}
    delete [] buffer_new;
	size = new_size;
}