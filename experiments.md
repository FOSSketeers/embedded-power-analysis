# Experiments

Using Nordic Power Profile Kit 2, we are measuring power consumptions of certain programs in different microprocessors. We have experimented with Arduino Uno R3 SMD (which we just call R3) and Arduino Uno R4 Minima (which we just call R4) so far. Both are clone devices.

## 1. sort

In this benchmark, we test 10 well-known sorting algorithms on our testing devices: Bubble sort, insertion sort, merge sort, quick sort, heap sort, gnome sort, radix sort, shell sort, comb sort and pancake sort.

<details>
<summary>
Click to view the Experiment Log
</summary>

| Date       | Device | Commit                                                                                                            | Array Size | Array Type                                 | Circuit                          | Measurement                                                                                                           |
| ---------- | ------ | ----------------------------------------------------------------------------------------------------------------- | ---------- | ------------------------------------------ | -------------------------------- | --------------------------------------------------------------------------------------------------------------------- |
| 2024-11-18 | R3     | [d9e1f62](https://github.com/FOSSketeers/embedded-power-analysis/commit/d9e1f629729e626ce25a95ed244edd289c76b294) | 300        | Generated before each algo, pseudo-random  | [circuit 000](/circuits/000.png) | [r3-sort-300-digitalout-5runs.csv.xz](/measurements/old-broken-state-transitions/r3-sort-300-digitalout-5runs.csv.xz) |
| 2024-11-18 | R4     | [9acfcf9](https://github.com/FOSSketeers/embedded-power-analysis/commit/9acfcf9bb049b7724b56dbb1016f7749e48f11f6) | 300        | Generated before each algo, pseudo-random  | [circuit 001](/circuits/001.png) | [r4-sort-300-digitalout-5runs.csv.xz](/measurements/old-broken-state-transitions/r4-sort-300-digitalout-5runs.csv.xz) |
| 2024-12-24 | R4     | [36e8f02](https://github.com/FOSSketeers/embedded-power-analysis/commit/36e8f02a1fa9936b5b51fc5fb29bc6f369c06594) | 100        | **Sorted**, \`int[]\` with numbers between [-300, 300] | [circuit 003](/circuits/003.png) | [r4-sort-sortedarray-int-100-3runs.csv.xz](/measurements/r4-sort-sortedarray-int-100-3runs.csv.xz)        |
| 2024-12-24 | R4     | [469a670](https://github.com/FOSSketeers/embedded-power-analysis/commit/469a670844f31c8b909383efc87cddb7ac05b504) | 100        | **Reversely sorted**, \`int[]\` with numbers between [-300, 300] | [circuit 003](/circuits/003.png) | [r4-sort-revsortedarray-int-100-3runs.csv.xz](/measurements/r4-sort-revsortedarray-int-100-3runs.csv.xz)        |
| 2024-12-24 | R3     | [469a670](https://github.com/FOSSketeers/embedded-power-analysis/commit/469a670844f31c8b909383efc87cddb7ac05b504) | 100        | **Sorted**, \`int[]\` with numbers between [-300, 300] | [circuit 002](/circuits/002.png) | [r3-sort-sortedarray-int-100-3runs.csv.xz](/measurements/r3-sort-sortedarray-int-100-3runs.csv.xz)        |
| 2024-12-24 | R3     | [469a670](https://github.com/FOSSketeers/embedded-power-analysis/commit/469a670844f31c8b909383efc87cddb7ac05b504) | 100        | **Reversely sorted**, \`int[]\` with numbers between [-300, 300] | [circuit 002](/circuits/002.png) | [r3-sort-revsortedarray-int-100-3runs.csv.xz](/measurements/r3-sort-revsortedarray-int-100-3runs.csv.xz)        |
| 2025-03-03 | R3     | [98cc0d4](https://github.com/FOSSketeers/embedded-power-analysis/commit/98cc0d4d02d5156a44480c939fc15899bc84f026) | 16         | \`int[]\` with numbers between [-300, 300] | [circuit 002](/circuits/002.png) | [r3-sort-predefined-int-16-3runs.csv.xz](/measurements/r3-sort-predefined-int-16-3runs.csv.xz)                        |
| 2025-03-03 | R3     | [2b31e7b](https://github.com/FOSSketeers/embedded-power-analysis/commit/2b31e7be7bc880ce86148b6125a5edb6f9a560ce) | 32         | \`int[]\` with numbers between [-300, 300] | [circuit 002](/circuits/002.png) | [r3-sort-predefined-int-32-3runs.csv.xz](/measurements/r3-sort-predefined-int-32-3runs.csv.xz)                        |
| 2025-03-03 | R3     | [feba46b](https://github.com/FOSSketeers/embedded-power-analysis/commit/feba46bbaaee44cb5df21b46662e3c70d02d1a4b) | 64         | \`int[]\` with numbers between [-300, 300] | [circuit 002](/circuits/002.png) | [r3-sort-predefined-int-64-3runs.csv.xz](/measurements/r3-sort-predefined-int-64-3runs.csv.xz)                        |
| 2025-03-03 | R3     | [eddf957](https://github.com/FOSSketeers/embedded-power-analysis/commit/eddf957ffa00640368fd5a221412312d12aa938e) | 128        | \`int[]\` with numbers between [-300, 300] | [circuit 002](/circuits/002.png) | [r3-sort-predefined-int-128-3runs.csv.xz](/measurements/r3-sort-predefined-int-128-3runs.csv.xz)                      |
| 2025-03-04 | R4     | [4969d11](https://github.com/FOSSketeers/embedded-power-analysis/commit/4969d11a8ee73156aef8c8342051aa007cdf312f) | 16         | \`int[]\` with numbers between [INT_MIN, INT_MAX] | [circuit 003](/circuits/003.png) | [r4-sort-predefined-int-16-3runs.csv.xz](/measurements/r4-sort-predefined-int-16-3runs.csv.xz)                        |
| 2025-03-04 | R4     | [af415ce](https://github.com/FOSSketeers/embedded-power-analysis/commit/af415ce2e27084c85236a45270f6709fd90c8bf8) | 32         | \`int[]\` with numbers between [INT_MIN, INT_MAX] | [circuit 003](/circuits/003.png) | [r4-sort-predefined-int-32-3runs.csv.xz](/measurements/r4-sort-predefined-int-32-3runs.csv.xz)                        |
| 2025-03-04 | R4     | [518a092](https://github.com/FOSSketeers/embedded-power-analysis/commit/518a092985e635243be4c9102ac9414d5dab4a7e) | 64         | \`int[]\` with numbers between [INT_MIN, INT_MAX] | [circuit 003](/circuits/003.png) | [r4-sort-predefined-int-64-3runs.csv.xz](/measurements/r4-sort-predefined-int-64-3runs.csv.xz)                        |
| 2025-03-04 | R4     | [b6df94a](https://github.com/FOSSketeers/embedded-power-analysis/commit/b6df94a4d8094156a1e7e64b3c172835c9b0d5e8) | 128        | \`int[]\` with numbers between [INT_MIN, INT_MAX] | [circuit 003](/circuits/003.png) | [r4-sort-predefined-int-128-3runs.csv.xz](/measurements/r4-sort-predefined-int-128-3runs.csv.xz)                      |
| 2025-03-04 | R4     | [cdc5085](https://github.com/FOSSketeers/embedded-power-analysis/commit/cdc5085067e9d04e95498f03f33db73e423168ff) | 256        | \`int[]\` with numbers between [INT_MIN, INT_MAX] | [circuit 003](/circuits/003.png) | [r4-sort-predefined-int-256-3runs.csv.xz](/measurements/r4-sort-predefined-int-256-3runs.csv.xz)                      |
| 2025-03-04 | R4     | [e74dbfd](https://github.com/FOSSketeers/embedded-power-analysis/commit/e74dbfdf7badddda2317800f97aadbae8bdc6847) | 512        | \`int[]\` with numbers between [INT_MIN, INT_MAX] | [circuit 003](/circuits/003.png) | [r4-sort-predefined-int-512-3runs.csv.xz](/measurements/r4-sort-predefined-int-512-3runs.csv.xz)                      |
| 2025-03-04 | R4     | [8e71d10](https://github.com/FOSSketeers/embedded-power-analysis/commit/8e71d100f792c80a5307bec9ab569c6e187a81a4) | 1024       | \`int[]\` with numbers between [INT_MIN, INT_MAX] | [circuit 003](/circuits/003.png) | [r4-sort-predefined-int-1024-3runs.csv.xz](/measurements/r4-sort-predefined-int-1024-3runs.csv.xz)                    |
| 2025-03-05 | R3     | [322cc27](https://github.com/FOSSketeers/embedded-power-analysis/commit/322cc2743d796edfcec3a441f1682c52d09439bb) | 100        | \`int[]\` with numbers between [-300, 300] | **3.3V** [circuit 004](/circuits/004.png) | [r3-sort-predefined-int-100-3runs-3.3v.csv.xz](/measurements/r3-sort-predefined-int-100-3runs-3.3v.csv.xz)                    |

</details>

## 2. crypto

In this benchmark, we evaluate the performance of several cryptographic algorithms by testing different rounds of ChaCha encryption and decryption (8, 12, and 20), various key sizes of AES encryption and decryption (128, 192, and 256). Additionally, we assess AES (128/192/256)-GCM, ChaCha20-Poly1305, as well as Acorn128 and Ascon128 AEAD (authenticated encryption with associated data) scheme.

<details>
<summary>
Click to view the Experiment Log
</summary>

| Date | Device | Commit Hash | Circuit | Measurement |
| ---- | ------ | ------------ | ------- | ----------- |
| 2024-12-03 |  R4  | [65cc397](https://github.com/FOSSketeers/embedded-power-analysis/commit/65cc397122b0b00d1971487c2bf67bac3a54556f) | [circuit 003](/circuits/003.png) | [r4-crypto-digitalout-1runs.csv.xz](/measurements/r4-crypto-digitalout-1runs.csv.xz) |
| 2024-12-04 |  R3  | [e1edc7b](https://github.com/FOSSketeers/embedded-power-analysis/commit/e1edc7b80b04c2694d0e707135cc02af977c1860) | [circuit 002](/circuits/002.png) | [r3-crypto-digitalout-1runs.csv.xz](/measurements/r3-crypto-digitalout-1runs.csv.xz) |
| 2024-12-17 |  R4  | [d486902](https://github.com/FOSSketeers/embedded-power-analysis/commit/d4869026f153a9b9c67de75b82350007d2cf8920) | [circuit 003](/circuits/003.png) | [r4-crypto-digitalout-3runs.csv.xz](/measurements/r4-crypto-digitalout-3runs.csv.xz) |
| 2024-12-17 |  R3  | [d486902](https://github.com/FOSSketeers/embedded-power-analysis/commit/d4869026f153a9b9c67de75b82350007d2cf8920) | [circuit 002](/circuits/002.png) | [r3-crypto-digitalout-3runs.csv.xz](/measurements/r3-crypto-digitalout-3runs.csv.xz) |
| 2024-12-24 |  R4  | [12b211b](https://github.com/FOSSketeers/embedded-power-analysis/commit/12b211bc6bde5cbaa83ed8723d3d837f1d756167) | **3.3V** [circuit 005](/circuits/005.png) | [r4-crypto-digitalout-3runs-3.3v.csv.xz](/measurements/r4-crypto-digitalout-3runs-3.3v.csv.xz) |
| 2024-12-24 |  R3  | [12b211b](https://github.com/FOSSketeers/embedded-power-analysis/commit/12b211bc6bde5cbaa83ed8723d3d837f1d756167) | **3.3V** [circuit 004](/circuits/004.png) | [r3-crypto-digitalout-3runs-3.3v.csv.xz](/measurements/r3-crypto-digitalout-3runs-3.3v.csv.xz) |

</details>

## 3. llm-sort and llm-sort-floating

Here we experiment whether there is a significant difference in the performance of sorting algorithm implementations across different LLMs (ChatGPT 4o, Gemini 1.5 Flash, and Claude 3.5 Haiku). The `llm-sort` benchmark code is used for arrays of integer type, whereas `llm-sort-floating` is used for arrays of floating point type.

<details>
<summary>
Click to view the Experiment Log
</summary>

| Date | Device | Commit Hash | Array Size | Array Type | Array Characteristics | Circuit | Measurement |
| ---- | ------ | ------------ | ---------- | ---------- | ------- | ------- | ----------- |
| 2024-12-03 |  R4  | [65cc397](https://github.com/FOSSketeers/embedded-power-analysis/commit/65cc397122b0b00d1971487c2bf67bac3a54556f) | 100 | `int[]` with numbers between [-300, 300] | Predefined random array generated with [rag](https://github.com/FOSSketeers/embedded-power-analysis/blob/65cc397122b0b00d1971487c2bf67bac3a54556f/random_array_generator.py). | [circuit 003](/circuits/003.png) | [r4-llmsort-predefinedarray-int-100-digitalout-1runs.csv.xz](/measurements/r4-llmsort-predefinedarray-int-100-digitalout-1runs.csv.xz) |
| 2024-12-04 |  R3  | [e1edc7b](https://github.com/FOSSketeers/embedded-power-analysis/commit/e1edc7b80b04c2694d0e707135cc02af977c1860) | 100 | `int[]` with numbers between [-300, 300] | Predefined random array generated with [rag](https://github.com/FOSSketeers/embedded-power-analysis/blob/65cc397122b0b00d1971487c2bf67bac3a54556f/random_array_generator.py). | [circuit 002](/circuits/002.png) | [r3-llmsort-predefinedarray-int-100-digitalout-1runs.csv.xz](/measurements/r3-llmsort-predefinedarray-int-100-digitalout-1runs.csv.xz) |
| 2024-12-17 |  R4  | [d486902](https://github.com/FOSSketeers/embedded-power-analysis/commit/d4869026f153a9b9c67de75b82350007d2cf8920) | 100 | `int[]` with numbers between [-300, 300] | Predefined random array generated with [rag](https://github.com/FOSSketeers/embedded-power-analysis/blob/d4869026f153a9b9c67de75b82350007d2cf8920/random_array_generator.py). | [circuit 003](/circuits/003.png) | [r4-llmsort-predefinedarray-int-100-digitalout-3runs.csv.xz](/measurements/r4-llmsort-predefinedarray-int-100-digitalout-3runs.csv.xz) |
| 2024-12-17 |  R4  | [d486902](https://github.com/FOSSketeers/embedded-power-analysis/commit/d4869026f153a9b9c67de75b82350007d2cf8920) | 50  | `float[]` with numbers between [0, 300]  | Predefined random array generated with [rag](https://github.com/FOSSketeers/embedded-power-analysis/blob/d4869026f153a9b9c67de75b82350007d2cf8920/random_array_generator.py). | [circuit 003](/circuits/003.png) | [r4-llmsortfloat-predefinedarray-float-50-3runs.csv.xz](/measurements/r4-llmsortfloat-predefinedarray-float-50-3runs.csv.xz) |
| 2024-12-17 |  R3  | [d486902](https://github.com/FOSSketeers/embedded-power-analysis/commit/d4869026f153a9b9c67de75b82350007d2cf8920) | 100 | `int[]` with numbers between [-300, 300] | Predefined random array generated with [rag](https://github.com/FOSSketeers/embedded-power-analysis/blob/d4869026f153a9b9c67de75b82350007d2cf8920/random_array_generator.py). | [circuit 002](/circuits/002.png) | [r3-llmsort-predefinedarray-int-100-digitalout-3runs.csv.xz](/measurements/r3-llmsort-predefinedarray-int-100-digitalout-3runs.csv.xz) |
| 2024-12-17 |  R3  | [d486902](https://github.com/FOSSketeers/embedded-power-analysis/commit/d4869026f153a9b9c67de75b82350007d2cf8920) | 50  | `float[]` with numbers between [0, 300]  | Predefined random array generated with [rag](https://github.com/FOSSketeers/embedded-power-analysis/blob/d4869026f153a9b9c67de75b82350007d2cf8920/random_array_generator.py). | [circuit 002](/circuits/002.png) | [r3-llmsortfloat-predefinedarray-float-50-3runs.csv.xz](/measurements/r3-llmsortfloat-predefinedarray-float-50-3runs.csv.xz) |
| 2024-12-17 |  R3  | [d486902](https://github.com/FOSSketeers/embedded-power-analysis/commit/d4869026f153a9b9c67de75b82350007d2cf8920) | 50  | `float[]` with numbers between [0, 300]  | Predefined random array generated with [rag](https://github.com/FOSSketeers/embedded-power-analysis/blob/d4869026f153a9b9c67de75b82350007d2cf8920/random_array_generator.py). | [circuit 002](/circuits/002.png) | [r3-llmsortfloat-predefinedarray-float-50-1runs.csv.xz](/measurements/r3-llmsortfloat-predefinedarray-float-50-1runs.csv.xz) |
| 2024-12-24 |  R4  | [12b211b](https://github.com/FOSSketeers/embedded-power-analysis/commit/12b211bc6bde5cbaa83ed8723d3d837f1d756167) | 100 | `int[]` with numbers between [-300, 300] | Predefined random array generated with [rag](https://github.com/FOSSketeers/embedded-power-analysis/blob/12b211bc6bde5cbaa83ed8723d3d837f1d756167/random_array_generator.py). | **3.3V** [circuit 005](/circuits/005.png) | [r4-llmsort-predefinedarray-int-100-digitalout-3runs-3.3v.csv.xz](/measurements/r4-llmsort-predefinedarray-int-100-digitalout-3runs-3.3v.csv.xz) |
| 2024-12-24 |  R3  | [5a6fa36](https://github.com/FOSSketeers/embedded-power-analysis/commit/5a6fa36db610b2c554bc4f99010ecf1600f5e884) | 100 | `int[]` with numbers between [-300, 300] | Predefined random array generated with [rag](https://github.com/FOSSketeers/embedded-power-analysis/blob/5a6fa36db610b2c554bc4f99010ecf1600f5e884/random_array_generator.py). | **3.3V** [circuit 004](/circuits/004.png) | [r3-llmsort-predefinedarray-int-100-digitalout-3runs-3.3v.csv.xz](/measurements/r3-llmsort-predefinedarray-int-100-digitalout-3runs-3.3v.csv.xz) |
| 2024-12-24 |  R3  | [e25e6e2](https://github.com/FOSSketeers/embedded-power-analysis/commit/e25e6e292ea8481ad1b773c70834b97b55146eea) | 50  | `float[]` with numbers between [0, 300]  | Predefined random array generated with [rag](https://github.com/FOSSketeers/embedded-power-analysis/blob/e25e6e292ea8481ad1b773c70834b97b55146eea/random_array_generator.py). | **3.3V** [circuit 004](/circuits/004.png) | [r3-llmsortfloat-predefinedarray-float-50-3runs-3.3v.csv.xz](/measurements/r3-llmsortfloat-predefinedarray-float-50-3runs-3.3v.csv.xz) |

</details>

## 4. misc

We also gathered a few common algorithms under a miscellaneous category. We picked LCG (Linear Congruential Generator) and MT19937 (Mersenne Twister) PRNGs (Pseudo-random Number Generator), linear and binary search, matrix multiplication, binary GCD (Greatest Common Divisor), Dijkstra, Karatsuba multiplication, iterative and recursive versions of fibonacci and factorial and a basic sum operation as a mixed representation of commonly used algorithms in programs.

<details>
<summary>
Click to view the Experiment Log
</summary>

| Date | Device | Commit Hash | Circuit | Measurement |
| ---- | ------ | ----------- | ------- | ----------- |
| 2025-03-04 |  R4  | [47eda78](https://github.com/FOSSketeers/embedded-power-analysis/commit/47eda78df7b9c80c2dc859b4000f77bcd776cb75) | [circuit 003](/circuits/003.png) | [r4-misc-10runs.csv.xz](/measurements/r4-misc-10runs.csv.xz) |
| 2025-03-04 |  R3  | [7571754](https://github.com/FOSSketeers/embedded-power-analysis/commit/75717541ee8100f1278c13dbfc522658bc6c8b3b) | [circuit 002](/circuits/002.png) | [r3-misc-10runs.csv.xz](/measurements/r3-misc-10runs.csv.xz) |

</details>

## 5. instruction

lorem ipsum

<details>
<summary>
Click to view the Experiment Log
</summary>

| Date | Device | Commit Hash | Circuit | Measurement |
| ---- | ------ | ----------- | ------- | ----------- |
| 2025-04-15 |  R3  | [3fbeec3](https://github.com/FOSSketeers/embedded-power-analysis/commit/3fbeec3f55c914022334e9f5e9439e9762860515) | [circuit 002](/circuits/002.png) | [r3-instruction-30000-0xFF-3runs.csv.xz](/measurements/r3-instruction-30000-0xFF-3runs.csv.xz) |
| 2025-04-15 |  R3  | [cff6a11](https://github.com/FOSSketeers/embedded-power-analysis/commit/cff6a114c2d204d45b4e29cb5dcff63ab04f55fe) | [circuit 002](/circuits/002.png) | [r3-instruction-30000-0xFF-isolatedstate-3runs.csv.xz](/measurements/r3-instruction-30000-0xFF-isolatedstate-3runs.csv.xz) |

</details>
