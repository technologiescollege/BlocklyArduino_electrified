//******************************************************************************
// IRremote.cpp.h
//
//  Contains all IRreceiver static functions
//
//
// Initially coded 2009 Ken Shirriff http://www.righto.com
//
// Modified by Paul Stoffregen <paul@pjrc.com> to support other boards and timers
//
// Interrupt code based on NECIRrcv by Joe Knapp
// http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1210243556
// Also influenced by http://zovirl.com/2008/11/12/building-a-universal-remote-with-an-arduino/
//******************************************************************************
/************************************************************************************
 * MIT License
 *
 * Copyright (c) 2009-2021 Ken Shirriff, Rafi Khan, Armin Joachimsmeyer
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 ************************************************************************************
 */
#include "IRremoteInt.h"

struct irparams_struct irparams; // the irparams instance

//+=============================================================================
// The match functions were (apparently) originally MACROs to improve code speed
//   (although this would have bloated the code) hence the names being CAPS
// A later release implemented debug output and so they needed to be converted
//   to functions.
// I tried to implement a dual-compile mode (DEBUG/non-DEBUG) but for some
//   reason, no matter what I did I could not get them to function as macros again.
// I have found a *lot* of bugs in the Arduino compiler over the last few weeks,
//   and I am currently assuming that one of these bugs is my problem.
// I may revisit this code at a later date and look at the assembler produced
//   in a hope of finding out what is going on, but for now they will remain as
//   functions even in non-DEBUG mode
//
bool MATCH(uint16_t measured, uint16_t desired) {
#ifdef TRACE
    Serial.print(F("Testing: "));
    Serial.print(TICKS_LOW(desired), DEC);
    Serial.print(F(" <= "));
    Serial.print(measured, DEC);
    Serial.print(F(" <= "));
    Serial.print(TICKS_HIGH(desired), DEC);
#endif
    bool passed = ((measured >= TICKS_LOW(desired)) && (measured <= TICKS_HIGH(desired)));
#ifdef TRACE
    if (passed) {
        Serial.println(F("?; passed"));
    } else {
        Serial.println(F("?; FAILED"));
    }
#endif
    return passed;
}

// used for ir_Pronto
int getMarkExcessMicros() {
    return MARK_EXCESS_MICROS;
}

//+========================================================
// Due to sensor lag, when received, Marks tend to be MARK_EXCESS_MICROS us too long
//
bool MATCH_MARK(uint16_t measured_ticks, uint16_t desired_us) {
#ifdef TRACE
    Serial.print(F("Testing mark (actual vs desired): "));
    Serial.print(measured_ticks * MICROS_PER_TICK, DEC);
    Serial.print(F("us vs "));
    Serial.print(desired_us, DEC);
    Serial.print(F("us: "));
    Serial.print(TICKS_LOW(desired_us + MARK_EXCESS_MICROS) * MICROS_PER_TICK, DEC);
    Serial.print(F(" <= "));
    Serial.print(measured_ticks * MICROS_PER_TICK, DEC);
    Serial.print(F(" <= "));
    Serial.print(TICKS_HIGH(desired_us + MARK_EXCESS_MICROS) * MICROS_PER_TICK, DEC);
#endif
    // compensate for marks exceeded by demodulator hardware
    bool passed = ((measured_ticks >= TICKS_LOW(desired_us + MARK_EXCESS_MICROS))
            && (measured_ticks <= TICKS_HIGH(desired_us + MARK_EXCESS_MICROS)));
#ifdef TRACE
    if (passed) {
        Serial.println(F("?; passed"));
    } else {
        Serial.println(F("?; FAILED"));
    }
#endif
    return passed;
}

//+========================================================
// Due to sensor lag, when received, Spaces tend to be MARK_EXCESS_MICROS us too short
//
bool MATCH_SPACE(uint16_t measured_ticks, uint16_t desired_us) {
#ifdef TRACE
    Serial.print(F("Testing space (actual vs desired): "));
    Serial.print(measured_ticks * MICROS_PER_TICK, DEC);
    Serial.print(F("us vs "));
    Serial.print(desired_us, DEC);
    Serial.print(F("us: "));
    Serial.print(TICKS_LOW(desired_us - MARK_EXCESS_MICROS) * MICROS_PER_TICK, DEC);
    Serial.print(F(" <= "));
    Serial.print(measured_ticks * MICROS_PER_TICK, DEC);
    Serial.print(F(" <= "));
    Serial.print(TICKS_HIGH(desired_us - MARK_EXCESS_MICROS) * MICROS_PER_TICK, DEC);
#endif
    // compensate for marks exceeded and spaces shortened by demodulator hardware
    bool passed = ((measured_ticks >= TICKS_LOW(desired_us - MARK_EXCESS_MICROS))
            && (measured_ticks <= TICKS_HIGH(desired_us - MARK_EXCESS_MICROS)));
#ifdef TRACE
    if (passed) {
        Serial.println(F("?; passed"));
    } else {
        Serial.println(F("?; FAILED"));
    }
#endif
    return passed;
}

