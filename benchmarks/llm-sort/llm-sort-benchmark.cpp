// #include "SoftwareSerial.h"
#include <Arduino.h>
#include "chatgpt-sort.h"
#include "claude-sort.h"
#include "gemini-sort.h"

// const int rx = 10;
// const int tx = 11;
// SoftwareSerial sserial(rx, tx);
#define sserial Serial


const int EXPERIMENT_REPETITION = 1;
const int EXPERIMENT_DELAY = 2000;
const int END_DELAY = 2000;
const int ALGORITHM_DELAY = 1500;
const bool SORT_VERIFICATION = false;

// Taken from random_array_generator.py
int arr[100] = { -107, -105, -261, 278, -14, -59, 267, -7, 82, -209, 133, 189, 93, -53, 57, 79, 133, 30, 125, -299, 250, 265, 198, -57, -262, -216, 27, -286, -17, -207, 34, -136, 252, 23, -97, 201, 260, -197, 259, 81, -133, 208, 169, 81, 211, 138, 21, 161, 223, -53, -227, 300, -252, 277, 27, 34, 67, -29, 296, -247, -203, -116, -217, 6, 273, 90, -178, 226, -172, 82, 220, 122, 119, -134, 268, -188, -213, 257, 220, -154, 89, -241, 65, -254, -56, 225, -230, -34, 205, -162, 154, 148, 208, -287, 8, 134, 280, 39, 293, 131 };
int arr_length = sizeof(arr) / sizeof(arr[0]);
int arr_copy[100];

void pinOutput(int x) {
    bool d8 = x & (1 << 0);
    bool d9 = x & (1 << 1);
    bool d10 = x & (1 << 2);
    bool d11 = x & (1 << 3);
    bool d12 = x & (1 << 4);

    digitalWrite(8, d8);
    digitalWrite(9, d9);
    digitalWrite(10, d10);
    digitalWrite(11, d11);
    digitalWrite(12, d12);
}

void initializeArray() {
    for (int i = 0; i < arr_length; i++) {
        arr_copy[i] = arr[i];
    }
}

bool verifySorting(int arr[]) {
    for (int i = 0; i < arr_length - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            sserial.println("VERIF_FAIL: Array is not sorted!");
            return false;
        }
    }
    return true;
}

