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
    for (int i = 0; i < LOOP_COUNT; i++) {
        setState(1, "nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        setState(0, "idle");
    }
    delay(ALGORITHM_DELAY);

    // 2. LDI (Load immediate)
    for (int i = 0; i < LOOP_COUNT; i++) {
        setState(2, "ldi");
        asm volatile("ldi r21, 0xFF");
        asm volatile("ldi r21, 0xFF");
        asm volatile("ldi r21, 0xFF");
        asm volatile("ldi r21, 0xFF");
        asm volatile("ldi r21, 0xFF");
        asm volatile("ldi r21, 0xFF");
        asm volatile("ldi r21, 0xFF");
        asm volatile("ldi r21, 0xFF");
        asm volatile("ldi r21, 0xFF");
        asm volatile("ldi r21, 0xFF");
        setState(0, "idle");
    }
    delay(ALGORITHM_DELAY);

    // 3. MOV (Move register to register)
    for (int i = 0; i < LOOP_COUNT; i++) {
        setState(3, "mov");
        asm volatile("mov r21, r22");
        asm volatile("mov r21, r22");
        asm volatile("mov r21, r22");
        asm volatile("mov r21, r22");
        asm volatile("mov r21, r22");
        asm volatile("mov r21, r22");
        asm volatile("mov r21, r22");
        asm volatile("mov r21, r22");
        asm volatile("mov r21, r22");
        asm volatile("mov r21, r22");
        setState(0, "idle");
    }
    delay(ALGORITHM_DELAY);

    // 4. ADD (Add registers)
    for (int i = 0; i < LOOP_COUNT; i++) {
        setState(4, "add");
        asm volatile("add r21, r22");
        asm volatile("add r21, r22");
        asm volatile("add r21, r22");
        asm volatile("add r21, r22");
        asm volatile("add r21, r22");
        asm volatile("add r21, r22");
        asm volatile("add r21, r22");
        asm volatile("add r21, r22");
        asm volatile("add r21, r22");
        asm volatile("add r21, r22");
        setState(0, "idle");
    }
    delay(ALGORITHM_DELAY);

    // 5. SUB (Subtract registers)
    for (int i = 0; i < LOOP_COUNT; i++) {
        setState(5, "sub");
        asm volatile("sub r21, r22");
        asm volatile("sub r21, r22");
        asm volatile("sub r21, r22");
        asm volatile("sub r21, r22");
        asm volatile("sub r21, r22");
        asm volatile("sub r21, r22");
        asm volatile("sub r21, r22");
        asm volatile("sub r21, r22");
        asm volatile("sub r21, r22");
        asm volatile("sub r21, r22");
        setState(0, "idle");
    }
    delay(ALGORITHM_DELAY);

    // 6. AND (Bitwise AND)
    for (int i = 0; i < LOOP_COUNT; i++) {
        setState(6, "and");
        asm volatile("and r21, r22");
        asm volatile("and r21, r22");
        asm volatile("and r21, r22");
        asm volatile("and r21, r22");
        asm volatile("and r21, r22");
        asm volatile("and r21, r22");
        asm volatile("and r21, r22");
        asm volatile("and r21, r22");
        asm volatile("and r21, r22");
        asm volatile("and r21, r22");
        setState(0, "idle");
    }
    delay(ALGORITHM_DELAY);

    // 7. OR (Bitwise OR)
    for (int i = 0; i < LOOP_COUNT; i++) {
        setState(7, "or");
        asm volatile("or r21, r22");
        asm volatile("or r21, r22");
        asm volatile("or r21, r22");
        asm volatile("or r21, r22");
        asm volatile("or r21, r22");
        asm volatile("or r21, r22");
        asm volatile("or r21, r22");
        asm volatile("or r21, r22");
        asm volatile("or r21, r22");
        asm volatile("or r21, r22");
        setState(0, "idle");
    }
    delay(ALGORITHM_DELAY);

    // 8. EOR (Exclusive OR)
    for (int i = 0; i < LOOP_COUNT; i++) {
        setState(8, "eor");
        asm volatile("eor r21, r22");
        asm volatile("eor r21, r22");
        asm volatile("eor r21, r22");
        asm volatile("eor r21, r22");
        asm volatile("eor r21, r22");
        asm volatile("eor r21, r22");
        asm volatile("eor r21, r22");
        asm volatile("eor r21, r22");
        asm volatile("eor r21, r22");
        asm volatile("eor r21, r22");
        setState(0, "idle");
    }
    delay(ALGORITHM_DELAY);

    // 9. INC (Increment)
    for (int i = 0; i < LOOP_COUNT; i++) {
        setState(9, "inc");
        asm volatile("inc r21");
        asm volatile("inc r21");
        asm volatile("inc r21");
        asm volatile("inc r21");
        asm volatile("inc r21");
        asm volatile("inc r21");
        asm volatile("inc r21");
        asm volatile("inc r21");
        asm volatile("inc r21");
        asm volatile("inc r21");
        setState(0, "idle");
    }
    delay(ALGORITHM_DELAY);

    // 10. DEC (Decrement)
    for (int i = 0; i < LOOP_COUNT; i++) {
        setState(10, "dec");
        asm volatile("dec r21");
        asm volatile("dec r21");
        asm volatile("dec r21");
        asm volatile("dec r21");
        asm volatile("dec r21");
        asm volatile("dec r21");
        asm volatile("dec r21");
        asm volatile("dec r21");
        asm volatile("dec r21");
        asm volatile("dec r21");
        setState(0, "idle");
    }
    delay(ALGORITHM_DELAY);

    // 11. MUL (Multiply r21 * r22 → result in r0:r1)
    for (int i = 0; i < LOOP_COUNT; i++) {
        setState(11, "mul");
        asm volatile("mul r22, r18");
        asm volatile("mul r22, r18");
        asm volatile("mul r22, r18");
        asm volatile("mul r22, r18");
        asm volatile("mul r22, r18");
        asm volatile("mul r22, r18");
        asm volatile("mul r22, r18");
        asm volatile("mul r22, r18");
        asm volatile("mul r22, r18");
        asm volatile("mul r22, r18");
        setState(0, "idle");
    }
    delay(ALGORITHM_DELAY);

    // 12. LSL (Logical Shift Left)
    for (int i = 0; i < LOOP_COUNT; i++) {
        setState(12, "lsl");
        asm volatile("lsl r21");
        asm volatile("lsl r21");
        asm volatile("lsl r21");
        asm volatile("lsl r21");
        asm volatile("lsl r21");
        asm volatile("lsl r21");
        asm volatile("lsl r21");
        asm volatile("lsl r21");
        asm volatile("lsl r21");
        asm volatile("lsl r21");
        setState(0, "idle");
    }
    delay(ALGORITHM_DELAY);

    // 13. LSR (Logical Shift Right)
    for (int i = 0; i < LOOP_COUNT; i++) {
        setState(13, "lsr");
        asm volatile("lsr r21");
        asm volatile("lsr r21");
        asm volatile("lsr r21");
        asm volatile("lsr r21");
        asm volatile("lsr r21");
        asm volatile("lsr r21");
        asm volatile("lsr r21");
        asm volatile("lsr r21");
        asm volatile("lsr r21");
        asm volatile("lsr r21");
        setState(0, "idle");
    }
    delay(ALGORITHM_DELAY);

    // 14. ASR (Arithmetic Shift Right)
    for (int i = 0; i < LOOP_COUNT; i++) {
        setState(14, "asr");
        asm volatile("asr r21");
        asm volatile("asr r21");
        asm volatile("asr r21");
        asm volatile("asr r21");
        asm volatile("asr r21");
        asm volatile("asr r21");
        asm volatile("asr r21");
        asm volatile("asr r21");
        asm volatile("asr r21");
        asm volatile("asr r21");
        setState(0, "idle");
    }
    delay(ALGORITHM_DELAY);

    // 15. ROR (Rotate Right Through Right)
    for (int i = 0; i < LOOP_COUNT; i++) {
        setState(15, "ror");
        asm volatile("ror r21");
        asm volatile("ror r21");
        asm volatile("ror r21");
        asm volatile("ror r21");
        asm volatile("ror r21");
        asm volatile("ror r21");
        asm volatile("ror r21");
        asm volatile("ror r21");
        asm volatile("ror r21");
        asm volatile("ror r21");
        setState(0, "idle");
    }
    delay(ALGORITHM_DELAY);

    // 16. NEG (Negate two's complement)
    for (int i = 0; i < LOOP_COUNT; i++) {
        setState(16, "neg");
        asm volatile("neg r21");
        asm volatile("neg r21");
        asm volatile("neg r21");
        asm volatile("neg r21");
        asm volatile("neg r21");
        asm volatile("neg r21");
        asm volatile("neg r21");
        asm volatile("neg r21");
        asm volatile("neg r21");
        asm volatile("neg r21");
        setState(0, "idle");
    }
    delay(ALGORITHM_DELAY);

    // 17. COM (One's complement)
    for (int i = 0; i < LOOP_COUNT; i++) {
        setState(17, "com");
        asm volatile("com r21");
        asm volatile("com r21");
        asm volatile("com r21");
        asm volatile("com r21");
        asm volatile("com r21");
        asm volatile("com r21");
        asm volatile("com r21");
        asm volatile("com r21");
        asm volatile("com r21");
        asm volatile("com r21");
        setState(0, "idle");
    }
    delay(ALGORITHM_DELAY);

    // 18. SBRC (Skip if Bit in Register Cleared - adds branching)
    for (int i = 0; i < LOOP_COUNT; i++) {
        setState(18, "sbrc");
        asm volatile(
            "sbrc r21, 0\n\t"  // Skip next if bit 0 of r21 is cleared
            "nop"
        );
        asm volatile(
            "sbrc r21, 0\n\t"  // Skip next if bit 0 of r21 is cleared
            "nop"
        );
        asm volatile(
            "sbrc r21, 0\n\t"  // Skip next if bit 0 of r21 is cleared
            "nop"
        );
        asm volatile(
            "sbrc r21, 0\n\t"  // Skip next if bit 0 of r21 is cleared
            "nop"
        );
        asm volatile(
            "sbrc r21, 0\n\t"  // Skip next if bit 0 of r21 is cleared
            "nop"
        );
        asm volatile(
            "sbrc r21, 0\n\t"  // Skip next if bit 0 of r21 is cleared
            "nop"
        );
        asm volatile(
            "sbrc r21, 0\n\t"  // Skip next if bit 0 of r21 is cleared
            "nop"
        );
        asm volatile(
            "sbrc r21, 0\n\t"  // Skip next if bit 0 of r21 is cleared
            "nop"
        );
        asm volatile(
            "sbrc r21, 0\n\t"  // Skip next if bit 0 of r21 is cleared
            "nop"
        );
        asm volatile(
            "sbrc r21, 0\n\t"  // Skip next if bit 0 of r21 is cleared
            "nop"
        );
        setState(0, "idle");
    }
    delay(ALGORITHM_DELAY);

    // 19. MULS (Signed × Signed)
    for (int i = 0; i < LOOP_COUNT; i++) {
        setState(19, "muls");
        asm volatile("muls r21, r22");
        asm volatile("muls r21, r22");
        asm volatile("muls r21, r22");
        asm volatile("muls r21, r22");
        asm volatile("muls r21, r22");
        asm volatile("muls r21, r22");
        asm volatile("muls r21, r22");
        asm volatile("muls r21, r22");
        asm volatile("muls r21, r22");
        asm volatile("muls r21, r22");
        setState(0, "idle");
    }
    delay(ALGORITHM_DELAY);

    // 20. MULSU (Signed × Unsigned)
    for (int i = 0; i < LOOP_COUNT; i++) {
        setState(20, "mulsu");
        asm volatile("mulsu r21, r22");
        asm volatile("mulsu r21, r22");
        asm volatile("mulsu r21, r22");
        asm volatile("mulsu r21, r22");
        asm volatile("mulsu r21, r22");
        asm volatile("mulsu r21, r22");
        asm volatile("mulsu r21, r22");
        asm volatile("mulsu r21, r22");
        asm volatile("mulsu r21, r22");
        asm volatile("mulsu r21, r22");
        setState(0, "idle");
    }
    delay(ALGORITHM_DELAY);

    // 21. FMUL (Unsigned Fractional ×2)
    for (int i = 0; i < LOOP_COUNT; i++) {
        setState(21, "fmul");
        asm volatile("fmul r21, r22");
        asm volatile("fmul r21, r22");
        asm volatile("fmul r21, r22");
        asm volatile("fmul r21, r22");
        asm volatile("fmul r21, r22");
        asm volatile("fmul r21, r22");
        asm volatile("fmul r21, r22");
        asm volatile("fmul r21, r22");
        asm volatile("fmul r21, r22");
        asm volatile("fmul r21, r22");
        setState(0, "idle");
    }
    delay(ALGORITHM_DELAY);

    // 22. FMULS (Signed Fractional ×2)
    for (int i = 0; i < LOOP_COUNT; i++) {
        setState(22, "fmuls");
        asm volatile("fmuls r21, r22");
        asm volatile("fmuls r21, r22");
        asm volatile("fmuls r21, r22");
        asm volatile("fmuls r21, r22");
        asm volatile("fmuls r21, r22");
        asm volatile("fmuls r21, r22");
        asm volatile("fmuls r21, r22");
        asm volatile("fmuls r21, r22");
        asm volatile("fmuls r21, r22");
        asm volatile("fmuls r21, r22");
        setState(0, "idle");
    }
    delay(ALGORITHM_DELAY);

    // 23. FMULSU (Signed × Unsigned Fractional ×2)
    for (int i = 0; i < LOOP_COUNT; i++) {
        setState(23, "fmulsu");
        asm volatile("fmulsu r21, r22");
        asm volatile("fmulsu r21, r22");
        asm volatile("fmulsu r21, r22");
        asm volatile("fmulsu r21, r22");
        asm volatile("fmulsu r21, r22");
        asm volatile("fmulsu r21, r22");
        asm volatile("fmulsu r21, r22");
        asm volatile("fmulsu r21, r22");
        asm volatile("fmulsu r21, r22");
        asm volatile("fmulsu r21, r22");
        setState(0, "idle");
    }
    delay(ALGORITHM_DELAY);

    // 24. STS (Store direct to SRAM address)
    for (int i = 0; i < LOOP_COUNT; i++) {
        setState(24, "sts");
        asm volatile("sts 0x0100, r21");
        asm volatile("sts 0x0100, r21");
        asm volatile("sts 0x0100, r21");
        asm volatile("sts 0x0100, r21");
        asm volatile("sts 0x0100, r21");
        asm volatile("sts 0x0100, r21");
        asm volatile("sts 0x0100, r21");
        asm volatile("sts 0x0100, r21");
        asm volatile("sts 0x0100, r21");
        asm volatile("sts 0x0100, r21");
        setState(0, "idle");
    }
    delay(ALGORITHM_DELAY);

    // 25. STD Y+1 (Store via Y pointer with displacement)
    asm volatile(
        "ldi r28, 0x00\n\t"   // Y low byte
        "ldi r29, 0x01"       // Y high byte → Y = 0x0100
    );
    for (int i = 0; i < LOOP_COUNT; i++) {
        setState(25, "std_y+1");
        asm volatile("std Y+1, r21");
        asm volatile("std Y+1, r21");
        asm volatile("std Y+1, r21");
        asm volatile("std Y+1, r21");
        asm volatile("std Y+1, r21");
        asm volatile("std Y+1, r21");
        asm volatile("std Y+1, r21");
        asm volatile("std Y+1, r21");
        asm volatile("std Y+1, r21");
        asm volatile("std Y+1, r21");
        setState(0, "idle");
    }
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
