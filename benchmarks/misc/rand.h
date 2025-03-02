#include <stdint.h>

// ===== MT19937 =====

// Reduced for memory.
#define MT19937_N 32
#define MT19937_M 16
#define MT19937_MATRIX_A 0x9908b0dfU
#define MT19937_UPPER_MASK 0x80000000U
#define MT19937_LOWER_MASK 0x7fffffffU

static uint32_t mt[MT19937_N]; // State vector
static int mt_index = MT19937_N + 1; // Index for the state vector

void mt19937_init(uint32_t seed) {
    mt[0] = seed & 0xffffffff;
    for (int i = 1; i < MT19937_N; i++) {
        mt[i] = (1812433253U * (mt[i - 1] ^ (mt[i - 1] >> 30)) + i);
        mt[i] &= 0xffffffff;
    }
    mt_index = MT19937_N;
}

uint32_t mt19937_rand() {
    if (mt_index >= MT19937_N) {
        int i;
        for (i = 0; i < MT19937_N - MT19937_M; i++) {
            uint32_t y = (mt[i] & MT19937_UPPER_MASK) | (mt[i + 1] & MT19937_LOWER_MASK);
            mt[i] = mt[i + MT19937_M] ^ (y >> 1) ^ ((y & 1) ? MT19937_MATRIX_A : 0);
        }
        for (; i < MT19937_N - 1; i++) {
            uint32_t y = (mt[i] & MT19937_UPPER_MASK) | (mt[i + 1] & MT19937_LOWER_MASK);
            mt[i] = mt[i + (MT19937_M - MT19937_N)] ^ (y >> 1) ^ ((y & 1) ? MT19937_MATRIX_A : 0);
        }
        uint32_t y = (mt[MT19937_N - 1] & MT19937_UPPER_MASK) | (mt[0] & MT19937_LOWER_MASK);
        mt[MT19937_N - 1] = mt[MT19937_M - 1] ^ (y >> 1) ^ ((y & 1) ? MT19937_MATRIX_A : 0);

        mt_index = 0;
    }

    uint32_t y = mt[mt_index++];
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680U;
    y ^= (y << 15) & 0xefc60000U;
    y ^= (y >> 18);

    return y;
}

// ===== LCG =====

#define LCG_A 1664525U
#define LCG_C 1013904223U
#define LCG_M 0xFFFFFFFFU

static uint32_t lcg_state = 0;

void lcg_init(uint32_t seed) {
    lcg_state = seed & LCG_M;
}

uint32_t lcg_rand() {
    lcg_state = (LCG_A * lcg_state + LCG_C) & LCG_M;
    return lcg_state;
}
