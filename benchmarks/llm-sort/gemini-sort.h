#ifndef GEMINI_SORT_H
#define GEMINI_SORT_H

#include "arr_t.h"

class Gemini {
  public:
    static void bubbleSort(arr_t arr[], int n);
    static void insertionSort(arr_t arr[], int n);
    static void mergeSort(arr_t arr[], int n);
    static void quickSort(arr_t arr[], int n);
    static void heapSort(arr_t arr[], int n);
    static void gnomeSort(arr_t arr[], int n);
    static void radixSort(arr_t arr[], int n);
    static void shellSort(arr_t arr[], int n);
    static void combSort(arr_t arr[], int n);
    static void pancakeSort(arr_t arr[], int n);
};

#endif
