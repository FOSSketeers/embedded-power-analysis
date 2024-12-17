#include "chatgpt-sort.h"

// 1. Bubble Sort

/**
 * Bubble Sort: Repeatedly swaps adjacent elements if they are in the wrong order.
 * 
 * @param arr[] Array of integers to be sorted.
 * @param n Size of the array.
 */
void ChatGPT::bubbleSort(float arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                float temp = arr[j];
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
void ChatGPT::insertionSort(float arr[], int n) {
    for (int i = 1; i < n; i++) {
        float key = arr[i];
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
 * Implements Merge Sort algorithm.
 * Divides the array recursively and merges sorted halves.
 * Input: A float array `arr` of size `n`.
 * Output: The array is sorted in ascending order.
 * Note: Uses recursion and requires a helper function.
 */
static void merge(float arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    float L[n1], R[n2];
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int i = 0; i < n2; i++) R[i] = arr[mid + 1 + i];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

static void mergeSortHelper(float arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortHelper(arr, left, mid);
        mergeSortHelper(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void ChatGPT::mergeSort(float arr[], int n) {
    mergeSortHelper(arr, 0, n - 1);
}

// 4. Quick Sort

/**
 * Implements Quick Sort algorithm.
 * Partitions the array around a pivot and recursively sorts partitions.
 * Input: A float array `arr` of size `n`.
 * Output: The array is sorted in ascending order.
 * Note: Uses recursion and requires a helper function.
 */
int partition(float arr[], int low, int high) {
    float pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            float temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    float temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

static void quickSortHelper(float arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSortHelper(arr, low, pi - 1);
        quickSortHelper(arr, pi + 1, high);
    }
}

void ChatGPT::quickSort(float arr[], int n) {
    quickSortHelper(arr, 0, n - 1);
}

// 5. Heap Sort

/**
 * Implements Heap Sort algorithm.
 * Converts the array into a max-heap and sorts it by extracting the largest element iteratively.
 * Input: A float array `arr` of size `n`.
 * Output: The array is sorted in ascending order.
 */
void heapify(float arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;
    if (largest != i) {
        float temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void ChatGPT::heapSort(float arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        float temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

// 6. Gnome Sort

/**
 * Implements Gnome Sort algorithm.
 * Moves an element to its correct position in a manner similar to a garden gnome sorting flower pots.
 * Input: A float array `arr` of size `n`.
 * Output: The array is sorted in ascending order.
 */
void ChatGPT::gnomeSort(float arr[], int n) {
    int index = 0;
    while (index < n) {
        if (index == 0 || arr[index] >= arr[index - 1]) {
            index++;
        } else {
            float temp = arr[index];
            arr[index] = arr[index - 1];
            arr[index - 1] = temp;
            index--;
        }
    }
}

// 7. Radix Sort

void ChatGPT::radixSort(float arr[], int n) {
    // Radix sort does not work directly on floating-point numbers due to the
    // absence of a straightforward digit-extraction process. This algorithm
    // is not implemented.
    return;
}

// 8. Shell Sort

/**
 * Implements Shell Sort algorithm.
 * Sorts the array by comparing elements separated by a gap that decreases over iterations.
 * Input: A float array `arr` of size `n`.
 * Output: The array is sorted in ascending order.
 */
void ChatGPT::shellSort(float arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            float temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

// 9. Comb Sort

/**
 * Implements Comb Sort algorithm.
 * Improves Bubble Sort by eliminating turtles (small values) using a gap reduction factor.
 * Input: A float array `arr` of size `n`.
 * Output: The array is sorted in ascending order.
 */
void ChatGPT::combSort(float arr[], int n) {
    int gap = n;
    bool swapped = true;
    while (gap > 1 || swapped) {
        gap = (gap > 1) ? (gap / 1.3) : 1; // Reduce the gap size
        swapped = false;
        for (int i = 0; i + gap < n; i++) {
            if (arr[i] > arr[i + gap]) {
                float temp = arr[i];
                arr[i] = arr[i + gap];
                arr[i + gap] = temp;
                swapped = true;
            }
        }
    }
}

// 10. Pancake Sort

static void flip(float arr[], int i) {
    int start = 0;
    while (start < i) {
        float temp = arr[start];
        arr[start] = arr[i];
        arr[i] = temp;
        start++;
        i--;
    }
}

/**
 * Implements Pancake Sort algorithm.
 * Repeatedly flips the largest unsorted element to the top, then to its correct position.
 * Input: A float array `arr` of size `n`.
 * Output: The array is sorted in ascending order.
 */
void ChatGPT::pancakeSort(float arr[], int n) {
    for (int curr_size = n; curr_size > 1; curr_size--) {
        int max_index = 0;
        for (int i = 1; i < curr_size; i++) {
            if (arr[i] > arr[max_index]) max_index = i;
        }
        if (max_index != curr_size - 1) {
            flip(arr, max_index);
            flip(arr, curr_size - 1);
        }
    }
}
