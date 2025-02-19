#include <Arduino.h>
#include <stdint.h>

#include <util.h>

#include <Acorn128.h>
#include <Ascon128.h>
#include <AES.h>
#include <ChaCha.h>
#include <ChaChaPoly.h>
#include <GCM.h>

const bool CHECK_CORRECTNESS = false;
static_assert(!CHECK_CORRECTNESS || SERIAL_OUTPUT, "Correctness check is meaningless without serial output.");
const int EXPERIMENT_REPETITION = 3;
const int EXPERIMENT_DELAY = 2000;
const int ALGORITHM_DELAY = 1500;

const uint8_t message[32] = "Lorem ipsum dolor sit amet, con";                                                                                                                                                                  // -1 for NUL terminator
const uint8_t key128[16] = { 0xac, 0x9f, 0xc8, 0x33, 0xc9, 0x6e, 0x73, 0x47, 0xf2, 0xb1, 0xda, 0xe8, 0x32, 0xae, 0x54, 0x79 };                                                                                                  // first 16 bytes of sha256("symmetric")
const uint8_t key192[24] = { 0xac, 0x9f, 0xc8, 0x33, 0xc9, 0x6e, 0x73, 0x47, 0xf2, 0xb1, 0xda, 0xe8, 0x32, 0xae, 0x54, 0x79, 0x5a, 0x31, 0x0a, 0xae, 0xb8, 0x3e, 0x18, 0xc0 };                                                  // first 24 bytes of sha256("symmetric")
const uint8_t key256[32] = { 0xac, 0x9f, 0xc8, 0x33, 0xc9, 0x6e, 0x73, 0x47, 0xf2, 0xb1, 0xda, 0xe8, 0x32, 0xae, 0x54, 0x79, 0x5a, 0x31, 0x0a, 0xae, 0xb8, 0x3e, 0x18, 0xc0, 0x6d, 0xdf, 0x28, 0xd5, 0x7f, 0xe3, 0x3f, 0xf2 };  // 32 bytes of sha256("symmetric")
const uint8_t iv64[8] = { 0x0a, 0xb3, 0x06, 0x82, 0x30, 0x35, 0x66, 0x1b };                                                                                                                                                     // first 8 bytes of sha256("iv")
const uint8_t iv96[12] = { 0x0a, 0xb3, 0x06, 0x82, 0x30, 0x35, 0x66, 0x1b, 0xb8, 0xdb, 0xa2, 0x1c };                                                                                                                            // first 12 bytes of sha256("iv")
const uint8_t iv128[16] = { 0x0a, 0xb3, 0x06, 0x82, 0x30, 0x35, 0x66, 0x1b, 0xb8, 0xdb, 0xa2, 0x1c, 0xc2, 0x53, 0x52, 0x31 };                                                                                                   // first 16 bytes of sha256("iv")


