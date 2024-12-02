// #include "SoftwareSerial.h"
#include <Arduino.h>

#include <util.h>

#include "chatgpt-sort.h"
#include "claude-sort.h"
#include "gemini-sort.h"

const int EXPERIMENT_REPETITION = 1;
const int EXPERIMENT_DELAY = 2000;
const int ALGORITHM_DELAY = 1500;
const bool SORT_VERIFICATION = false;

// Taken from random_array_generator.py
int arr[100] = { -107, -105, -261, 278, -14, -59, 267, -7, 82, -209, 133, 189, 93, -53, 57, 79, 133, 30, 125, -299, 250, 265, 198, -57, -262, -216, 27, -286, -17, -207, 34, -136, 252, 23, -97, 201, 260, -197, 259, 81, -133, 208, 169, 81, 211, 138, 21, 161, 223, -53, -227, 300, -252, 277, 27, 34, 67, -29, 296, -247, -203, -116, -217, 6, 273, 90, -178, 226, -172, 82, 220, 122, 119, -134, 268, -188, -213, 257, 220, -154, 89, -241, 65, -254, -56, 225, -230, -34, 205, -162, 154, 148, 208, -287, 8, 134, 280, 39, 293, 131 };
int arr_length = sizeof(arr) / sizeof(arr[0]);
int arr_copy[100];

void initializeArray() {
    for (int i = 0; i < arr_length; i++) {
        arr_copy[i] = arr[i];
    }
}

bool verifySorting(int arr[]) {
    for (int i = 0; i < arr_length - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            if constexpr (SERIAL_OUTPUT) Serial.println("VERIF_FAIL: Array is not sorted!");
            return false;
        }
    }
    return true;
}

