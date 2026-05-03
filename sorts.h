#ifndef _sorts_h_
#define _sorts_h_

#include <iostream>

int getMin_Max(int*,int, bool (*comp)(int,int));
int getMin(int*ar ,int size);
int getMax(int*ar ,int size);
int part(int* ar, int suke, bool (*comp)(int,int));
void merge(int* ar, int suke, int mid, bool (*comp)(int,int));
int isSorted(const int* array, unsigned int size);
void bubbleSort(int* ar, int size, bool (*comp)(int, int));
void selectionSort(int* ar, int size, bool (*comp)(int,int));
void insertionSort(int* ar, int size, bool (*comp)(int,int));
void mergeSort(int* ar, int size, bool (*comp)(int,int));
void quickSort(int* ar, int size, bool (*comp)(int,int));
void sortShell(int* ar, int size, bool (*comp)(int,int));
void countSort(int* ar, int size, bool (*comp)(int,int));
bool comp_asc(int a, int b);
bool comp_des(int a, int b);
#endif