//#include <SoftwareSerial.h>
#include <Arduino.h>
#include <stdint.h>

// int rx = 10;
// int tx = 11;
//SoftwareSerial sserial(rx, tx);
#define sserial Serial

const int ARRAY_SIZE = 300;
const int INTERVAL = 1000;

#define arr_t uint16_t

// Test arrays
arr_t array[ARRAY_SIZE];
arr_t temp[ARRAY_SIZE];  // For merge sort

void pinOutput(int x) {
    bool d8 = x & (1 << 0);
    bool d9 = x & (1 << 1);
    bool d10 = x & (1 << 2);
    bool d11 = x & (1 << 3);

    digitalWrite(8, d8);
    digitalWrite(9, d9);
    digitalWrite(10, d10);
    digitalWrite(11, d11);
}

// Function to initialize the array with random values
void initializeArray() {
    unsigned int r = random(1, 10000);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = r & 1023;  // Random numbers between 0 and 9999
        r *= 31;
        r += 79;
        r >>= 3;
        if (!r) r = random(1, 10000);
        // Serial.print(array[i]);
        // Serial.print(" - ");
    }
    // Serial.println();
}

// Bubble Sort
void bubbleSort(arr_t arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                arr_t temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Insertion Sort
void insertionSort(arr_t arr[], int size) {
    for (int i = 1; i < size; i++) {
        arr_t key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Merge Sort
void merge(arr_t arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temp arrays
    for (int i = 0; i < n1; i++) temp[i] = arr[left + i];
    for (int i = 0; i < n2; i++) temp[n1 + i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (temp[i] <= temp[n1 + j]) {
            arr[k++] = temp[i++];
        } else {
            arr[k++] = temp[n1 + j++];
        }
    }

    while (i < n1) arr[k++] = temp[i++];
    while (j < n2) arr[k++] = temp[n1 + j++];
}

void mergeSort(arr_t arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Quick Sort
int partition(arr_t arr[], int low, int high) {
    arr_t pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            arr_t temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    arr_t temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

void quickSort(arr_t arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Heap Sort
void heapify(arr_t arr[], int size, int root) {
    int largest = root;
    int left = 2 * root + 1;
    int right = 2 * root + 2;

    if (left < size && arr[left] > arr[largest]) largest = left;
    if (right < size && arr[right] > arr[largest]) largest = right;

    if (largest != root) {
        arr_t temp = arr[root];
        arr[root] = arr[largest];
        arr[largest] = temp;
        heapify(arr, size, largest);
    }
}

void heapSort(arr_t arr[], int size) {
    for (int i = size / 2 - 1; i >= 0; i--) heapify(arr, size, i);
    for (int i = size - 1; i > 0; i--) {
        arr_t temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

// Gnome Sort
void gnomeSort(arr_t arr[], int size) {
    int index = 0;
    while (index < size) {
        if (index == 0 || arr[index] >= arr[index - 1]) {
            index++;
        } else {
            arr_t temp = arr[index];
            arr[index] = arr[index - 1];
            arr[index - 1] = temp;
            index--;
        }
    }
}

// Radix Sort
void countSortForRadix(arr_t arr[], int size, int exp) {
    arr_t output[size];
    int count[10] = { 0 };

    for (int i = 0; i < size; i++) count[(arr[i] / exp) % 10]++;
    for (int i = 1; i < 10; i++) count[i] += count[i - 1];
    for (int i = size - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    for (int i = 0; i < size; i++) arr[i] = output[i];
}

void radixSort(arr_t arr[], int size) {
    arr_t max = arr[0];
    for (int i = 1; i < size; i++)
        if (arr[i] > max) max = arr[i];
    for (int exp = 1; max / exp > 0; exp *= 10) countSortForRadix(arr, size, exp);
}

// Shell Sort
void shellSort(arr_t arr[], int size) {
    for (int gap = size / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; i++) {
            arr_t temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

// Comb Sort
void combSort(arr_t arr[], int size) {
    int gap = size;
    bool swapped = true;
    while (gap != 1 || swapped) {
        gap = (gap * 10) / 13;
        if (gap < 1) gap = 1;
        swapped = false;
        for (int i = 0; i < size - gap; i++) {
            if (arr[i] > arr[i + gap]) {
                arr_t temp = arr[i];
                arr[i] = arr[i + gap];
                arr[i + gap] = temp;
                swapped = true;
            }
        }
    }
}

// Pancake Sort
int findMax(arr_t arr[], int size) {
    int maxIdx = 0;
    for (int i = 1; i < size; i++) {
        if (arr[i] > arr[maxIdx]) maxIdx = i;
    }
    return maxIdx;
}

void flip(arr_t arr[], int size) {
    for (int i = 0; i < size / 2; i++) {
        arr_t temp = arr[i];
        arr[i] = arr[size - i - 1];
        arr[size - i - 1] = temp;
    }
}

void pancakeSort(arr_t arr[], int size) {
    for (int currSize = size; currSize > 1; currSize--) {
        int maxIdx = findMax(arr, currSize);
        if (maxIdx != currSize - 1) {
            flip(arr, maxIdx + 1);
            flip(arr, currSize);
        }
    }
}


// Benchmark function
void runBenchmark() {
    sserial.println("Starting benchmark...");
    pinOutput(0);

    // Bubble Sort
    initializeArray();
    pinOutput(1);
    sserial.println("Running Bubble Sort...");
    bubbleSort(array, ARRAY_SIZE);
    sserial.println("Sleeping for 1000 ms");
    pinOutput(0);
    delay(INTERVAL);


    // Insertion Sort
    initializeArray();
    pinOutput(2);
    sserial.println("Running Insertion Sort...");
    insertionSort(array, ARRAY_SIZE);
    sserial.println("Sleeping for 1000 ms");
    pinOutput(0);
    delay(INTERVAL);

    // Merge Sort
    initializeArray();
    pinOutput(3);
    sserial.println("Running Merge Sort...");
    mergeSort(array, 0, ARRAY_SIZE - 1);
    sserial.println("Sleeping for 1000 ms");
    pinOutput(0);
    delay(INTERVAL);

    // Quick Sort
    initializeArray();
    pinOutput(4);
    sserial.println("Running Quick Sort...");
    quickSort(array, 0, ARRAY_SIZE - 1);
    sserial.println("Sleeping for 1000 ms");
    pinOutput(0);
    delay(INTERVAL);

    // Heap Sort
    initializeArray();
    pinOutput(5);
    sserial.println("Running Heap Sort...");
    heapSort(array, ARRAY_SIZE);
    sserial.println("Sleeping for 1000 ms");
    pinOutput(0);
    delay(INTERVAL);

    // Gnome Sort
    initializeArray();
    pinOutput(6);
    sserial.println("Running Gnome Sort...");
    gnomeSort(array, ARRAY_SIZE);
    sserial.println("Sleeping for 1000 ms");
    pinOutput(0);
    delay(INTERVAL);

    // Radix Sort
    initializeArray();
    pinOutput(7);
    sserial.println("Running Radix Sort...");
    radixSort(array, ARRAY_SIZE);
    sserial.println("Sleeping for 1000 ms");
    pinOutput(0);
    delay(INTERVAL);

    // Shell Sort
    initializeArray();
    pinOutput(8);
    sserial.println("Running Shell Sort...");
    shellSort(array, ARRAY_SIZE);
    sserial.println("Sleeping for 1000 ms");
    pinOutput(0);
    delay(INTERVAL);

    // Comb Sort
    initializeArray();
    pinOutput(9);
    sserial.println("Running Comb Sort...");
    combSort(array, ARRAY_SIZE);
    sserial.println("Sleeping for 1000 ms");
    pinOutput(0);
    delay(INTERVAL);

    // Pancake Sort
    initializeArray();
    pinOutput(10);
    sserial.println("Running Pancake Sort...");
    pancakeSort(array, ARRAY_SIZE);
    sserial.println("Sleeping for 1000 ms");
    pinOutput(0);
    delay(INTERVAL);

    sserial.println("Benchmark complete!");
}

void setup() {
    // pinMode(rx, INPUT);
    // pinMode(tx, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    sserial.begin(9600);
    // Serial.begin(115200);

    for (int i = 0; i < 5; i++) {
        delay(2000);
        runBenchmark();
    }
    pinOutput(15);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
    // Do nothing
}
