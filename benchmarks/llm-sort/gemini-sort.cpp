#include "gemini-sort.h"

// 1. Bubble Sort

void Gemini::bubbleSort(int arr[], int n) {
    // Sorts an array of integers using bubble sort.
    // Input: An integer array 'arr' of size 'n'.
    // Output: The sorted array 'arr'.

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap arr[j] and arr[j+1]
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// 2. Insertion Sort

void Gemini::insertionSort(int arr[], int n) {
    // Sorts an array of integers using insertion sort.
    // Input: An integer array 'arr' of size 'n'.
    // Output: The sorted array 'arr'.

    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        /* Move elements of arr[0..i-1], that are
       greater than key, to one position ahead
       of their current position */
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// 3. Merge Sort

static void merge(int arr[], int left, int mid, int right) {
    // Merges two subarrays of arr[].
    // First subarray is arr[left..mid]
    // Second subarray is arr[mid+1..right]
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    int L[n1], R[n2];

    // Copy data to temporary arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Merge the temporary arrays back into arr[left..right]
    int i = 0, j = 0, k = left;
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

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

static void mergeSortHelper(int arr[], int left, int right) {
    if (left < right) {
        // Find the middle point
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSortHelper(arr, left, mid);
        mergeSortHelper(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

void Gemini::mergeSort(int arr[], int n) {
    // Sorts an array of integers using the Merge Sort algorithm.
    // Input: An integer array `arr` and its size `n`.
    // Output: The sorted array in ascending order.

    mergeSortHelper(arr, 0, n - 1);
}

// 4. Quick Sort

static void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

static int partition(int arr[], int low, int high) {
    // Partition the array around a pivot element.
    // Input: An integer array `arr`, low index `low`, and high index `high`.
    // Output: The index of the pivot element after partitioning.

    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

static void quickSortHelper(int arr[], int low, int high) {
    if (low < high) {
        // Partition the array and get the pivot index
        int pi = partition(arr, low, high);

        // Recursively sort the subarrays before and after the pivot
        quickSortHelper(arr, low, pi - 1);
        quickSortHelper(arr, pi + 1, high);
    }
}

void Gemini::quickSort(int arr[], int n) {
    // Sorts an array of integers using the Quick Sort algorithm.
    // Input: An integer array `arr` and its size `n`.
    // Output: The sorted array in ascending order.

    quickSortHelper(arr, 0, n - 1);
}

// 5. Heap Sort

static void heapify(int arr[], int n, int i) {
    // Heapify subtree rooted at index i.
    // Input: An integer array `arr`, its size `n`, and the root index `i`.
    // Output: The heapified subtree.

    int largest = i;    // Initialize largest as root
    int l = 2 * i + 1;  // left = 2*i + 1
    int r = 2 * i + 2;  // right = 2*i + 2

    // If left child is larger than root
    if (l < n && arr[l] > arr[largest])
        largest = l;

    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // If largest is not root
    if (largest != i) {
        swap(&arr[i], &arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

void Gemini::heapSort(int arr[], int n) {
    // Sorts an array of integers using the Heap Sort algorithm.
    // Input: An integer array `arr` and its size `n`.
    // Output: The sorted array in ascending order.

    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // One by one extract an element from heap
    for (int i = n - 1; i >= 0; i--) {
        // Move current root to end
        swap(&arr[0], &arr[i]);

        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

// 6. Gnome Sort

void Gemini::gnomeSort(int arr[], int n) {
    // Sorts an array of integers using the Gnome Sort algorithm.
    // Input: An integer array `arr` and its size `n`.
    // Output: The sorted array in ascending order.

    int index = 0;
    while (index < n) {
        if (index == 0 || arr[index] >= arr[index - 1]) {
            index++;
        } else {
            swap(&arr[index], &arr[index - 1]);
            index--;
        }
    }
}

// 7. Radix Sort

static int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

static void countSort(int arr[], int n, int exp) {
    int output[n];  // output array
    int count[10] = { 0 };

    // Store count of occurrences in count[]
    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    // Change count[i] so that count[i] now contains
    // actual position of this digit in output[]
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // Copy the output array to arr[], so that arr[] now
    // contains sorted numbers for current digit
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

void Gemini::radixSort(int arr[], int n) {
    // Sorts an array of integers using the Radix Sort algorithm.
    // Input: An integer array `arr` and its size `n`.
    // Output: The sorted array in ascending order.

    // Find the maximum number to know the number of digits
    int max = getMax(arr, n);

    // Do counting sort for every digit. Note that instead
    // of passing digit number, exp is passed. exp is 10^i
    // where i is current digit number
    for (int exp = 1; max / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}

// 8. Shell Sort

void Gemini::shellSort(int arr[], int n) {
    // Sorts an array of integers using the Shell Sort algorithm.
    // Input: An integer array `arr` and its size `n`.
    // Output: The sorted array in ascending order.

    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i += 1) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
    }
}

// 9. Comb Sort

static int getNextGap(int gap) {
    gap = (gap * 10) / 13;
    if (gap < 1)
        return 1;
    return gap;
}

void Gemini::combSort(int arr[], int n) {
    // Sorts an array of integers using the Comb Sort algorithm.
    // Input: An integer array `arr` and its size `n`.
    // Output: The sorted array in ascending order.

    int gap = n;
    bool swapped = true;

    while (gap != 1 || swapped) {
        gap = getNextGap(gap);
        swapped = false;

        for (int i = 0; i < n - gap; i++) {
            if (arr[i] > arr[i + gap]) {
                swap(&arr[i], &arr[i + gap]);
                swapped = true;
            }
        }
    }
}

// 10. Pancake Sort

static void flip(int arr[], int i) {
    // Reverse array from 0 to i
    int temp, start = 0;
    while (start < i) {
        temp = arr[start];
        arr[start] = arr[i];
        arr[i] = temp;
        start++;
        i--;
    }
}

void Gemini::pancakeSort(int arr[], int n) {
    // Sorts an array of integers using the Pancake Sort algorithm.
    // Input: An integer array `arr` and its size `n`.
    // Output: The sorted array in ascending order.

    for (int curr_size = n; curr_size > 1; --curr_size) {
        // Find the index of the maximum element in arr[0..curr_size-1]
        int mi = 0;
        for (int i = 1; i < curr_size; ++i)
            if (arr[i] > arr[mi])
                mi = i;

        // Bring the maximum element to beginning
        flip(arr, mi);

        // Bring the maximum element to end of current array
        flip(arr, curr_size - 1);
    }
}
