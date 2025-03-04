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
arr_t arr[512] = { -16086, -24526, -6199, -27353, 13069, -16540, 3501, 21175, -183, -28308, 17142, -8361, 22033, 19883, 29524, -10624, 26114, 22696, 20924, -4684, -27928, -11371, 18974, 19630, 18004, -7351, 11748, 26713, -24218, -12561, 20146, 26508, 14036, -14469, 1060, -29930, -27594, -25397, -24053, -30731, -17459, -14992, -4650, -20056, -12052, -22234, -19735, -22064, -22431, 15528, -28320, -31940, 254, -26882, 12119, 17603, 29953, -1318, -11735, -13703, -16617, 12483, 21403, -6329, 27824, -8787, 27953, 8258, -24250, 26985, -16499, 23817, 27428, 5986, -9172, 24790, -25867, -3958, 18303, -23057, -22548, -13907, -9261, 10851, -32702, 23579, -12779, -9009, -24407, 1638, 2311, 16703, -13789, -7329, -15381, -19291, 29780, -29412, 6421, -32554, 733, 19018, 10576, -29742, 18496, -26719, -3224, -8064, 28715, 19629, 11767, 979, -25533, 5302, -11175, 24029, -19788, 27796, 8850, -16970, -15574, -17114, 17523, 22825, 23431, -11260, 1812, 15420, -15458, 25895, 21724, 20698, 23069, -1816, 26363, -31501, 21899, -20205, 18893, -5064, 21445, -18255, -12047, 27146, -28632, 14174, -30073, 17984, 26383, -2192, -2640, 9725, -8661, -17829, 18806, -14014, 31512, -8430, -12378, 5644, -27293, 7295, 4049, -9859, -15066, -29340, 26211, 29355, 19776, -31333, -23468, -3134, 13418, 5796, -9541, -29871, -22813, -21952, 19492, -15745, -7354, -25392, 27840, -14820, -2708, -31555, -25526, -14277, -26061, 12330, -14990, -24014, 14361, 29536, -22943, -27341, 10151, 18305, 16857, 24005, -27920, -16879, 18511, -8083, -21035, 14975, -22522, -27402, -22161, -4174, 7820, 3442, -26364, -4003, 2569, 20499, -27233, -11520, -244, 12315, 1733, 21545, -9092, -31799, -9205, -26515, 2237, -21727, -10133, 31454, 11809, -21680, 25938, -14580, -1465, -12393, 31473, -19799, 9006, 12060, 2597, -29382, -9847, -20950, -5724, 1737, -17213, -3836, 9648, 2288, -18722, 5888, -14823, -27757, -28385, 22047, -1521, 22293, 30994, -455, 5816, 30425, 13114, 30678, -5901, -20257, -8773, 4050, -8580, -12944, -30140, -17467, -17224, -21413, 15075, -29308, 25384, -22665, 7143, -32334, 14991, 6593, -28461, 23362, 19988, 6850, -9036, -22539, -19089, -6138, -24903, -22830, 17848, 13294, -22238, -8906, -3329, 11782, 11300, 935, -15563, 3342, 22614, -15776, 5821, -3711, 30983, -15364, 122, 21628, -28659, 2922, 4003, -27505, -24781, -7547, -2640, 22866, 10949, 31532, 27511, -16179, -7984, 22878, 7551, 18199, -29164, -12606, -19539, 19375, 19100, -4135, 17478, 14746, -16386, 1206, 13661, 31311, 27454, 10525, 21635, 15825, 8396, 2325, 10185, -23070, 15455, -819, -15196, -15512, 30636, 31838, -13066, -10028, 17274, 19264, 14856, 26903, -29207, 3490, -7407, 31566, 618, -12470, -6731, 26382, 20873, -2184, 2448, -5075, -25211, -15414, -7208, -22790, 9472, 23069, -935, 2003, -5130, 20932, -12291, -1814, -23920, -9963, -13184, 25545, -13176, 17835, -16817, -17712, -17008, -12244, -22105, -11141, 14739, -22410, 27631, 27211, -8461, -26859, -1175, 1613, 4844, -673, -27728, -23159, -26699, 17209, 14647, 20203, 11191, 1268, -11814, 2492, 454, 22251, -10425, -16673, -15034, 13138, 1146, -6412, -29104, 20620, -26635, 2741, -18231, -10108, 22076, 400, 23309, -24219, -22286, -9550, -30212, -989, 17083, 27728, -12206, 25633, -7448, 20, 610, 11982, 21736, 22015, 25468, -6122, -30432, -9764, 6751, -1708, 6673, 22533, 4131, -2171, -18947, 15613, 10592, -17766, 3391, 12788, 30096, 2407, -11669, -27974, 5015, -4312, 23452, 2636, 30081, 22046, -23010, -21088, 27919, 24708, 8089, 22094, -16362, 9875, -375, -32383, 14560, -5386, 25112, 25225, 16799, 6572, -15115, 3253, -13997, -21900, 3191, -8380, -220, -14816, -20150, -15100, -6912, 9887, -14534, 13836, 25914, -26997, -6572, 18123, 23850, -14506, 29939, 7595, -27618, -8536 };
int arr_length = sizeof(arr) / sizeof(arr[0]);
arr_t arr_copy[512];

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
