#include <Arduino.h>

#include <util.h>

#include "rand.h"
#include "search.h"
#include "matmul.h"
#include "dijkstra.h"
#include "numeric.h"

constexpr static int32_t LOOP_COUNT = 10000;
const int EXPERIMENT_REPETITION = 10;
const int EXPERIMENT_DELAY = 2000;
const int ALGORITHM_DELAY = 1500;

// Force values to not be optimized.
extern volatile int32_t sink = 0;

void runBenchmark() {
    if constexpr (SERIAL_OUTPUT)
        Serial.println("Starting benchmark...");
    setState(0, "idle");

    mt19937_init(0xdeadbeef);
    setState(1, "rand_mt19937");
    #pragma GCC unroll 4
    for (int i = 0; i < LOOP_COUNT; ++i) {
        sink = mt19937_rand();
    }
    setState(0, "idle");
    delay(ALGORITHM_DELAY);

    lcg_init(0xdeadbeef);
    setState(2, "rand_lcg");
    #pragma GCC unroll 4
    for (int i = 0; i < LOOP_COUNT; ++i) {
        sink = lcg_rand();
    }
    setState(0, "idle");
    delay(ALGORITHM_DELAY);

    {
        lcg_init(0xdeadbeef);
        int arr[100];
        for (int i = 0; i < 100; ++i) {
            arr[i] = lcg_rand();
        }

        setState(3, "search_linear");
        #pragma GCC unroll 4
        for (int i = 0; i < LOOP_COUNT; ++i) {
            sink = lcg_rand();
        }
        setState(0, "idle");
        delay(ALGORITHM_DELAY);

        arr[0] = 0;
        for (int i = 1; i < 100;) {
            int cand = lcg_rand();
            if (arr[i - 1] < cand) {
                arr[i] = cand;
                ++i;
            }
        }
        setState(4, "search_binary");
        #pragma GCC unroll 4
        for (int i = 0; i < LOOP_COUNT; ++i) {
            sink = binary_search(arr, 100, arr[lcg_rand() % 100]);
        }
        setState(0, "idle");
        delay(ALGORITHM_DELAY);
    }

    {
        int arr1[100];
        int arr2[100];
        volatile int sink_arr[100] = {};

        lcg_init(0xdeadbeef);
        for (int i = 0; i < 100; ++i) {
            arr1[i] = lcg_rand();
            arr2[i] = lcg_rand();
        }

        setState(5, "matmul");
        for (int i = 0; i < LOOP_COUNT; ++i) {
            matmul(arr1, arr2, sink_arr, 10, 10, 10, 10);
        }
        setState(0, "idle");
        delay(ALGORITHM_DELAY);
    }

    {
        int graph[DIJKSTRA_MAX_NODES][DIJKSTRA_MAX_NODES];
        volatile int sink_dist[DIJKSTRA_MAX_NODES];

        lcg_init(0xdeadbeef);
        for (int i = 0; i < DIJKSTRA_MAX_NODES; ++i) {
            for (int j = 0; j < DIJKSTRA_MAX_NODES; ++j) {
                graph[i][j] = lcg_rand() % DIJKSTRA_INF;
            }
        }

        setState(6, "dijkstra");
        for (int i = 0; i < LOOP_COUNT; ++i) {
            dijkstra(graph, sink_dist, DIJKSTRA_MAX_NODES, 0);
        }
        setState(0, "idle");
        delay(ALGORITHM_DELAY);
    }

    lcg_init(0xdeadbeef);
    setState(7, "gcd");
    #pragma GCC unroll 4
    for (int i = 0; i < LOOP_COUNT; ++i) {
        sink = binaryGCD(lcg_rand(), lcg_rand());
    }
    setState(0, "idle");
    delay(ALGORITHM_DELAY);

    lcg_init(0xdeadbeef);
    setState(8, "karatsuba");
    for (int i = 0; i < LOOP_COUNT; ++i) {
        sink = karatsuba(lcg_rand(), lcg_rand());
    }
    setState(0, "idle");
    delay(ALGORITHM_DELAY);

    lcg_init(0xdeadbeef);
    #pragma GCC unroll 4
    setState(9, "fibonacci_recursive");
    for (int i = 0; i < LOOP_COUNT; ++i) {
        sink = fibonacci_recursive(lcg_rand() % 100);
    }
    setState(0, "idle");
    delay(ALGORITHM_DELAY);

    lcg_init(0xdeadbeef);
    #pragma GCC unroll 4
    setState(10, "fibonacci_iterative");
    for (int i = 0; i < LOOP_COUNT; ++i) {
        sink = fibonacci_iterative(lcg_rand() % 100);
    }
    setState(0, "idle");
    delay(ALGORITHM_DELAY);

    lcg_init(0xdeadbeef);
    #pragma GCC unroll 4
    setState(11, "factorial_recursive");
    for (int i = 0; i < LOOP_COUNT; ++i) {
        sink = factorial_recursive(lcg_rand() % 9);
    }
    setState(0, "idle");
    delay(ALGORITHM_DELAY);

    lcg_init(0xdeadbeef);
    #pragma GCC unroll 4
    setState(12, "factorial_iterative");
    for (int i = 0; i < LOOP_COUNT; ++i) {
        sink = factorial_iterative(lcg_rand() % 9);
    }
    setState(0, "idle");
    delay(ALGORITHM_DELAY);

    {
        int arr[200];

        lcg_init(0xdeadbeef);
        for (int i = 0; i < 200; ++i) {
            arr[i] = lcg_rand();
        }

        setState(13, "sum");
        #pragma GCC unroll 4
        for (int i = 0; i < LOOP_COUNT; ++i) {
            sink = sum(arr, 200);
        }
        setState(0, "idle");
        delay(ALGORITHM_DELAY);
    }

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
