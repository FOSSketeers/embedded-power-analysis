#include <Arduino.h>

#include <util.h>


void runBenchmark() {
    if constexpr (SERIAL_OUTPUT)
        Serial.println("Starting benchmark...");
    setState(0, "idle");

    #if defined(__AVR_ATmega328P__) // Arduino Uno R3

    for (int i = 0; i < 100; i++) {
        // 1. NOP (No operation)
        setState(1, "nop");
        asm volatile("nop");
    }

    for (int i = 0; i < 100; i++) {
        // 2. LDI (Load immediate)
        setState(2, "ldi");
        asm volatile("ldi r16, 0xFF");
    }

    for (int i = 0; i < 100; i++) {
        // 3. MOV (Move register to register)
        setState(3, "mov");
        asm volatile("mov r17, r16");
    }

    for (int i = 0; i < 100; i++) {
        // 4. ADD (Add registers)
        setState(4, "add");
        asm volatile("add r18, r19");
    }

    for (int i = 0; i < 100; i++) {
        // 5. SUB (Subtract registers)
        setState(5, "sub");
        asm volatile("sub r20, r21");
    }

    for (int i = 0; i < 100; i++) {
        // 6. AND (Bitwise AND)
        setState(6, "and");
        asm volatile("and r22, r23");
    }

    for (int i = 0; i < 100; i++) {
        // 7. OR (Bitwise OR)
        setState(7, "or");
        asm volatile("or r24, r25");
    }

    for (int i = 0; i < 100; i++) {
        // 8. EOR (Exclusive OR)
        setState(8, "eor");
        asm volatile("eor r26, r27");
    }

    for (int i = 0; i < 100; i++) {
        // 9. INC (Increment)
        setState(9, "inc");
        asm volatile("inc r28");
    }

    for (int i = 0; i < 100; i++) {
        // 10. DEC (Decrement)
        setState(10, "dec");
        asm volatile("dec r29");
    }

    #else                           // Arduino Uno R4 Minima
        // Empty for now
    #endif
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

void loop() {}
