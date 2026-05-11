#ifndef _filo_h_
#define _filo_h_

#include <iostream>
enum ErrorFilo {
	ok = 0,
	empty = 1,
	full = 2,
};

class FILO {
	private :
		int* buffer;
		int size;
		int dataLen;

	public :
		FILO();
		FILO(int size);
		~FILO();

		int putToEnd(int element);
		int getFromEnd(int* element);
		int showLastElement(int* element) const;
		void flush();

		void showElements() const;
};
#endif