void runBenchmark() {
    setState(0, "idle");

    uint8_t enc_buffer[32] = { 0 };
    uint8_t dec_buffer[32] = { 0 };
    uint8_t tag_buffer[16] = { 0 };

    // ======== Building blocks ========

    // ==== ChaCha ====
    {
        setState(1, "chacha8");
        ChaCha chacha8(8);
        chacha8.setKey(key128, util::size(key128));
        chacha8.setIV(iv64, util::size(iv64));
        chacha8.encrypt(enc_buffer, message, util::size(message));

        ChaCha chacha8d(8);
        chacha8d.setKey(key128, util::size(key128));
        chacha8d.setIV(iv64, util::size(iv64));
        chacha8d.decrypt(dec_buffer, enc_buffer, util::size(message));

        if constexpr (CHECK_CORRECTNESS) {
            if (!util::equal(util::begin(dec_buffer), util::end(dec_buffer), util::begin(message))) {
                Serial.println("ERROR: ChaCha8 failed correctness test!");
            }
        }
    }

    setState(0, "idle");
    delay(ALGORITHM_DELAY);

    {
        setState(2, "chacha12");
        ChaCha chacha12(12);
        chacha12.setKey(key128, util::size(key128));
        chacha12.setIV(iv64, util::size(iv64));
        chacha12.encrypt(enc_buffer, message, util::size(message));

        ChaCha chacha12d(12);
        chacha12d.setKey(key128, util::size(key128));
        chacha12d.setIV(iv64, util::size(iv64));
        chacha12d.decrypt(dec_buffer, enc_buffer, util::size(message));

        if constexpr (CHECK_CORRECTNESS) {
            if (!util::equal(util::begin(dec_buffer), util::end(dec_buffer), util::begin(message))) {
                Serial.println("ERROR: ChaCha12 failed correctness test!");
            }
        }
    }

    setState(0, "idle");
    delay(ALGORITHM_DELAY);

    {
        setState(3, "chacha20");
        ChaCha chacha20(20);
        chacha20.setKey(key256, util::size(key256));
        chacha20.setIV(iv96, util::size(iv96));
        chacha20.encrypt(enc_buffer, message, util::size(message));

        ChaCha chacha20d(20);
        chacha20d.setKey(key256, util::size(key256));
        chacha20d.setIV(iv96, util::size(iv96));
        chacha20d.decrypt(dec_buffer, enc_buffer, util::size(message));

        if constexpr (CHECK_CORRECTNESS) {
            if (!util::equal(util::begin(dec_buffer), util::end(dec_buffer), util::begin(message))) {
                Serial.println("ERROR: ChaCha20 failed correctness test!");
            }
        }
    }

    // ==== AES ====

    setState(0, "idle");
    delay(ALGORITHM_DELAY);

    {
        setState(4, "aes128");
        AES128 aes128;
        aes128.setKey(key128, util::size(key128));
        aes128.encryptBlock(enc_buffer, message);

        AES128 aes128d;
        aes128d.setKey(key128, util::size(key128));
        aes128d.decryptBlock(dec_buffer, enc_buffer);

        if constexpr (CHECK_CORRECTNESS) {
            if (!util::equal(util::begin(dec_buffer), util::end(dec_buffer), util::begin(message))) {
                Serial.println("ERROR: AES128 failed correctness test!");
            }
        }
    }

    setState(0, "idle");
    delay(ALGORITHM_DELAY);

    {
        setState(5, "aes192");
        AES192 aes192;
        aes192.setKey(key192, util::size(key192));
        aes192.encryptBlock(enc_buffer, message);

        AES192 aes192d;
        aes192d.setKey(key192, util::size(key192));
        aes192d.decryptBlock(dec_buffer, enc_buffer);

        if constexpr (CHECK_CORRECTNESS) {
            if (!util::equal(util::begin(dec_buffer), util::end(dec_buffer), util::begin(message))) {
                Serial.println("ERROR: AES192 failed correctness test!");
            }
        }
    }

    setState(0, "idle");
    delay(ALGORITHM_DELAY);

    {
        setState(6, "aes256");
        AES256 aes256;
        aes256.setKey(key256, util::size(key256));
        aes256.encryptBlock(enc_buffer, message);

        AES256 aes256d;
        aes256d.setKey(key256, util::size(key256));
        aes256d.decryptBlock(dec_buffer, enc_buffer);

        if constexpr (CHECK_CORRECTNESS) {
            if (!util::equal(util::begin(dec_buffer), util::end(dec_buffer), util::begin(message))) {
                Serial.println("ERROR: AES256 failed correctness test!");
            }
        }
    }

    // ======== AEADs ========

    setState(0, "idle");
    delay(ALGORITHM_DELAY);

    // ==== ChaCha20Poly1305

    {
        setState(7, "chacha20poly1305");
        ChaChaPoly chachapoly;
        chachapoly.setKey(key256, util::size(key256));
        chachapoly.setIV(iv96, util::size(iv96));
        chachapoly.encrypt(enc_buffer, message, util::size(message));
        chachapoly.computeTag(tag_buffer, util::size(tag_buffer));

        ChaChaPoly chachapolyd;
        chachapolyd.setKey(key256, util::size(key256));
        chachapolyd.setIV(iv96, util::size(iv96));
        chachapolyd.decrypt(dec_buffer, enc_buffer, util::size(message));

        if constexpr (CHECK_CORRECTNESS) {
            if (!util::equal(util::begin(dec_buffer), util::end(dec_buffer), util::begin(message))) {
                Serial.println("ERROR: ChaCha20Poly1305 encryption failed correctness test!");
            }

            if (!chachapolyd.checkTag(tag_buffer, util::size(tag_buffer))) {
                Serial.println("ERROR: ChaCha20Poly1305 tag failed correctness test!");
            }
        }
    }

    // ==== AES-GCM ====

    setState(0, "idle");
    delay(ALGORITHM_DELAY);

    {
        setState(8, "aes128-gcm");
        GCM<AES128> gcm;
        gcm.setKey(key128, util::size(key128));
        gcm.setIV(iv128, util::size(iv128));
        gcm.encrypt(enc_buffer, message, util::size(message));
        gcm.computeTag(tag_buffer, util::size(tag_buffer));

        GCM<AES128> gcmd;
        gcmd.setKey(key128, util::size(key128));
        gcmd.setIV(iv128, util::size(iv128));
        gcmd.decrypt(dec_buffer, enc_buffer, util::size(message));

        if constexpr (CHECK_CORRECTNESS) {
            if (!util::equal(util::begin(dec_buffer), util::end(dec_buffer), util::begin(message))) {
                Serial.println("ERROR: AES128-GCM encryption failed correctness test!");
            }

            if (!gcmd.checkTag(tag_buffer, util::size(tag_buffer))) {
                Serial.println("ERROR: AES128-GCM tag failed correctness test!");
            }
        }
    }

    setState(0, "idle");
    delay(ALGORITHM_DELAY);

    {
        setState(9, "aes192-gcm");
        GCM<AES192> gcm;
        gcm.setKey(key192, util::size(key192));
        gcm.setIV(iv128, util::size(iv128));
        gcm.encrypt(enc_buffer, message, util::size(message));
        gcm.computeTag(tag_buffer, util::size(tag_buffer));

        GCM<AES192> gcmd;
        gcmd.setKey(key192, util::size(key192));
        gcmd.setIV(iv128, util::size(iv128));
        gcmd.decrypt(dec_buffer, enc_buffer, util::size(message));

        if constexpr (CHECK_CORRECTNESS) {
            if (!util::equal(util::begin(dec_buffer), util::end(dec_buffer), util::begin(message))) {
                Serial.println("ERROR: AES192-GCM encryption failed correctness test!");
            }

            if (!gcmd.checkTag(tag_buffer, util::size(tag_buffer))) {
                Serial.println("ERROR: AES192-GCM tag failed correctness test!");
            }
        }
    }

    setState(0, "idle");
    delay(ALGORITHM_DELAY);

    {
        setState(10, "aes256-gcm");
        GCM<AES128> gcm;
        gcm.setKey(key256, util::size(key256));
        gcm.setIV(iv128, util::size(iv128));
        gcm.encrypt(enc_buffer, message, util::size(message));
        gcm.computeTag(tag_buffer, util::size(tag_buffer));

        GCM<AES128> gcmd;
        gcmd.setKey(key256, util::size(key256));
        gcmd.setIV(iv128, util::size(iv128));
        gcmd.decrypt(dec_buffer, enc_buffer, util::size(message));

        if constexpr (CHECK_CORRECTNESS) {
            if (!util::equal(util::begin(dec_buffer), util::end(dec_buffer), util::begin(message))) {
                Serial.println("ERROR: AES256-GCM encryption failed correctness test!");
            }

            if (!gcmd.checkTag(tag_buffer, util::size(tag_buffer))) {
                Serial.println("ERROR: AES256-GCM tag failed correctness test!");
            }
        }
    }

    // ==== Acorn128 ====

    setState(0, "idle");
    delay(ALGORITHM_DELAY);

    {
        setState(11, "acorn128");
        Acorn128 acorn128;
        acorn128.setKey(key128, util::size(key128));
        acorn128.setIV(iv128, util::size(iv128));
        acorn128.encrypt(enc_buffer, message, util::size(message));
        acorn128.computeTag(tag_buffer, util::size(tag_buffer));

        Acorn128 acorn128d;
        acorn128d.setKey(key128, util::size(key128));
        acorn128d.setIV(iv128, util::size(iv128));
        acorn128d.decrypt(dec_buffer, enc_buffer, util::size(message));

        if constexpr (CHECK_CORRECTNESS) {
            if (!util::equal(util::begin(dec_buffer), util::end(dec_buffer), util::begin(message))) {
                Serial.println("ERROR: Acorn128 encryption failed correctness test!");
            }

            if (!acorn128d.checkTag(tag_buffer, util::size(tag_buffer))) {
                Serial.println("ERROR: Acorn128 tag failed correctness test!");
            }
        }
    }

    // ==== Ascon128 ====

    setState(0, "idle");
    delay(ALGORITHM_DELAY);

    {
        setState(12, "ascon128");
        Ascon128 ascon128;
        ascon128.setKey(key128, util::size(key128));
        ascon128.setIV(iv128, util::size(iv128));
        ascon128.encrypt(enc_buffer, message, util::size(message));
        ascon128.computeTag(tag_buffer, util::size(tag_buffer));

        Ascon128 ascon128d;
        ascon128d.setKey(key128, util::size(key128));
        ascon128d.setIV(iv128, util::size(iv128));
        ascon128d.decrypt(dec_buffer, enc_buffer, util::size(message));

        if constexpr (CHECK_CORRECTNESS) {
            if (!util::equal(util::begin(dec_buffer), util::end(dec_buffer), util::begin(message))) {
                Serial.println("ERROR: Ascon128 encryption failed correctness test!");
            }

            if (!ascon128d.checkTag(tag_buffer, util::size(tag_buffer))) {
                Serial.println("ERROR: Ascon128 tag failed correctness test!");
            }
        }
    }

    setState(0, "idle");
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
}
