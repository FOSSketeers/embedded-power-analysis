# Benchmarking Sorting Algorithm Implementations from Different LLMs

We ask each LLM to implement certain sorting algorithms with same prompt message. Then, we will run a benchmark in each implementation and compare the results.

## Models

- ChatGPT (4o)
- Gemini (1.5 Flash)
- Claude (Haiku)

These versions are recorded on 29th of November, 2024.

## Algorithms:

1. Bubble Sort
2. Insertion Sort
3. Merge Sort
4. Quick Sort
5. Heap Sort
6. Gnome Sort
7. Radix Sort
8. Shell Sort
9. Comb Sort
10. Pancake Sort

## Prompt

Prompt below is written for Arduino Uno R3, if you are going to benchmark different boards or microprocessors, replace the names.

```markdown
I am conducting a benchmarking experiment to measure the current draw of an Arduino Uno R3 while running different sorting algorithms. I need your implementation of each of the following sorting algorithms, but **only the sorting function itself** (do not include Arduino setup, loop, or other unrelated code).

For each algorithm, provide:

1.  A signature that is `void sort(int arr[], int n);`.
2.  **Concise documentation** at the beginning of the function to explain:
    -   The algorithm being implemented.
    -   The expected input/output (e.g., an integer array and its length).
    -   Any additional parameters or assumptions you make.

The algorithms I need implementations for are:

1.  **Bubble Sort**
2.  **Insertion Sort**
3.  **Merge Sort**
4.  **Quick Sort**
5.  **Heap Sort**
6.  **Gnome Sort**
7.  **Radix Sort**
8.  **Shell Sort**
9.  **Comb Sort**
10.  **Pancake Sort**

Please ensure that your implementation:

-   **Does not use any libraries** that are not standard for basic sorting (e.g., no `std::sort` or other built-in sort functions).
-   Assumes the array is an integer array.
-   Is optimized for small-scale array sizes (as it will run on an Arduino).

If you have any specific implementation notes or considerations, please document them briefly. The primary goal is to get the sorting functions in an efficient and well-documented format.
```
