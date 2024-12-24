#include <Arduino.h>

#include <util.h>

// Change the array type in arr_t.h
#include "arr_t.h";
#include "sortlib.h";

const int EXPERIMENT_REPETITION = 3;
const int EXPERIMENT_DELAY = 1500;
const int ALGORITHM_DELAY = 1000;
const bool SORT_VERIFICATION = false;

// Taken from random_array_generator.py
arr_t arr[100] = { -107, -105, -261, 278, -14, -59, 267, -7, 82, -209, 133, 189, 93, -53, 57, 79, 133, 30, 125, -299, 250, 265, 198, -57, -262, -216, 27, -286, -17, -207, 34, -136, 252, 23, -97, 201, 260, -197, 259, 81, -133, 208, 169, 81, 211, 138, 21, 161, 223, -53, -227, 300, -252, 277, 27, 34, 67, -29, 296, -247, -203, -116, -217, 6, 273, 90, -178, 226, -172, 82, 220, 122, 119, -134, 268, -188, -213, 257, 220, -154, 89, -241, 65, -254, -56, 225, -230, -34, 205, -162, 154, 148, 208, -287, 8, 134, 280, 39, 293, 131 };
int arr_length = sizeof(arr) / sizeof(arr[0]);
arr_t arr_copy[100];

void initializeArray() {
    for (int i = 0; i < arr_length; i++) {
        arr_copy[i] = arr[i];
    }
}

bool verifySorting(arr_t arr[]) {
    for (int i = 0; i < arr_length - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            if constexpr (SERIAL_OUTPUT)
                Serial.println("VERIF_FAIL: Array is not sorted!");
            return false;
        }
    }
    return true;
}

void runBenchmark() {
    if constexpr (SERIAL_OUTPUT)
        Serial.println("Starting benchmark...");
    setState(0, "idle");

    initializeArray();
    setState(1, "bubblesort");
    bubbleSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION)
        verifySorting(arr_copy);
    delay(ALGORITHM_DELAY);

    initializeArray();
    setState(2, "insertionsort");
    insertionSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION)
        verifySorting(arr_copy);
    delay(ALGORITHM_DELAY);

    initializeArray();
    setState(3, "mergesort");
    mergeSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION)
        verifySorting(arr_copy);
    delay(ALGORITHM_DELAY);

    initializeArray();
    setState(4, "quicksort");
    quickSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION)
        verifySorting(arr_copy);
    delay(ALGORITHM_DELAY);

    initializeArray();
    setState(5, "heapsort");
    heapSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION)
        verifySorting(arr_copy);
    delay(ALGORITHM_DELAY);

    initializeArray();
    setState(6, "gnomesort");
    gnomeSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION)
        verifySorting(arr_copy);
    delay(ALGORITHM_DELAY);

    initializeArray();
    setState(7, "radixsort");
    radixSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION)
        verifySorting(arr_copy);
    delay(ALGORITHM_DELAY);

    initializeArray();
    setState(8, "shellsort");
    shellSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION)
        verifySorting(arr_copy);
    delay(ALGORITHM_DELAY);

    initializeArray();
    setState(9, "combsort");
    combSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION)
        verifySorting(arr_copy);
    delay(ALGORITHM_DELAY);

    initializeArray();
    setState(10, "pancakesort");
    pancakeSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION)
        verifySorting(arr_copy);
    delay(ALGORITHM_DELAY);

    if constexpr (SERIAL_OUTPUT)
        Serial.println("Benchmark complete!");
}

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    _CommonInitializer();
    for (int i = 0; i < EXPERIMENT_REPETITION; i++) {
        delay(EXPERIMENT_DELAY);
        runBenchmark();
    }

    setState(255, "finish");
    digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
    // put your main code here, to run repeatedly:
}