void runBenchmark() {
    if constexpr (SERIAL_OUTPUT) Serial.println("Starting benchmark...");
    setState(0, "idle");

    if constexpr (SERIAL_OUTPUT) Serial.println("-------------------");
    if constexpr (SERIAL_OUTPUT) Serial.println("----- ChatGPT -----");
    if constexpr (SERIAL_OUTPUT) Serial.println("-------------------");

    initializeArray();
    if constexpr (SERIAL_OUTPUT) Serial.println("Running Bubble Sort...");
    setState(1, "chatpt_bubblesort");
    ChatGPT::bubbleSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    if constexpr (SERIAL_OUTPUT) Serial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    if constexpr (SERIAL_OUTPUT) Serial.println("Running Insertion Sort...");
    setState(2, "chatgpt_insertionsort");
    ChatGPT::insertionSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    if constexpr (SERIAL_OUTPUT) Serial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    if constexpr (SERIAL_OUTPUT) Serial.println("Running Merge Sort...");
    setState(3, "chatgpt_mergesort");
    ChatGPT::mergeSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    if constexpr (SERIAL_OUTPUT) Serial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    if constexpr (SERIAL_OUTPUT) Serial.println("Running Quick Sort...");
    setState(4, "chatgpt_quicksort");
    ChatGPT::quickSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    if constexpr (SERIAL_OUTPUT) Serial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    if constexpr (SERIAL_OUTPUT) Serial.println("Running Heap Sort...");
    setState(5, "chatgpt_heapsort");
    ChatGPT::heapSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    if constexpr (SERIAL_OUTPUT) Serial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    if constexpr (SERIAL_OUTPUT) Serial.println("Running Gnome Sort...");
    setState(6, "chatgpt_gnomesort");
    ChatGPT::gnomeSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    if constexpr (SERIAL_OUTPUT) Serial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    if constexpr (SERIAL_OUTPUT) Serial.println("Running Radix Sort...");
    setState(7, "chatgpt_radixsort");
    ChatGPT::radixSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    if constexpr (SERIAL_OUTPUT) Serial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    if constexpr (SERIAL_OUTPUT) Serial.println("Running Shell Sort...");
    setState(8, "chatgpt_shellsort");
    ChatGPT::shellSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    if constexpr (SERIAL_OUTPUT) Serial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    if constexpr (SERIAL_OUTPUT) Serial.println("Running Comb Sort...");
    setState(9, "chatgpt_combsort");
    ChatGPT::combSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    if constexpr (SERIAL_OUTPUT) Serial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    if constexpr (SERIAL_OUTPUT) Serial.println("Running Pancake Sort...");
    setState(10, "chatgpt_pancakesort");
    ChatGPT::pancakeSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    if constexpr (SERIAL_OUTPUT) Serial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    if constexpr (SERIAL_OUTPUT) Serial.println("-------------------");
    if constexpr (SERIAL_OUTPUT) Serial.println("------ Gemini -----");
    if constexpr (SERIAL_OUTPUT) Serial.println("-------------------");

    initializeArray();
    if constexpr (SERIAL_OUTPUT) Serial.println("Running Bubble Sort...");
    setState(11, "gemini_bubblesort");
    Gemini::bubbleSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    if constexpr (SERIAL_OUTPUT) Serial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    if constexpr (SERIAL_OUTPUT) Serial.println("Running Insertion Sort...");
    setState(12, "gemini_insertionsort");
    Gemini::insertionSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    if constexpr (SERIAL_OUTPUT) Serial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    if constexpr (SERIAL_OUTPUT) Serial.println("Running Merge Sort...");
    setState(13, "gemini_mergesort");
    Gemini::mergeSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    if constexpr (SERIAL_OUTPUT) Serial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    if constexpr (SERIAL_OUTPUT) Serial.println("Running Quick Sort...");
    setState(14, "gemini_quicksort");
    Gemini::quickSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    if constexpr (SERIAL_OUTPUT) Serial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    if constexpr (SERIAL_OUTPUT) Serial.println("Running Heap Sort...");
    setState(15, "gemini_heapsort");
    Gemini::heapSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    if constexpr (SERIAL_OUTPUT) Serial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    if constexpr (SERIAL_OUTPUT) Serial.println("Running Gnome Sort...");
    setState(16, "gemini_gnomesort");
    Gemini::gnomeSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    if constexpr (SERIAL_OUTPUT) Serial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    if constexpr (SERIAL_OUTPUT) Serial.println("Running Radix Sort...");
    setState(17, "gemini_radixsort");
    Gemini::radixSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    if constexpr (SERIAL_OUTPUT) Serial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    if constexpr (SERIAL_OUTPUT) Serial.println("Running Shell Sort...");
    setState(18, "gemini_shellsort");
    Gemini::shellSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    if constexpr (SERIAL_OUTPUT) Serial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    if constexpr (SERIAL_OUTPUT) Serial.println("Running Comb Sort...");
    setState(19, "gemini_combsort");
    Gemini::combSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    if constexpr (SERIAL_OUTPUT) Serial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    if constexpr (SERIAL_OUTPUT) Serial.println("Running Pancake Sort...");
    setState(20, "gemini_pancakesort");
    Gemini::pancakeSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    if constexpr (SERIAL_OUTPUT) Serial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    if constexpr (SERIAL_OUTPUT) Serial.println("-------------------");
    if constexpr (SERIAL_OUTPUT) Serial.println("------ Claude -----");
    if constexpr (SERIAL_OUTPUT) Serial.println("-------------------");

    initializeArray();
    if constexpr (SERIAL_OUTPUT) Serial.println("Running Bubble Sort...");
    setState(21, "claude_bubblesort");
    Claude::bubbleSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    if constexpr (SERIAL_OUTPUT) Serial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    if constexpr (SERIAL_OUTPUT) Serial.println("Running Insertion Sort...");
    setState(22, "claude_insertionsort");
    Claude::insertionSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    if constexpr (SERIAL_OUTPUT) Serial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    if constexpr (SERIAL_OUTPUT) Serial.println("Running Merge Sort...");
    setState(23, "claude_mergesort");
    Claude::mergeSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    if constexpr (SERIAL_OUTPUT) Serial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    if constexpr (SERIAL_OUTPUT) Serial.println("Running Quick Sort...");
    setState(24, "claude_quicksort");
    Claude::quickSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    if constexpr (SERIAL_OUTPUT) Serial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    if constexpr (SERIAL_OUTPUT) Serial.println("Running Heap Sort...");
    setState(25, "claude_heapsort");
    Claude::heapSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    if constexpr (SERIAL_OUTPUT) Serial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    if constexpr (SERIAL_OUTPUT) Serial.println("Running Gnome Sort...");
    setState(26, "claude_gnomesor");
    Claude::gnomeSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    if constexpr (SERIAL_OUTPUT) Serial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    if constexpr (SERIAL_OUTPUT) Serial.println("Running Radix Sort...");
    setState(27, "claude_radixsort");
    Claude::radixSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    if constexpr (SERIAL_OUTPUT) Serial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    if constexpr (SERIAL_OUTPUT) Serial.println("Running Shell Sort...");
    setState(28, "claude_shellsort");
    Claude::shellSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    if constexpr (SERIAL_OUTPUT) Serial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    if constexpr (SERIAL_OUTPUT) Serial.println("Running Comb Sort...");
    setState(29, "claude_combsort");
    Claude::combSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    if constexpr (SERIAL_OUTPUT) Serial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    initializeArray();
    if constexpr (SERIAL_OUTPUT) Serial.println("Running Pancake Sort...");
    setState(30, "claude_pancakesort");
    Claude::pancakeSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION) verifySorting(arr_copy);
    if constexpr (SERIAL_OUTPUT) Serial.println("Going to sleep...");
    delay(ALGORITHM_DELAY);

    if constexpr (SERIAL_OUTPUT) Serial.println("Benchmark complete!");
}

void setup() {
    for (int i = 0; i < EXPERIMENT_REPETITION; i++) {
        delay(EXPERIMENT_DELAY);
        runBenchmark();
    }

    setState(255, "finish");
}

void loop() {
    // put your main code here, to run repeatedly:
}