//+=============================================================================
// Interrupt Service Routine - Fires every 50 us
// Widths of alternating SPACE, MARK are recorded in irparams.rawbuf.
// Recorded in ticks of 50 us [microseconds, 0.000050 seconds]
// 'rawlen' counts the number of entries recorded so far.
// First entry is the SPACE between transmissions.
// As soon as a the first [SPACE] entry gets longer than RECORD_GAP_TICKS:
//   State switches to STOP (frame received); Timing of SPACE continues.
// A resume() switches from STOP to IDLE.
// As soon as first MARK arrives in IDLE:
//   Gap width is recorded; New logging starts.
//
//#define IR_MEASURE_TIMING
//#define IR_TIMING_TEST_PIN 7 // do not forget to execute:  pinMode(7, OUTPUT);
#if defined(IR_MEASURE_TIMING) && defined(IR_TIMING_TEST_PIN)
#include "digitalWriteFast.h"
#endif
ISR (TIMER_INTR_NAME) {
#if defined(IR_MEASURE_TIMING) && defined(IR_TIMING_TEST_PIN)
    digitalWriteFast(IR_TIMING_TEST_PIN, HIGH); // 2 clock cycles
#endif
    // 7 - 8.5 us for ISR body (without pushes and pops) for ATmega328 @16MHz

    TIMER_RESET_INTR_PENDING; // reset timer interrupt flag if required (currently only for Teensy and ATmega4809)

    // Read if IR Receiver -> SPACE [xmt LED off] or a MARK [xmt LED on]
    uint8_t irdata = (uint8_t) digitalRead(irparams.recvpin);

    // clip timer at maximum 0xFFFF / 3.2 seconds at 50 us ticks
    if (irparams.timer < 0xFFFF) {
        irparams.timer++;  // One more 50uS tick
    }

    /*
     * Due to a ESP32 compiler bug https://github.com/espressif/esp-idf/issues/1552 no switch statements are possible for ESP32
     * So we change the code to if / else if
     */
//    switch (irparams.rcvstate) {
    //......................................................................
    if (irparams.rcvstate == IR_REC_STATE_IDLE) { // In the middle of a gap
        if (irdata == MARK) {
            // check if we did not start in the middle of an command by checking the minimum length of leading space
            if (irparams.timer > RECORD_GAP_TICKS) {
                // Gap just ended; Record gap duration + start recording transmission
                // Initialize all state machine variables
#if defined(IR_MEASURE_TIMING) && defined(IR_TIMING_TEST_PIN)
//                digitalWriteFast(IR_TIMING_TEST_PIN, HIGH); // 2 clock cycles
#endif
                irparams.overflow = false;
                irparams.rawbuf[0] = irparams.timer;
                irparams.rawlen = 1;
                irparams.rcvstate = IR_REC_STATE_MARK;
            }
            irparams.timer = 0;
        }

    } else if (irparams.rcvstate == IR_REC_STATE_MARK) {  // Timing Mark
        if (irdata == SPACE) {   // Mark ended; Record time
#if defined(IR_MEASURE_TIMING) && defined(IR_TIMING_TEST_PIN)
//            digitalWriteFast(IR_TIMING_TEST_PIN, HIGH); // 2 clock cycles
#endif
            irparams.rawbuf[irparams.rawlen++] = irparams.timer;
            irparams.rcvstate = IR_REC_STATE_SPACE;
            irparams.timer = 0;
        }

    } else if (irparams.rcvstate == IR_REC_STATE_SPACE) {  // Timing Space
        if (irdata == MARK) {  // Space just ended; Record time
            if (irparams.rawlen >= RAW_BUFFER_LENGTH) {
                // Flag up a read overflow; Stop the State Machine
                irparams.overflow = true;
                irparams.rcvstate = IR_REC_STATE_STOP;
            } else {
#if defined(IR_MEASURE_TIMING) && defined(IR_TIMING_TEST_PIN)
//                digitalWriteFast(IR_TIMING_TEST_PIN, HIGH); // 2 clock cycles
#endif
                irparams.rawbuf[irparams.rawlen++] = irparams.timer;
                irparams.rcvstate = IR_REC_STATE_MARK;
            }
            irparams.timer = 0;

        } else if (irparams.timer > RECORD_GAP_TICKS) {
            /*
             * Current code is ready for processing!
             * We received a long space, which indicates gap between codes.
             * Switch to IR_REC_STATE_STOP
             * Don't reset timer; keep counting width of next leading space
             */
            irparams.rcvstate = IR_REC_STATE_STOP;
        }
    } else if (irparams.rcvstate == IR_REC_STATE_STOP) {
        /*
         * Complete command received
         * stay here until resume() is called, which switches state to IR_REC_STATE_IDLE
         */
#if defined(IR_MEASURE_TIMING) && defined(IR_TIMING_TEST_PIN)
//        digitalWriteFast(IR_TIMING_TEST_PIN, HIGH); // 2 clock cycles
#endif
        if (irdata == MARK) {
            irparams.timer = 0;  // Reset gap timer, to prepare for call of resume()
        }
    }
    setFeedbackLED(irdata == MARK);
#ifdef IR_MEASURE_TIMING
    digitalWriteFast(IR_TIMING_TEST_PIN, LOW); // 2 clock cycles
#endif
}

// If requested, flash LED while receiving IR data
#if defined(ESP32)
IRAM_ATTR
#endif
void setFeedbackLED(bool aSwitchLedOn) {
    if (irparams.blinkflag) {
        if (aSwitchLedOn) {
            if (irparams.blinkpin) {
                digitalWrite(irparams.blinkpin, HIGH); // Turn user defined pin LED on
#ifdef BLINKLED_ON
            } else {
                BLINKLED_ON();   // if no user defined LED pin, turn default LED pin for the hardware on
#endif
            }
        } else {
            if (irparams.blinkpin) {
                digitalWrite(irparams.blinkpin, LOW); // Turn user defined pin LED off
#ifdef BLINKLED_OFF
            } else {
                BLINKLED_OFF();   // if no user defined LED pin, turn default LED pin for the hardware on
#endif
            }
        }
    }
}
