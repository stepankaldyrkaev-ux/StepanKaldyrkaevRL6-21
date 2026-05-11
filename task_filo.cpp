#include <iostream>
#include <bitset>
#include <string.h>
#include "task_filo.h"
#include "filo.h"
bool test_brackets(const char* brackets){
	int size = strlen(brackets);
	int*arr = new int[size];
	for(int i=0; i<size; i++){
		char s = brackets[i];
		if(s=='(')
			arr[i] = 1;
		if(s=='[')
			arr[i] = 2;
		if(s=='{')
			arr[i] = 3;
		if(s=='<')
			arr[i] = 4;
		if(s==')')
			arr[i] = -1;
		if(s==']')
			arr[i] = -2;
		if(s=='}')
			arr[i] = -3;
		if(s=='>')
			arr[i] = -4;
	}
	for(int i=0; i<size; i++){
		std::cout<<arr[i]<<" ";
	}
	FILO filo(size);
	int er, buf;
	for(int i=0; i<size; i++){
		if(arr[i]>0)
			er = filo.putToEnd(arr[i]);
		if(arr[i]<0){
			er = filo.showLastElement(&buf);
			if(((buf+arr[i])!=0)||(er==ErrorFilo::empty))
				return false;
			if((buf+arr[i])==0)
				er = filo.getFromEnd(&buf);
		}
	}
	delete [] arr;
	if(filo.showLastElement(&buf)==ErrorFilo::empty)
		return true;
	else
		return false;
}