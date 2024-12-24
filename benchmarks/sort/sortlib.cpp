#include "sortlib.h"

// 1. Bubble Sort

void bubbleSort(arr_t arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// 2. Insertion Sort

void insertionSort(arr_t arr[], int n) {
    for (int i = 1; i < n; i++) {
        arr_t key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// 3. Merge Sort

void mergeSort(arr_t arr[], int n) {
    if (n < 2) return;

    int mid = n / 2;
    arr_t left[mid], right[n - mid];

    for (int i = 0; i < mid; i++) left[i] = arr[i];
    for (int i = mid; i < n; i++) right[i - mid] = arr[i];

    mergeSort(left, mid);
    mergeSort(right, n - mid);

    int i = 0, j = 0, k = 0;
    while (i < mid && j < n - mid) {
        if (left[i] <= right[j]) arr[k++] = left[i++];
        else arr[k++] = right[j++];
    }
    while (i < mid) arr[k++] = left[i++];
    while (j < n - mid) arr[k++] = right[j++];
}

// 4. Quick Sort

static void quickSortHelper(arr_t arr[], int low, int high) {
    if (low < high) {
        arr_t pivot = arr[high], i = low - 1;
        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) {
                i++;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        arr_t temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;

        int pi = i + 1;
        quickSortHelper(arr, low, pi - 1);
        quickSortHelper(arr, pi + 1, high);
    }
}

void quickSort(arr_t arr[], int n) {
    quickSortHelper(arr, 0, n - 1);
}

// 5. Heap Sort

static void heapify(arr_t arr[], int n, int i) {
    int largest = i, left = 2 * i + 1, right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;

    if (largest != i) {
        arr_t temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void heapSort(arr_t arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        arr_t temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

// 6. Gnome Sort

void gnomeSort(arr_t arr[], int n) {
    int i = 0;
    while (i < n) {
        if (i == 0 || arr[i] >= arr[i - 1]) i++;
        else {
            arr_t temp = arr[i];
            arr[i] = arr[i - 1];
            arr[i - 1] = temp;
            i--;
        }
    }
}

// 7. Radix Sort
static void countSort(arr_t arr[], int n, int exp) {
    arr_t output[n], count[10] = { 0 };

    for (int i = 0; i < n; i++) count[(arr[i] / exp) % 10]++;
    for (int i = 1; i < 10; i++) count[i] += count[i - 1];
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    for (int i = 0; i < n; i++) arr[i] = output[i];
}


static void _radixSort(arr_t arr[], int n) {
    arr_t max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max) max = arr[i];

    for (int exp = 1; max / exp > 0; exp *= 10) countSort(arr, n, exp);
}

void radixSort(arr_t arr[], int n) {
    // Separate negative and positive numbers
    arr_t negatives[n], positives[n];
    int negCount = 0, posCount = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] < 0) negatives[negCount++] = -arr[i];
        else positives[posCount++] = arr[i];
    }

    // Sort negatives and positives independently
    if (negCount > 0) _radixSort(negatives, negCount);
    if (posCount > 0) _radixSort(positives, posCount);

    // Merge sorted negatives (reversed) and positives into the original array
    int idx = 0;
    for (int i = negCount - 1; i >= 0; i--) arr[idx++] = -negatives[i];
    for (int i = 0; i < posCount; i++) arr[idx++] = positives[i];
}

// 8. Shell Sort

void shellSort(arr_t arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            arr_t temp = arr[i], j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

// 9. Comb Sort

void combSort(arr_t arr[], int n) {
    int gap = n;
    bool swapped = true;

    while (gap > 1 || swapped) {
        gap = (gap * 10) / 13;
        if (gap < 1) gap = 1;
        swapped = false;
        for (int i = 0; i + gap < n; i++) {
            if (arr[i] > arr[i + gap]) {
                arr_t temp = arr[i];
                arr[i] = arr[i + gap];
                arr[i + gap] = temp;
                swapped = true;
            }
        }
    }
}

// 10. Pancake Sort

static void flip(arr_t arr[], int n) {
    for (int i = 0, j = n - 1; i < j; i++, j--) {
        arr_t temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

void pancakeSort(arr_t arr[], int n) {
    for (int i = n; i > 1; i--) {
        int maxIdx = 0;
        for (int j = 1; j < i; j++) {
            if (arr[j] > arr[maxIdx]) maxIdx = j;
        }
        if (maxIdx != i - 1) {
            flip(arr, maxIdx + 1);
            flip(arr, i);
        }
    }
}
