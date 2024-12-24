# BBM479 Workspace

Well, our project(s) don't have their own name yet. This is our workspace where we do experiments and such, and store everything related to them. To maintain markdown tables more easily, you can use this [handy tool](https://tabletomarkdown.com/convert-spreadsheet-to-markdown/). These experiment logs are not definitive, feel free to add new columns.

## Experiments

Using Nordic Power Profile Kit 2, we are measuring power consumptions of certain programs in different microprocessors. We are experimenting with only Arduino Uno R3 and Arduino Uno R4 Minima these days.

### 1. sort

We experiment different sorting algorithms with different arrays in different devices.

#### Experiment Log

| Date | Device | Commit Hash | Array Size | Array Type | Array Characteristics | Circuit | Measurement |
| ---- | ------ | ------------ | ---------- | ---------- | ---------- | ------- | ----------- |
| 2024-11-18 | Uno R3 (clone) | [d9e1f62](https://github.com/div72/bbm479/commit/d9e1f629729e626ce25a95ed244edd289c76b294) | 300 | `int[]` with only non-negative numbers | Generated before each algo, pseudo-random | [circuit 000](/circuits/000.png) | [r3-sort-300-digitalout-5runs.csv.xz](/measurements/old-broken-state-transitions/r3-sort-300-digitalout-5runs.csv.xz) |
| 2024-11-18 | Uno R4 Minima (clone) | [9acfcf9](https://github.com/div72/bbm479/commit/9acfcf9bb049b7724b56dbb1016f7749e48f11f6) | 300 | `int[]` with only non-negative numbers | Generated before each algo, pseudo-random | [circuit 001](/circuits/001.png) | [r4-sort-300-digitalout-5runs.csv.xz](/measurements/old-broken-state-transitions/r4-sort-300-digitalout-5runs.csv.xz) |
|      |        |              |            |            |         |             | |


### 2. crypto

Lorem ipsum

#### Experiment Log

| Date | Device | Commit Hash | Circuit | Measurement |
| ---- | ------ | ------------ | ------- | ----------- |
| 2024-12-03 | Uno R4 Minima (clone) | [65cc397](https://github.com/div72/bbm479/commit/65cc397122b0b00d1971487c2bf67bac3a54556f) | [circuit 003](/circuits/003.png) | [r4-crypto-digitalout-1runs.csv.xz](/measurements/r4-crypto-digitalout-1runs.csv.xz) |
| 2024-12-04 | Uno R3 (clone) | [e1edc7b](https://github.com/div72/bbm479/commit/e1edc7b80b04c2694d0e707135cc02af977c1860) | [circuit 002](/circuits/002.png) | [r3-crypto-digitalout-1runs.csv.xz](/measurements/r3-crypto-digitalout-1runs.csv.xz) |
| 2024-12-17 | Uno R4 Minima (clone) | [d486902](https://github.com/div72/bbm479/commit/d4869026f153a9b9c67de75b82350007d2cf8920) | [circuit 003](/circuits/003.png) | [r4-crypto-digitalout-3runs.csv.xz](/measurements/r4-crypto-digitalout-3runs.csv.xz) |
| 2024-12-17 | Uno R3 (clone) | [d486902](https://github.com/div72/bbm479/commit/d4869026f153a9b9c67de75b82350007d2cf8920) | [circuit 002](/circuits/002.png) | [r3-crypto-digitalout-3runs.csv.xz](/measurements/r3-crypto-digitalout-3runs.csv.xz) |

### 3. llm-sort

Here we experiment whether there is a significant difference in the performance of sorting algorithm implementations across different LLMs.

#### Experiment Log

| Date | Device | Commit Hash | Array Size | Array Type | Array Characteristics | Circuit | Measurement |
| ---- | ------ | ------------ | ---------- | ---------- | ------- | ------- | ----------- |
| 2024-12-03 | Uno R4 Minima (clone) | [65cc397](https://github.com/div72/bbm479/commit/65cc397122b0b00d1971487c2bf67bac3a54556f) | 100 | `int[]` with numbers between [-300, 300] | Predefined random array generated with [random_array_generator.py](https://github.com/div72/bbm479/blob/65cc397122b0b00d1971487c2bf67bac3a54556f/random_array_generator.py) | [circuit 003](/circuits/003.png) | [r4-llmsort-predefinedarray-int-100-digitalout-1runs.csv.xz](/measurements/r4-llmsort-predefinedarray-int-100-digitalout-1runs.csv.xz) |
| 2024-12-04 | Uno R3 (clone) | [e1edc7b](https://github.com/div72/bbm479/commit/e1edc7b80b04c2694d0e707135cc02af977c1860) | 100 | `int[]` with numbers between [-300, 300] | Predefined random array generated with [random_array_generator.py](https://github.com/div72/bbm479/blob/65cc397122b0b00d1971487c2bf67bac3a54556f/random_array_generator.py) | [circuit 002](/circuits/002.png) | [r3-llmsort-predefinedarray-int-100-digitalout-1runs.csv.xz](/measurements/r3-llmsort-predefinedarray-int-100-digitalout-1runs.csv.xz) |
| 2024-12-17 | Uno R4 Minima (clone) | [d486902](https://github.com/div72/bbm479/commit/d4869026f153a9b9c67de75b82350007d2cf8920) | 100 | `int[]` with numbers between [-300, 300] | Predefined random array generated with [random_array_generator.py](https://github.com/div72/bbm479/blob/d4869026f153a9b9c67de75b82350007d2cf8920/random_array_generator.py) | [circuit 003](/circuits/003.png) | [r4-llmsort-predefinedarray-int-100-digitalout-3runs.csv.xz](/measurements/r4-llmsort-predefinedarray-int-100-digitalout-3runs.csv.xz) |
| 2024-12-17 | Uno R4 Minima (clone) | [d486902](https://github.com/div72/bbm479/commit/d4869026f153a9b9c67de75b82350007d2cf8920) | 50 | `float[]` with numbers between [0, 300] | Predefined random array generated with [random_array_generator.py](https://github.com/div72/bbm479/blob/d4869026f153a9b9c67de75b82350007d2cf8920/random_array_generator.py) | [circuit 003](/circuits/003.png) | [r4-llmsortfloat-predefinedarray-float-50-3runs.csv.xz](/measurements/r4-llmsortfloat-predefinedarray-float-50-3runs.csv.xz) |
| 2024-12-17 | Uno R3 (clone) | [d486902](https://github.com/div72/bbm479/commit/d4869026f153a9b9c67de75b82350007d2cf8920) | 100 | `int[]` with numbers between [-300, 300] | Predefined random array generated with [random_array_generator.py](https://github.com/div72/bbm479/blob/d4869026f153a9b9c67de75b82350007d2cf8920/random_array_generator.py) | [circuit 002](/circuits/002.png) | [r3-llmsort-predefinedarray-int-100-digitalout-3runs.csv.xz](/measurements/r3-llmsort-predefinedarray-int-100-digitalout-3runs.csv.xz) |
| 2024-12-17 | Uno R3 (clone) | [d486902](https://github.com/div72/bbm479/commit/d4869026f153a9b9c67de75b82350007d2cf8920) | 50 | `float[]` with numbers between [0, 300] | Predefined random array generated with [random_array_generator.py](https://github.com/div72/bbm479/blob/d4869026f153a9b9c67de75b82350007d2cf8920/random_array_generator.py) | [circuit 002](/circuits/002.png) | [r3-llmsortfloat-predefinedarray-float-50-3runs.csv.xz](/measurements/r3-llmsortfloat-predefinedarray-float-50-3runs.csv.xz) |
| 2024-12-17 | Uno R3 (clone) | [d486902](https://github.com/div72/bbm479/commit/d4869026f153a9b9c67de75b82350007d2cf8920) | 50 | `float[]` with numbers between [0, 300] | Predefined random array generated with [random_array_generator.py](https://github.com/div72/bbm479/blob/d4869026f153a9b9c67de75b82350007d2cf8920/random_array_generator.py) | [circuit 002](/circuits/002.png) | [r3-llmsortfloat-predefinedarray-float-50-1runs.csv.xz](/measurements/r3-llmsortfloat-predefinedarray-float-50-1runs.csv.xz) |
