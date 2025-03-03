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
        int arr[100] = { -28962, -28474, -28020, -27803, -27802, -27554, -27453, -27409, -27406, -26178, -26039, -24828, -24439, -23938, -23663, -22732, -22186, -22174, -21954, -21770, -20477, -20167, -19659, -19604, -18922, -16159, -15573, -14199, -14179, -14044, -12372, -11270, -10038, -9818, -8913, -8227, -7233, -6630, -5768, -5634, -4762, -4564, -4519, -4297, -3753, -2909, -2860, -2799, -2744, -2295, -2120, -1905, -505, -206, 102, 1061, 1215, 1484, 1712, 1847, 2225, 3567, 4213, 4335, 4646, 5213, 6296, 6665, 6817, 8138, 8280, 8681, 8885, 9041, 9196, 9483, 12197, 12677, 13622, 13731, 13884, 14000, 16313, 16437, 18058, 18187, 18208, 19089, 20287, 22755, 23565, 24197, 24534, 24790, 26049, 26260, 27271, 27394, 27658, 27744 };

        setState(3, "search_linear");
        #pragma GCC unroll 4
        for (int i = 0; i < LOOP_COUNT; ++i) {
            sink = linear_search(arr, 100, arr[abs(lcg_rand()) % 100]);
        }
        setState(0, "idle");
        delay(ALGORITHM_DELAY);

        setState(4, "search_binary");
        #pragma GCC unroll 4
        for (int i = 0; i < LOOP_COUNT; ++i) {
            sink = binary_search(arr, 100, arr[abs(lcg_rand()) % 100]);
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
                graph[i][j] = abs(lcg_rand()) % DIJKSTRA_INF;
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
        sink = binaryGCD(abs(lcg_rand()), abs(lcg_rand()));
    }
    setState(0, "idle");
    delay(ALGORITHM_DELAY);

    lcg_init(0xdeadbeef);
    setState(8, "karatsuba");
    for (int i = 0; i < LOOP_COUNT; ++i) {
        sink = karatsuba(abs(lcg_rand()), abs(lcg_rand()));
    }
    setState(0, "idle");
    delay(ALGORITHM_DELAY);

    lcg_init(0xdeadbeef);
    setState(9, "fibonacci_recursive");
    #pragma GCC unroll 4
    for (int i = 0; i < LOOP_COUNT; ++i) {
        sink = fibonacci_recursive(abs(lcg_rand()) % 10);
    }
    setState(0, "idle");
    delay(ALGORITHM_DELAY);

    lcg_init(0xdeadbeef);
    setState(10, "fibonacci_iterative");
    #pragma GCC unroll 4
    for (int i = 0; i < LOOP_COUNT; ++i) {
        sink = fibonacci_iterative(abs(lcg_rand()) % 10);
    }
    setState(0, "idle");
    delay(ALGORITHM_DELAY);

    lcg_init(0xdeadbeef);
    setState(11, "factorial_recursive");
    #pragma GCC unroll 4
    for (int i = 0; i < LOOP_COUNT; ++i) {
        sink = factorial_recursive(abs(lcg_rand()) % 9);
    }
    setState(0, "idle");
    delay(ALGORITHM_DELAY);

    lcg_init(0xdeadbeef);
    setState(12, "factorial_iterative");
    #pragma GCC unroll 4
    for (int i = 0; i < LOOP_COUNT; ++i) {
        sink = factorial_iterative(abs(lcg_rand()) % 9);
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
