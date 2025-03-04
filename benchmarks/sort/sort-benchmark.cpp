#include <Arduino.h>

#include <util.h>

// Change the array type in arr_t.h
#include "arr_t.h";
#include "sortlib.h";

const int EXPERIMENT_REPETITION = 3;
const int EXPERIMENT_DELAY = 1000;
const int ALGORITHM_DELAY = 500;
const bool SORT_VERIFICATION = false;

// Taken from random_array_generator.py
arr_t arr[128] = { -2213, -6093, -17062, -31292, -14712, 11457, -21368, 7879, 9724, 326, 14866, 30934, 12315, 2606, 27807, -16948, -30266, -22940, 24005, -5721, 24277, 24421, -3472, 31015, -31779, -6821, -13864, -18380, -29531, -20432, -12606, 2803, -12255, -5842, -26291, -9356, -10902, -16206, -4013, 7105, 24216, 32319, 2707, -1568, -30358, 25803, -26260, -21593, -23169, -25998, -14396, -23402, 32595, -1504, -8403, 23454, -28679, 20799, 25007, -17401, -8163, -10112, 4452, -4030, -25615, 11236, 19246, -11662, 28432, -12152, 5524, -28612, 12157, -10705, -29636, -28005, -32605, 10054, -26446, 9763, 15120, -24107, 29691, 15683, 4948, -21906, 11450, -24060, -24889, 30742, 32436, 7971, 1338, 13085, 1414, -28116, -14091, -27462, -18698, -9403, -31766, 24414, 25683, 2875, -2233, -9799, -1, 31144, 21707, -22214, -27677, -22965, 6157, -6165, 7017, -3675, -5140, 1005, 16083, -24996, -7747, 23416, -11392, -3405, -6733, 25664, 28012, 26719 };
int arr_length = sizeof(arr) / sizeof(arr[0]);
arr_t arr_copy[128];

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
