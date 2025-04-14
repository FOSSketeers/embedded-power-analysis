#include <Arduino.h>

#include <util.h>

constexpr static int32_t LOOP_COUNT = 30000;

void runBenchmark() {
    if constexpr (SERIAL_OUTPUT)
        Serial.println("Starting benchmark...");
    setState(0, "idle");

    // Save registers
    asm volatile("push r16");
    asm volatile("push r17");
    asm volatile("push r18");
    asm volatile("push r19");
    asm volatile("push r20");
    asm volatile("push r21");
    asm volatile("push r22");
    asm volatile("push r23");
    asm volatile("push r24");
    asm volatile("push r25");
    asm volatile("push r26");
    asm volatile("push r27");
    asm volatile("push r28");
    asm volatile("push r29");
    asm volatile("push r30");
    asm volatile("push r31");


    #if defined(__AVR_ATmega328P__) // Arduino Uno R3

    // 1. NOP (No operation)
    setState(1, "nop");
    for (int i = 0; i < LOOP_COUNT; i++) {
        asm volatile("nop");
    }
    setState(0, "idle");
    delay(ALGORITHM_DELAY);

    // 2. LDI (Load immediate)
    setState(2, "ldi");
    for (int i = 0; i < LOOP_COUNT; i++) {

        asm volatile("ldi r16, 0xFF");
    }
    setState(0, "idle");
    delay(ALGORITHM_DELAY);

    // 3. MOV (Move register to register)
    setState(3, "mov");
    for (int i = 0; i < LOOP_COUNT; i++) {
        asm volatile("mov r16, r17");
    }
    setState(0, "idle");
    delay(ALGORITHM_DELAY);

    // 4. ADD (Add registers)
    setState(4, "add");
    for (int i = 0; i < LOOP_COUNT; i++) {
        asm volatile("add r16, r17");
    }
    setState(0, "idle");
    delay(ALGORITHM_DELAY);

    // 5. SUB (Subtract registers)
    setState(5, "sub");
    for (int i = 0; i < LOOP_COUNT; i++) {
        asm volatile("sub r16, r17");
    }
    setState(0, "idle");
    delay(ALGORITHM_DELAY);

    // 6. AND (Bitwise AND)
    setState(6, "and");
    for (int i = 0; i < LOOP_COUNT; i++) {
        asm volatile("and r16, r17");
    }
    setState(0, "idle");
    delay(ALGORITHM_DELAY);

    // 7. OR (Bitwise OR)
    setState(7, "or");
    for (int i = 0; i < LOOP_COUNT; i++) {
        asm volatile("or r16, r17");
    }
    setState(0, "idle");
    delay(ALGORITHM_DELAY);

    // 8. EOR (Exclusive OR)
    setState(8, "eor");
    for (int i = 0; i < LOOP_COUNT; i++) {
        asm volatile("eor r16, r17");
    }
    setState(0, "idle");
    delay(ALGORITHM_DELAY);

    // 9. INC (Increment)
    setState(9, "inc");
    for (int i = 0; i < LOOP_COUNT; i++) {
        asm volatile("inc r16");
    }
    setState(0, "idle");
    delay(ALGORITHM_DELAY);

    // 10. DEC (Decrement)
    setState(10, "dec");
    for (int i = 0; i < LOOP_COUNT; i++) {
        asm volatile("dec r16");
    }
    setState(0, "idle");
    delay(ALGORITHM_DELAY);

    // 11. MUL (Multiply r16 * r17 → result in r0:r1)
    setState(11, "mul");
    for (int i = 0; i < LOOP_COUNT; i++) {
        asm volatile("mul r17, r18");
    }
    setState(0, "idle");
    delay(ALGORITHM_DELAY);

    // 12. LSL (Logical Shift Left)
    setState(12, "lsl");
    for (int i = 0; i < LOOP_COUNT; i++) {
        asm volatile("lsl r16");
    }
    setState(0, "idle");
    delay(ALGORITHM_DELAY);

    // 13. LSR (Logical Shift Right)
    setState(13, "lsr");
    for (int i = 0; i < LOOP_COUNT; i++) {
        asm volatile("lsr r16");
    }
    setState(0, "idle");
    delay(ALGORITHM_DELAY);

    // 14. ROR (Arithmetic Shift Right)
    setState(14, "asr");
    for (int i = 0; i < LOOP_COUNT; i++) {
        asm volatile("asr r16");
    }
    setState(0, "idle");
    delay(ALGORITHM_DELAY);

    // 15. ROR (Rotate Right Through Right)
    setState(15, "ror");
    for (int i = 0; i < LOOP_COUNT; i++) {
        asm volatile("ror r16");
    }
    setState(0, "idle");
    delay(ALGORITHM_DELAY);

    // 16. NEG (Negate two's complement)
    setState(16, "neg");
    for (int i = 0; i < LOOP_COUNT; i++) {
        asm volatile("neg r16");
    }
    setState(0, "idle");
    delay(ALGORITHM_DELAY);

    // 17. COM (One's complement)
    setState(17, "com");
    for (int i = 0; i < LOOP_COUNT; i++) {
        asm volatile("com r16");
    }
    setState(0, "idle");
    delay(ALGORITHM_DELAY);

    // 18. SBRC (Skip if Bit in Register Cleared - adds branching)
    setState(18, "sbrc");
    for (int i = 0; i < LOOP_COUNT; i++) {
        asm volatile(
            "sbrc r16, 0\n\t"  // Skip next if bit 0 of r16 is cleared
            "nop"
        );
    }
    setState(0, "idle");
    delay(ALGORITHM_DELAY);

    // 19. MULS (Signed × Signed)
    setState(19, "muls");
    for (int i = 0; i < LOOP_COUNT; i++) {
        asm volatile("muls r16, r17");
    }
    setState(0, "idle");
    delay(ALGORITHM_DELAY);

    // 20. MULSU (Signed × Unsigned)
    setState(20, "mulsu");
    for (int i = 0; i < LOOP_COUNT; i++) {
        asm volatile("mulsu r16, r17");
    }
    setState(0, "idle");
    delay(ALGORITHM_DELAY);

    // 21. FMUL (Unsigned Fractional ×2)
    setState(21, "fmul");
    for (int i = 0; i < LOOP_COUNT; i++) {
        asm volatile("fmul r16, r17");
    }
    setState(0, "idle");
    delay(ALGORITHM_DELAY);

    // 22. FMULS (Signed Fractional ×2)
    setState(22, "fmuls");
    for (int i = 0; i < LOOP_COUNT; i++) {
        asm volatile("fmuls r16, r17");
    }
    setState(0, "idle");
    delay(ALGORITHM_DELAY);

    // 23. FMULSU (Signed × Unsigned Fractional ×2)
    setState(23, "fmulsu");
    for (int i = 0; i < LOOP_COUNT; i++) {
        asm volatile("fmulsu r16, r17");
    }
    setState(0, "idle");
    delay(ALGORITHM_DELAY);

    // 24. STS (Store direct to SRAM address)
    setState(24, "sts");
    for (int i = 0; i < LOOP_COUNT; i++) {
        asm volatile("sts 0x0100, r16");
    }
    setState(0, "idle");
    delay(ALGORITHM_DELAY);

    // 25. STD Y+1 (Store via Y pointer with displacement)
    asm volatile(
        "ldi r28, 0x00\n\t"   // Y low byte
        "ldi r29, 0x01"       // Y high byte → Y = 0x0100
    );
    setState(25, "std_y+1");
    for (int i = 0; i < LOOP_COUNT; i++) {
        asm volatile("std Y+1, r16");
    }
    setState(0, "idle");
    delay(ALGORITHM_DELAY);


    #else                           // Arduino Uno R4 Minima
        // Empty for now
    #endif

    asm volatile("pop r31");
    asm volatile("pop r30");
    asm volatile("pop r29");
    asm volatile("pop r28");
    asm volatile("pop r27");
    asm volatile("pop r26");
    asm volatile("pop r25");
    asm volatile("pop r24");
    asm volatile("pop r23");
    asm volatile("pop r22");
    asm volatile("pop r21");
    asm volatile("pop r20");
    asm volatile("pop r19");
    asm volatile("pop r18");
    asm volatile("pop r17");
    asm volatile("pop r16");

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
        Serial.println(i);
    }

    setState(255, "finish");
    digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {}
