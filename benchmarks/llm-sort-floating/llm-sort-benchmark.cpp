#include <Arduino.h>

#define SERIAL_OUTPUT 0
#include <util.h>

#include "chatgpt-sort.h"
#include "claude-sort.h"
#include "gemini-sort.h"

const int EXPERIMENT_REPETITION = 3;
const int EXPERIMENT_DELAY = 2000;
const int ALGORITHM_DELAY = 1500;
const bool SORT_VERIFICATION = false;

// Taken from random_array_generator.py
float arr[50] = { 163.6878, 112.6001, 175.2774, 125.31, 293.3901, 112.6832, 156.8216, 294.4022, 264.0788, 104.7658, 83.5962, 209.8616, 247.1789, 136.51, 170.0135, 79.0686, 69.5217, 10.6769, 253.0693, 260.8782, 59.7145, 279.2076, 43.7665, 16.6772, 62.031, 211.596, 1.133, 256.1421, 109.6358, 181.0396, 261.5525, 287.6471, 271.5066, 52.3747, 271.8062, 133.0973, 120.1442, 202.4112, 16.5093, 63.639, 163.8315, 162.9567, 174.0054, 196.9813, 274.6218, 157.443, 37.2125, 276.0246, 169.1158, 98.862 };
int arr_length = sizeof(arr) / sizeof(arr[0]);
float arr_copy[50];

void initializeArray() {
    for (int i = 0; i < arr_length; i++) {
        arr_copy[i] = arr[i];
    }
}

void printArray(float arr[]) {
    Serial.print("array: [ ");
    for (int i = 0; i < arr_length; i++) {
        Serial.print(arr[i]);
        Serial.print(", ");
    }
    Serial.println("]");
}

bool verifySorting(float arr[]) {
    for (int i = 0; i < arr_length - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            if constexpr (SERIAL_OUTPUT) {
                Serial.println("VERIF_FAIL: Array is not sorted!");
                Serial.println(arr[i]);
                Serial.println(i);
                printArray(arr);
            }
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
    setState(1, "chatgpt_bubblesort");
    ChatGPT::bubbleSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION)
        verifySorting(arr_copy);
    delay(ALGORITHM_DELAY);

    initializeArray();
    setState(2, "claude_bubblesort");
    Claude::bubbleSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION)
        verifySorting(arr_copy);
    delay(ALGORITHM_DELAY);

    initializeArray();
    setState(3, "gemini_bubblesort");
    Gemini::bubbleSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION)
        verifySorting(arr_copy);
    delay(ALGORITHM_DELAY);

    initializeArray();
    setState(4, "chatgpt_insertionsort");
    ChatGPT::insertionSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION)
        verifySorting(arr_copy);
    delay(ALGORITHM_DELAY);

    initializeArray();
    setState(5, "claude_insertionsort");
    Claude::insertionSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION)
        verifySorting(arr_copy);
    delay(ALGORITHM_DELAY);

    initializeArray();
    setState(6, "gemini_insertionsort");
    Gemini::insertionSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION)
        verifySorting(arr_copy);
    delay(ALGORITHM_DELAY);

    initializeArray();
    setState(7, "chatgpt_mergesort");
    ChatGPT::mergeSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION)
        verifySorting(arr_copy);
    delay(ALGORITHM_DELAY);

    initializeArray();
    setState(8, "claude_mergesort");
    Claude::mergeSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION)
        verifySorting(arr_copy);
    delay(ALGORITHM_DELAY);

    initializeArray();
    setState(9, "gemini_mergesort");
    Gemini::mergeSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION)
        verifySorting(arr_copy);
    delay(ALGORITHM_DELAY);

    initializeArray();
    setState(10, "chatgpt_quicksort");
    ChatGPT::quickSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION)
        verifySorting(arr_copy);
    delay(ALGORITHM_DELAY);

    initializeArray();
    setState(11, "claude_quicksort");
    Claude::quickSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION)
        verifySorting(arr_copy);
    delay(ALGORITHM_DELAY);

    initializeArray();
    setState(12, "gemini_quicksort");
    Gemini::quickSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION)
        verifySorting(arr_copy);
    delay(ALGORITHM_DELAY);

    initializeArray();
    setState(13, "chatgpt_heapsort");
    ChatGPT::heapSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION)
        verifySorting(arr_copy);
    delay(ALGORITHM_DELAY);

    initializeArray();
    setState(14, "claude_heapsort");
    Claude::heapSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION)
        verifySorting(arr_copy);
    delay(ALGORITHM_DELAY);

    initializeArray();
    setState(15, "gemini_heapsort");
    Gemini::heapSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION)
        verifySorting(arr_copy);
    delay(ALGORITHM_DELAY);

    initializeArray();
    setState(16, "chatgpt_gnomesort");
    ChatGPT::gnomeSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION)
        verifySorting(arr_copy);
    delay(ALGORITHM_DELAY);

    initializeArray();
    setState(17, "claude_gnomesort");
    Claude::gnomeSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION)
        verifySorting(arr_copy);
    delay(ALGORITHM_DELAY);

    initializeArray();
    setState(18, "gemini_gnomesort");
    Gemini::gnomeSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION)
        verifySorting(arr_copy);
    delay(ALGORITHM_DELAY);

    initializeArray();
    setState(19, "chatgpt_radixsort");
    ChatGPT::radixSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION)
        verifySorting(arr_copy);
    delay(ALGORITHM_DELAY);

    initializeArray();
    setState(20, "claude_radixsort");
    Claude::radixSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION)
        verifySorting(arr_copy);
    delay(ALGORITHM_DELAY);

    initializeArray();
    setState(21, "gemini_radixsort");
    Gemini::radixSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION)
        verifySorting(arr_copy);
    delay(ALGORITHM_DELAY);

    initializeArray();
    setState(22, "chatgpt_shellsort");
    ChatGPT::shellSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION)
        verifySorting(arr_copy);
    delay(ALGORITHM_DELAY);

    initializeArray();
    setState(23, "claude_shellsort");
    Claude::shellSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION)
        verifySorting(arr_copy);
    delay(ALGORITHM_DELAY);

    initializeArray();
    setState(24, "gemini_shellsort");
    Gemini::shellSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION)
        verifySorting(arr_copy);
    delay(ALGORITHM_DELAY);

    initializeArray();
    setState(25, "chatgpt_combsort");
    ChatGPT::combSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION)
        verifySorting(arr_copy);
    delay(ALGORITHM_DELAY);

    initializeArray();
    setState(26, "claude_combsort");
    Claude::combSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION)
        verifySorting(arr_copy);
    delay(ALGORITHM_DELAY);

    initializeArray();
    setState(27, "gemini_combsort");
    Gemini::combSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION)
        verifySorting(arr_copy);
    delay(ALGORITHM_DELAY);

    initializeArray();
    setState(28, "chatgpt_pancakesort");
    ChatGPT::pancakeSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION)
        verifySorting(arr_copy);
    delay(ALGORITHM_DELAY);

    initializeArray();
    setState(29, "claude_pancakesort");
    Claude::pancakeSort(arr_copy, arr_length);
    setState(0, "idle");
    if (SORT_VERIFICATION)
        verifySorting(arr_copy);
    delay(ALGORITHM_DELAY);

    initializeArray();
    setState(30, "gemini_pancakesort");
    Gemini::pancakeSort(arr_copy, arr_length);
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
