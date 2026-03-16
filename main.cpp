#include "sorts.h"
int main(){
	int ar[] = {1,4,8,2,5,-3,9,4,1};
	selectionSort(ar, 9, true);
	std::cout << "Отсортированный массив по возрастанию:";
	for(int i =0;i<9;i++){
		std::cout << ar[i]<< std::endl;;
	}
	selectionSort(ar, 9, false);
	std::cout << "Отсортированный массив по убыванию:";
	for(int i =0;i<9;i++){
		std::cout << ar[i]<< std::endl;;
	}
	return 0;
}