#include "claude-sort.h"

// 1. Bubble Sort

/**
 * Implements Bubble Sort algorithm
 * @param arr Integer array to be sorted in-place
 * @param n Number of elements in the array
 * @note Time complexity: O(n^2), Space complexity: O(1)
 * @note Stable sorting algorithm that repeatedly steps through the list
 */
void Claude::bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap elements
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        // If no swapping occurred, array is already sorted
        if (!swapped) break;
    }
}

// 2. Insertion Sort

/**
 * Implements Insertion Sort algorithm
 * @param arr Integer array to be sorted in-place
 * @param n Number of elements in the array
 * @note Time complexity: O(n^2), Space complexity: O(1)
 * @note Efficient for small arrays or nearly sorted arrays
 */
void Claude::insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        // Move elements that are greater than key
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// 3. Merge Sort

/**
 * Merges two subarrays of arr[]
 * @param arr Integer array containing subarrays to merge
 * @param l Left index of first subarray
 * @param m Middle index separating subarrays
 * @param r Right index of second subarray
 */
static void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temporary arrays
    int L[n1], R[n2];

    // Copy data to temporary arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temporary arrays back into arr[l..r]
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

static void mergeSortRecursive(int arr[], int l, int r) {
    if (l < r) {
        // Find the middle point
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSortRecursive(arr, l, m);
        mergeSortRecursive(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

/**
 * Implements Merge Sort algorithm
 * @param arr Integer array to be sorted in-place
 * @param n Number of elements in the array
 * @note Time complexity: O(n log n), Space complexity: O(n)
 * @note Divide and conquer algorithm with consistent performance
 */
void Claude::mergeSort(int arr[], int n) {
    // Call recursive helper with full array range
    mergeSortRecursive(arr, 0, n - 1);
}

// 4. Quick Sort

/**
 * Partitions the array for Quick Sort
 * @param arr Integer array to partition
 * @param low Starting index of the partition
 * @param high Ending index of the partition
 * @return Index of the pivot element after partitioning
 */
static int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            // Swap elements
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    // Swap pivot
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

static void quickSortRecursive(int arr[], int low, int high) {
    if (low < high) {
        // Partition the array
        int pi = partition(arr, low, high);

        // Recursively sort elements before and after partition
        quickSortRecursive(arr, low, pi - 1);
        quickSortRecursive(arr, pi + 1, high);
    }
}

/**
 * Implements Quick Sort algorithm
 * @param arr Integer array to be sorted in-place
 * @param n Number of elements in the array
 * @note Time complexity: O(n log n) average, O(n^2) worst case
 * @note In-place sorting with good average-case performance
 */
void Claude::quickSort(int arr[], int n) {
    // Call recursive helper with full array range
    quickSortRecursive(arr, 0, n - 1);
}

// 5. Heap Sort

/**
 * Heapifies a subtree rooted with node i
 * @param arr Integer array to heapify
 * @param n Size of the heap
 * @param i Root index of the subtree
 */
static void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // Check if left child is larger than root
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // Check if right child is larger than largest so far
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // If largest is not root, swap and continue heapifying
    if (largest != i) {
        int swap = arr[i];
        arr[i] = arr[largest];
        arr[largest] = swap;

        // Recursively heapify the affected subtree
        heapify(arr, n, largest);
    }
}

/**
 * Implements Heap Sort algorithm
 * @param arr Integer array to be sorted in-place
 * @param n Number of elements in the array
 * @note Time complexity: O(n log n)
 * @note In-place sorting with consistent performance
 */
void Claude::heapSort(int arr[], int n) {
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extract elements from heap one by one
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // Call heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

// 6. Gnome Sort

/**
 * Implements Gnome Sort algorithm
 * @param arr Integer array to be sorted in-place
 * @param n Number of elements in the array
 * @note Time complexity: O(n^2)
 * @note Simple sorting algorithm similar to insertion sort
 */
void Claude::gnomeSort(int arr[], int n) {
    int index = 0;
    while (index < n) {
        if (index == 0 || arr[index] >= arr[index - 1])
            index++;
        else {
            // Swap elements
            int temp = arr[index];
            arr[index] = arr[index - 1];
            arr[index - 1] = temp;
            index--;
        }
    }
}

// 7. Radix Sort

/**
 * Manual absolute value function
 * 
 * @param x Integer input
 * @return Absolute value of the input
 */
int abs(int x) {
    return x < 0 ? -x : x;
}

/**
 * Counts sort for Radix Sort
 * @param arr Integer array to be sorted
 * @param n Number of elements
 * @param exp Current digit's place value
 */
void countSort(int arr[], int n, int exp) {
    int output[n];          // Output array
    int count[10] = { 0 };  // Counting array for digits 0-9

    // Store count of occurrences in count[]
    for (int i = 0; i < n; i++)
        count[abs((arr[i] / exp) % 10)]++;

    // Change count[i] so that count[i] now contains actual
    // position of this digit in output[]
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array
    for (int i = n - 1; i >= 0; i--) {
        int digit = abs((arr[i] / exp) % 10);
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    // Copy the output array to arr[]
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

/**
 * Radix Sort Algorithm for Signed Integers
 * 
 * @param arr Integer array to be sorted in-place
 * @param n Number of elements in the array
 * 
 * Algorithm characteristics:
 * - Handles both positive and negative integers
 * - Works with Arduino's memory constraints
 * - Sorts by individual digits, starting from least significant
 */
void Claude::radixSort(int arr[], int n) {
    // Separate positive and negative numbers
    int positives[n];
    int negatives[n];
    int posCount = 0, negCount = 0;

    // Separate positive and negative numbers
    for (int i = 0; i < n; i++) {
        if (arr[i] >= 0)
            positives[posCount++] = arr[i];
        else
            negatives[negCount++] = -arr[i];  // Store absolute value
    }

    // Find max for positive numbers
    int posMax = posCount > 0 ? positives[0] : 0;
    for (int i = 1; i < posCount; i++)
        if (positives[i] > posMax)
            posMax = positives[i];

    // Find max for negative numbers
    int negMax = negCount > 0 ? negatives[0] : 0;
    for (int i = 1; i < negCount; i++)
        if (negatives[i] > negMax)
            negMax = negatives[i];

    // Radix sort for non-negative numbers
    // Sort positive numbers
    for (int exp = 1; posMax / exp > 0; exp *= 10)
        countSort(positives, posCount, exp);

    // Sort negative numbers
    for (int exp = 1; negMax / exp > 0; exp *= 10)
        countSort(negatives, negCount, exp);

    // Reconstruct the original array
    int index = 0;

    // First add negative numbers in reverse order
    for (int i = negCount - 1; i >= 0; i--)
        arr[index++] = -negatives[i];

    // Then add positive numbers
    for (int i = 0; i < posCount; i++)
        arr[index++] = positives[i];
}

// 8. Shell Sort

/**
 * Implements Shell Sort algorithm
 * @param arr Integer array to be sorted in-place
 * @param n Number of elements in the array
 * @note Time complexity: O(n log n) - O(n^2)
 * @note Improvement over insertion sort for larger arrays
 */
void Claude::shellSort(int arr[], int n) {
    // Start with a big gap, then reduce gap
    for (int gap = n / 2; gap > 0; gap /= 2) {
        // Do gapped insertion sort for this gap size
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;

            // Shift earlier gap-sorted elements up until the correct location for arr[i] is found
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];

            // Place temp (the original arr[i]) in its correct location
            arr[j] = temp;
        }
    }
}

// 9. Comb Sort

/**
 * Implements Comb Sort algorithm
 * @param arr Integer array to be sorted in-place
 * @param n Number of elements in the array
 * @note Time complexity: O(n log n) with the right shrink factor
 * @note Improvement over bubble sort with gap reduction
 */
void Claude::combSort(int arr[], int n) {
    // Initialize gap
    int gap = n;
    bool swapped = true;

    // Keep running until gap is 1 and no more swaps are needed
    while (gap != 1 || swapped) {
        // Reduce gap by shrink factor
        gap = (gap * 10) / 13;
        if (gap < 1) gap = 1;

        // Initialize swapped as false to check if swap happens
        swapped = false;

        // Compare all elements with current gap
        for (int i = 0; i < n - gap; i++) {
            if (arr[i] > arr[i + gap]) {
                // Swap elements
                int temp = arr[i];
                arr[i] = arr[i + gap];
                arr[i + gap] = temp;
                swapped = true;
            }
        }
    }
}

// 10. Pancake Sort

/**
 * Flips the array from 0 to index k
 * @param arr Integer array to be flipped
 * @param k Index up to which array will be flipped
 */
static void flip(int arr[], int k) {
    int start = 0;
    while (start < k) {
        int temp = arr[start];
        arr[start] = arr[k];
        arr[k] = temp;
        start++;
        k--;
    }
}

/**
 * Finds index of the maximum element in arr[0..n-1]
 * @param arr Integer array
 * @param n Number of elements
 * @return Index of the maximum element
 */
static int findMaxIndex(int arr[], int n) {
    int maxIndex = 0;
    for (int i = 0; i < n; i++)
        if (arr[i] > arr[maxIndex])
            maxIndex = i;
    return maxIndex;
}

/**
 * Implements Pancake Sort algorithm
 * @param arr Integer array to be sorted in-place
 * @param n Number of elements in the array
 * @note Time complexity: O(n^2)
 * @note Unique sorting method using only pancake flipping
 */
void Claude::pancakeSort(int arr[], int n) {
    // Start from the complete array and one by one reduce current size
    for (int currSize = n; currSize > 1; currSize--) {
        // Find index of the maximum element in arr[0..currSize-1]
        int maxIndex = findMaxIndex(arr, currSize);

        // Move the maximum element to end of current array if needed
        if (maxIndex != currSize - 1) {
            // Flip maximum element to beginning if not at start
            if (maxIndex != 0)
                flip(arr, maxIndex);

            // Flip entire current array
            flip(arr, currSize - 1);
        }
    }
}