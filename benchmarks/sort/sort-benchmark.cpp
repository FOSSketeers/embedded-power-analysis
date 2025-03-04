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
arr_t arr[256] = { -5685, -7647, 14782, 16017, -2536, 23965, 3548, -17022, -20456, 12096, -746, 25906, 4056, -280, 31020, -90, -3579, 12592, 12773, 9799, 16634, -2622, -19813, 27631, -13924, -13224, -2421, 18072, 28087, -28687, -4592, 17588, 27436, 16542, -24802, -22116, -12969, 15438, 31416, 19163, -7380, 19848, 17630, -23160, -24414, -31428, 27709, -8764, -2077, -13434, 8887, -28491, -15454, 27737, 13177, 4136, 807, -4070, 17431, 12, 19898, 6617, 19000, 196, -7159, 4311, -5189, -3936, 17368, -11971, 16171, -13691, -1106, -31943, 15363, 4094, 22406, -128, -23691, 21531, 18101, 14789, -17173, 12786, -14616, -192, -12935, 6550, -16718, 15004, -17188, 13043, 29424, -5191, -31946, -8727, -19884, 29845, -1439, -11797, -28080, -7004, 18681, 26542, 30540, -27852, -2135, 25716, 18400, 8758, 12532, 32370, -17512, 2742, -26861, -3579, 2293, -31671, 14198, -10501, -7171, -20830, 19145, 27092, 13458, -19488, -13331, -27656, -6104, 7941, -4864, 10139, -15177, -26861, 23236, 30875, 24160, -22142, 3813, 28652, 20916, 26174, 2902, -5108, 9998, 23867, 24322, 10117, -19430, -30809, 23753, -19173, 31608, 14582, -4436, -27072, 21460, -27863, 21313, -4526, 26739, 27677, 12338, -26865, 3689, -25185, -15021, 21293, -8385, -9786, 31963, 4268, 23141, 2696, -31832, 37, -2133, 11717, -28373, 26921, -14575, 4781, -23838, 29511, -15121, -21682, 12280, 27231, 577, 32123, 15209, -15700, 9462, -7714, 22508, 24430, -18856, -6668, -1892, -4739, -93, -26381, -29084, 22841, -17345, -8224, -27269, 18898, -9972, -9199, -25685, 8261, 13401, 24105, -17124, 15365, 16780, -16897, 23253, 7563, 14959, -12669, 27605, -12821, 8790, -32682, 32374, 8482, -5500, -32383, -32135, 26044, -19600, -32545, 1711, 22045, 1881, -8363, -28527, -13251, -3146, -22814, -12015, 5882, 30467, -20819, -4466, -1065, 488, 23257, -22119, -12121, 4317, 30710, -10316, -19930 };
int arr_length = sizeof(arr) / sizeof(arr[0]);
arr_t arr_copy[256];

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
