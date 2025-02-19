#ifndef _UTIL_UTIL_H
#define _UTIL_UTIL_H

#include <Arduino.h>
#include <stdint.h>

#ifndef SERIAL_OUTPUT
#define SERIAL_OUTPUT 0
#endif

void _CommonInitializer() {
#if SERIAL_OUTPUT
    Serial.begin(9600);
#endif

#if defined(__AVR_ATmega328P__)  // Arduino Uno R3
    pinMode(2, OUTPUT);          // PD2
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);  // PB0
    pinMode(9, OUTPUT);  // PB1
#else                    // Arduino Uno R4 Minima
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(18, OUTPUT);
    pinMode(19, OUTPUT);
#endif
    delay(500);
}

#if defined(__AVR_ATmega328P__)

#define setState(num, name) \
    do { \
        static_assert(num < 256); \
        if constexpr (SERIAL_OUTPUT) Serial.println("Running stage " name); \
        PORTD = (num << 2); \
        PORTB = (num >> 6) & 0x03; \
    } while (0)

#else

#define setState(num, name) \
    do { \
        static_assert(num < 256); \
        if constexpr (SERIAL_OUTPUT) Serial.println("Running stage " name); \
        R_PORT1->PODR = num; \
    } while (0)

#endif  // defined(__AVR_ATmega328P__)

namespace util {
// Taken from https://en.cppreference.com/w/cpp/algorithm/equal
template<class InputIt1, class InputIt2>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2) {
    for (; first1 != last1; ++first1, ++first2) {
        if (!(*first1 == *first2)) {
            return false;
        }
    }

    return true;
}

template<class T, size_t N>
constexpr size_t size(const T (&array)[N]) noexcept {
    return N;
}

template< class T, size_t N >
T* begin(T (&array)[N]) {
    return array;
}

template< class T, size_t N >
T* end(T (&array)[N]) {
    return array + N;
}
}

#endif  // _UTIL_UTIL_H