void runBenchmark() {
    sserial.println("Starting benchmark...");
    pinOutput(0);

    sserial.println("-------------------");
    sserial.println("----- ChatGPT -----");
    sserial.println("-------------------");

    initializeArray();
    sserial.println("Running Bubble Sort...");
    pinOutput(1);
    ChatGPT::bubbleSort(arr_copy, arr_length);
    pinOutput(0);
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    sserial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    sserial.println("Running Insertion Sort...");
    pinOutput(2);
    ChatGPT::insertionSort(arr_copy, arr_length);
    pinOutput(0);
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    sserial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    sserial.println("Running Merge Sort...");
    pinOutput(3);
    ChatGPT::mergeSort(arr_copy, arr_length);
    pinOutput(0);
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    sserial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    sserial.println("Running Quick Sort...");
    pinOutput(4);
    ChatGPT::quickSort(arr_copy, arr_length);
    pinOutput(0);
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    sserial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    sserial.println("Running Heap Sort...");
    pinOutput(5);
    ChatGPT::heapSort(arr_copy, arr_length);
    pinOutput(0);
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    sserial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    sserial.println("Running Gnome Sort...");
    pinOutput(6);
    ChatGPT::gnomeSort(arr_copy, arr_length);
    pinOutput(0);
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    sserial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    sserial.println("Running Radix Sort...");
    pinOutput(7);
    ChatGPT::radixSort(arr_copy, arr_length);
    pinOutput(0);
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    sserial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    sserial.println("Running Shell Sort...");
    pinOutput(8);
    ChatGPT::shellSort(arr_copy, arr_length);
    pinOutput(0);
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    sserial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    sserial.println("Running Comb Sort...");
    pinOutput(9);
    ChatGPT::combSort(arr_copy, arr_length);
    pinOutput(0);
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    sserial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    sserial.println("Running Pancake Sort...");
    pinOutput(10);
    ChatGPT::pancakeSort(arr_copy, arr_length);
    pinOutput(0);
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    sserial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    sserial.println("-------------------");
    sserial.println("------ Gemini -----");
    sserial.println("-------------------");

    initializeArray();
    sserial.println("Running Bubble Sort...");
    pinOutput(11);
    Gemini::bubbleSort(arr_copy, arr_length);
    pinOutput(0);
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    sserial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    sserial.println("Running Insertion Sort...");
    pinOutput(12);
    Gemini::insertionSort(arr_copy, arr_length);
    pinOutput(0);
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    sserial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    sserial.println("Running Merge Sort...");
    pinOutput(13);
    Gemini::mergeSort(arr_copy, arr_length);
    pinOutput(0);
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    sserial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    sserial.println("Running Quick Sort...");
    pinOutput(14);
    Gemini::quickSort(arr_copy, arr_length);
    pinOutput(0);
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    sserial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    sserial.println("Running Heap Sort...");
    pinOutput(15);
    Gemini::heapSort(arr_copy, arr_length);
    pinOutput(0);
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    sserial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    sserial.println("Running Gnome Sort...");
    pinOutput(16);
    Gemini::gnomeSort(arr_copy, arr_length);
    pinOutput(0);
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    sserial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    sserial.println("Running Radix Sort...");
    pinOutput(17);
    Gemini::radixSort(arr_copy, arr_length);
    pinOutput(0);
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    sserial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    sserial.println("Running Shell Sort...");
    pinOutput(18);
    Gemini::shellSort(arr_copy, arr_length);
    pinOutput(0);
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    sserial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    sserial.println("Running Comb Sort...");
    pinOutput(19);
    Gemini::combSort(arr_copy, arr_length);
    pinOutput(0);
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    sserial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    sserial.println("Running Pancake Sort...");
    pinOutput(20);
    Gemini::pancakeSort(arr_copy, arr_length);
    pinOutput(0);
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    sserial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    sserial.println("-------------------");
    sserial.println("------ Claude -----");
    sserial.println("-------------------");

    initializeArray();
    sserial.println("Running Bubble Sort...");
    pinOutput(21);
    Claude::bubbleSort(arr_copy, arr_length);
    pinOutput(0);
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    sserial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    sserial.println("Running Insertion Sort...");
    pinOutput(22);
    Claude::insertionSort(arr_copy, arr_length);
    pinOutput(0);
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    sserial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    sserial.println("Running Merge Sort...");
    pinOutput(23);
    Claude::mergeSort(arr_copy, arr_length);
    pinOutput(0);
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    sserial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    sserial.println("Running Quick Sort...");
    pinOutput(24);
    Claude::quickSort(arr_copy, arr_length);
    pinOutput(0);
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    sserial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    sserial.println("Running Heap Sort...");
    pinOutput(25);
    Claude::heapSort(arr_copy, arr_length);
    pinOutput(0);
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    sserial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    sserial.println("Running Gnome Sort...");
    pinOutput(26);
    Claude::gnomeSort(arr_copy, arr_length);
    pinOutput(0);
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    sserial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    sserial.println("Running Radix Sort...");
    pinOutput(27);
    Claude::radixSort(arr_copy, arr_length);
    pinOutput(0);
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    sserial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    sserial.println("Running Shell Sort...");
    pinOutput(28);
    Claude::shellSort(arr_copy, arr_length);
    pinOutput(0);
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    sserial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    sserial.println("Running Comb Sort...");
    pinOutput(29);
    Claude::combSort(arr_copy, arr_length);
    pinOutput(0);
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    sserial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    sserial.println("Running Pancake Sort...");
    pinOutput(30);
    Claude::pancakeSort(arr_copy, arr_length);
    pinOutput(0);
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    sserial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    sserial.println("Benchmark complete!");
}

void setup() {
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(12, OUTPUT);
    sserial.begin(9600);

    for (int i = 0; i < EXPERIMENT_REPETITION; i++) {
        delay(EXPERIMENT_DELAY);
        runBenchmark();
    }

    pinOutput(31);
}

void loop() {
    // put your main code here, to run repeatedly:
}
