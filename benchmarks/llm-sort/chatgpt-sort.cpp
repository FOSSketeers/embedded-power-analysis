#include "chatgpt-sort.h"

// 1. Bubble Sort

/**
 * Bubble Sort: Repeatedly swaps adjacent elements if they are in the wrong order.
 * 
 * @param arr[] Array of integers to be sorted.
 * @param n Size of the array.
 */
void ChatGPT::bubbleSort(int arr[], int n) {
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

/**
 * Insertion Sort: Builds the sorted array one element at a time.
 * 
 * @param arr[] Array of integers to be sorted.
 * @param n Size of the array.
 */
void ChatGPT::insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// 3. Merge Sort

/**
 * Merge Sort: Divides the array into halves, sorts each half, and merges them.
 * 
 * @param arr[] Array of integers to be sorted.
 * @param n Size of the array.
 */
void ChatGPT::mergeSort(int arr[], int n) {
    if (n < 2) return;

    int mid = n / 2;
    int left[mid], right[n - mid];

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

/**
 * Quick Sort: Divides the array around a pivot, sorting each partition recursively.
 * 
 * @param arr[] Array of integers to be sorted.
 * @param n Size of the array.
 */
static void quickSortHelper(int arr[], int low, int high) {
    if (low < high) {
        int pivot = arr[high], i = low - 1;
        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) {
                i++;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        int temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;

        int pi = i + 1;
        quickSortHelper(arr, low, pi - 1);
        quickSortHelper(arr, pi + 1, high);
    }
}

void ChatGPT::quickSort(int arr[], int n) {
    quickSortHelper(arr, 0, n - 1);
}

// 5. Heap Sort

static void heapify(int arr[], int n, int i) {
    int largest = i, left = 2 * i + 1, right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;

    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

/**
 * Heap Sort: Turns the array into a max-heap and sorts by repeatedly removing the root.
 * 
 * @param arr[] Array of integers to be sorted.
 * @param n Size of the array.
 */
void ChatGPT::heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

// 6. Gnome Sort

/**
 * Gnome Sort: Moves back to correct mistakes while sorting sequentially.
 * 
 * @param arr[] Array of integers to be sorted.
 * @param n Size of the array.
 */
void ChatGPT::gnomeSort(int arr[], int n) {
    int i = 0;
    while (i < n) {
        if (i == 0 || arr[i] >= arr[i - 1]) i++;
        else {
            int temp = arr[i];
            arr[i] = arr[i - 1];
            arr[i - 1] = temp;
            i--;
        }
    }
}

// 7. Radix Sort
static void countSort(int arr[], int n, int exp) {
    int output[n], count[10] = { 0 };

    for (int i = 0; i < n; i++) count[(arr[i] / exp) % 10]++;
    for (int i = 1; i < 10; i++) count[i] += count[i - 1];
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    for (int i = 0; i < n; i++) arr[i] = output[i];
}


static void _radixSort(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max) max = arr[i];

    for (int exp = 1; max / exp > 0; exp *= 10) countSort(arr, n, exp);
}

/**
 * Radix Sort: Sorts integers digit by digit using counting sort as a subroutine.
 * 
 * @param arr[] Array of integers to be sorted.
 * @param n Size of the array.
 */
void ChatGPT::radixSort(int arr[], int n) {
    // Separate negative and positive numbers
    int negatives[n], positives[n];
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

/**
 * Shell Sort: Sorts elements at intervals, reducing the gap each iteration.
 * 
 * @param arr[] Array of integers to be sorted.
 * @param n Size of the array.
 */
void ChatGPT::shellSort(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i], j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

// 9. Comb Sort

/**
 * Comb Sort: Improves Bubble Sort by eliminating turtles using a shrinking gap.
 * 
 * @param arr[] Array of integers to be sorted.
 * @param n Size of the array.
 */
void ChatGPT::combSort(int arr[], int n) {
    int gap = n;
    bool swapped = true;

    while (gap > 1 || swapped) {
        gap = (gap * 10) / 13;
        if (gap < 1) gap = 1;
        swapped = false;
        for (int i = 0; i + gap < n; i++) {
            if (arr[i] > arr[i + gap]) {
                int temp = arr[i];
                arr[i] = arr[i + gap];
                arr[i + gap] = temp;
                swapped = true;
            }
        }
    }
}

// 10. Pancake Sort

static void flip(int arr[], int n) {
    for (int i = 0, j = n - 1; i < j; i++, j--) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

/**
 * Pancake Sort: Repeatedly flips subarrays to move the largest unsorted element to its correct position.
 * 
 * @param arr[] Array of integers to be sorted.
 * @param n Size of the array.
 */
void ChatGPT::pancakeSort(int arr[], int n) {
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
