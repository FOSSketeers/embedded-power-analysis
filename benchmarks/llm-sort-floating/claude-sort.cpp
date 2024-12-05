#include "claude-sort.h"

// 1. Bubble Sort

void Claude::bubbleSort(double arr[], int n) {
    /* 
     * Bubble Sort Algorithm
     * Input: 
     *   - arr: Pointer to a double array to be sorted
     *   - n: Number of elements in the array
     * Behavior: Sorts array in-place in ascending order
     * Time Complexity: O(n^2)
     * Space Complexity: O(1)
     * Note: Simple but inefficient for large arrays
     */
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap elements
                double temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        // Optimization: If no swapping occurred, array is already sorted
        if (!swapped) break;
    }
}

// 2. Insertion Sort

void Claude::insertionSort(double arr[], int n) {
    /* 
     * Insertion Sort Algorithm
     * Input: 
     *   - arr: Pointer to a double array to be sorted
     *   - n: Number of elements in the array
     * Behavior: Sorts array in-place in ascending order
     * Time Complexity: O(n^2)
     * Space Complexity: O(1)
     * Note: Efficient for small arrays or nearly sorted data
     */
    for (int i = 1; i < n; i++) {
        double key = arr[i];
        int j = i - 1;
        
        // Move elements greater than key one position ahead
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// 3. Merge Sort

static void merge(double arr[], int l, int m, int r) {
    // Helper function for Merge Sort
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    
    // Temporary arrays
    double L[n1], R[n2];
    
    // Copy data to temporary arrays
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    
    // Merge the temporary arrays
    i = 0; j = 0; k = l;
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
    
    // Copy remaining elements of L[]
    while (i < n1) {
        arr[k] = L[i];
        i++; k++;
    }
    
    // Copy remaining elements of R[]
    while (j < n2) {
        arr[k] = R[j];
        j++; k++;
    }
}

static void mergeSortHelper(double arr[], int l, int r) {
    if (l < r) {
        // Find the middle point
        int m = l + (r - l) / 2;
        
        // Sort first and second halves
        mergeSortHelper(arr, l, m);
        mergeSortHelper(arr, m + 1, r);
        
        merge(arr, l, m, r);
    }
}

void Claude::mergeSort(double arr[], int n) {
    /* 
     * Merge Sort Algorithm
     * Input: 
     *   - arr: Pointer to a double array to be sorted
     *   - n: Number of elements in the array
     * Behavior: Sorts array in-place in ascending order
     * Time Complexity: O(n log n)
     * Space Complexity: O(n)
     * Note: Divide and conquer algorithm, more memory intensive
     */
    mergeSortHelper(arr, 0, n - 1);
}

// 4. Quick Sort

static int partition(double arr[], int low, int high) {
    // Helper function for Quick Sort
    double pivot = arr[high];
    int i = (low - 1);
    
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            // Swap elements
            double temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    
    // Swap pivot
    double temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    
    return (i + 1);
}

static void quickSortHelper(double arr[], int low, int high) {
    if (low < high) {
        // Partition the array
        int pi = partition(arr, low, high);
        
        // Recursively sort elements before and after partition
        quickSortHelper(arr, low, pi - 1);
        quickSortHelper(arr, pi + 1, high);
    }
}

void Claude::quickSort(double arr[], int n) {
    /* 
     * Quick Sort Algorithm
     * Input: 
     *   - arr: Pointer to a double array to be sorted
     *   - n: Number of elements in the array
     * Behavior: Sorts array in-place in ascending order
     * Time Complexity: O(n log n) average, O(n^2) worst case
     * Space Complexity: O(log n)
     * Note: In-place sorting with good average performance
     */
    quickSortHelper(arr, 0, n - 1);
}

// 5. Heap Sort

static void heapify(double arr[], int n, int i) {
    // Helper function for Heap Sort
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
        double swap = arr[i];
        arr[i] = arr[largest];
        arr[largest] = swap;
        
        heapify(arr, n, largest);
    }
}

void Claude::heapSort(double arr[], int n) {
    /* 
     * Heap Sort Algorithm
     * Input: 
     *   - arr: Pointer to a double array to be sorted
     *   - n: Number of elements in the array
     * Behavior: Sorts array in-place in ascending order
     * Time Complexity: O(n log n)
     * Space Complexity: O(1)
     * Note: In-place sorting with consistent performance
     */
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    
    // Extract elements from heap one by one
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        double temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        
        // Call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

// 6. Gnome Sort

void Claude::gnomeSort(double arr[], int n) {
    /* 
     * Gnome Sort Algorithm
     * Input: 
     *   - arr: Pointer to a double array to be sorted
     *   - n: Number of elements in the array
     * Behavior: Sorts array in-place in ascending order
     * Time Complexity: O(n^2)
     * Space Complexity: O(1)
     * Note: Similar to insertion sort, very simple implementation
     */
    int index = 0;
    while (index < n) {
        if (index == 0 || arr[index] >= arr[index - 1])
            index++;
        else {
            // Swap elements
            double temp = arr[index];
            arr[index] = arr[index - 1];
            arr[index - 1] = temp;
            index--;
        }
    }
}

// 7. Radix Sort (for positive doubles, limited precision)

static void countingSort(double arr[], int n, int exp) {
    // Helper function for Radix Sort
    double output[n];
    int count[10] = {0};
    
    // Store count of occurrences in count[]
    for (int i = 0; i < n; i++)
        count[int(((int)arr[i] / exp) % 10)]++;
    
    // Change count[i] so that count[i] now contains actual
    // position of this digit in output[]
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];
    
    // Build the output array
    for (int i = n - 1; i >= 0; i--) {
        output[count[int(((int)arr[i] / exp) % 10)] - 1] = arr[i];
        count[int(((int)arr[i] / exp) % 10)]--;
    }
    
    // Copy the output array to arr[], so that arr[] now
    // contains sorted numbers according to current digit
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

void Claude::radixSort(double arr[], int n) {
    /* 
     * Radix Sort Algorithm (Integer-based)
     * Input: 
     *   - arr: Pointer to a double array to be sorted
     *   - n: Number of elements in the array
     * Behavior: Sorts array in-place in ascending order
     * Time Complexity: O(d(n+k)), where d is number of digits
     * Space Complexity: O(n+k)
     * Limitations: 
     *   - Only works for non-negative integers
     *   - Precision is limited
     *   - Converts doubles to integers
     */
    // Find the maximum number to know number of digits
    double max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    
    // Do counting sort for every digit
    for (int exp = 1; max/exp > 0; exp *= 10)
        countingSort(arr, n, exp);
}

// 8. Shell Sort

void Claude::shellSort(double arr[], int n) {
    /* 
     * Shell Sort Algorithm
     * Input: 
     *   - arr: Pointer to a double array to be sorted
     *   - n: Number of elements in the array
     * Behavior: Sorts array in-place in ascending order
     * Time Complexity: O(n log n) to O(n^2)
     * Space Complexity: O(1)
     * Note: Improvement over insertion sort
     */
    // Start with a big gap, then reduce gap
    for (int gap = n/2; gap > 0; gap /= 2) {
        // Do gapped insertion sort for this gap size
        for (int i = gap; i < n; i++) {
            // Save arr[i] in temp and make a hole at position i
            double temp = arr[i];
            
            // Shift earlier gap-sorted elements up until the correct
            // location for arr[i] is found
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
            
            // Put temp (the original arr[i]) in its correct location
            arr[j] = temp;
        }
    }
}

// 9. Comb Sort

void Claude::combSort(double arr[], int n) {
    /* 
     * Comb Sort Algorithm
     * Input: 
     *   - arr: Pointer to a double array to be sorted
     *   - n: Number of elements in the array
     * Behavior: Sorts array in-place in ascending order
     * Time Complexity: O(n log n)
     * Space Complexity: O(1)
     * Note: Improvement over bubble sort
     */
    // Initialize gap
    int gap = n;
    bool swapped = true;
    
    while (gap != 1 || swapped) {
        // Find next gap
        gap = (gap * 10) / 13;
        if (gap < 1) gap = 1;
        
        // Reset swapped flag for this pass
        swapped = false;
        
        // Compare all elements with current gap
        for (int i = 0; i < n - gap; i++) {
            if (arr[i] > arr[i + gap]) {
                // Swap elements
                double temp = arr[i];
                arr[i] = arr[i + gap];
                arr[i + gap] = temp;
                swapped = true;
            }
        }
    }
}

// 10. Pancake Sort

static void flip(double arr[], int k) {
    // Helper function to reverse first k elements
    int start = 0;
    while (start < k) {
        double temp = arr[start];
        arr[start] = arr[k];
        arr[k] = temp;
        start++;
        k--;
    }
}

static int findMaxIndex(double arr[], int n) {
    // Helper function to find index of maximum element
    int mi = 0;
    for (int i = 0; i < n; i++)
        if (arr[i] > arr[mi])
            mi = i;
    return mi;
}

void Claude::pancakeSort(double arr[], int n) {
    /* 
     * Pancake Sort Algorithm
     * Input: 
     *   - arr: Pointer to a double array to be sorted
     *   - n: Number of elements in the array
     * Behavior: Sorts array in-place in ascending order
     * Time Complexity: O(n^2)
     * Space Complexity: O(1)
     * Note: Unconventional sorting method using only flipping
     */
    for (int curr_size = n; curr_size > 1; curr_size--) {
        // Find index of maximum element
        int mi = findMaxIndex(arr, curr_size);
        
        // Move maximum element to beginning of array if not already
        if (mi != curr_size - 1) {
            // If maximum is not at end, first flip to move to beginning
            if (mi != 0)
                flip(arr, mi);
            
            // Now flip the entire current subarray
            flip(arr, curr_size - 1);
        }
    }
}
