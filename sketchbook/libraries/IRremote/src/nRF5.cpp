#if defined(NRF5)  || defined(ARDUINO_ARCH_NRF52840)

// This file contains functions specific to the nRF5.
// It uses Timer2 so you cannot use the Adafruit_Microbit display driver

#include "IRremote.h"

// "Idiot check"
#ifdef USE_DEFAULT_ENABLE_IR_IN
#error Must undef USE_DEFAULT_ENABLE_IR_IN
#endif

void IRTimer(); // defined in IRremote.cpp, masqueraded as ISR(TIMER_INTR_NAME)

//+=============================================================================
// initialization
//
void IRrecv::enableIRIn() {
// Interrupt Service Routine - Fires every 50uS
    NRF_TIMER2->MODE = TIMER_MODE_MODE_Timer;              // Set the timer in Timer Mode
    NRF_TIMER2->TASKS_CLEAR = 1;                           // clear the task first to be usable for later
    NRF_TIMER2->PRESCALER = 4;                             // f TIMER = 16 MHz / (2 ^ PRESCALER ) : 4 -> 1 MHz, 1 uS
    NRF_TIMER2->BITMODE = TIMER_BITMODE_BITMODE_16Bit;     //Set counter to 16 bit resolution
    NRF_TIMER2->CC[0] = 50;                                //Set value for TIMER2 compare register 0, to trigger every 50 uS
    NRF_TIMER2->CC[1] = 0;                                 //Set value for TIMER2 compare register 1

    // Enable interrupt on Timer 2, for CC[0] compare match events
    NRF_TIMER2->INTENSET = (TIMER_INTENSET_COMPARE0_Enabled << TIMER_INTENSET_COMPARE0_Pos);
    NVIC_EnableIRQ (TIMER2_IRQn);

    NRF_TIMER2->TASKS_START = 1;               // Start TIMER2

    // timerAttachInterrupt(timer, &IRTimer, 1);

    // Initialize state machine variables
    irparams.rcvstate = IR_REC_STATE_IDLE;
    irparams.rawlen = 0;

    // Set pin modes
    pinMode(irparams.recvpin, INPUT);
}

void timer_pal(void) {
    if ((NRF_TIMER2->EVENTS_COMPARE[0] != 0) && ((NRF_TIMER2->INTENSET & TIMER_INTENSET_COMPARE0_Msk) != 0)) {
        NRF_TIMER2->EVENTS_COMPARE[0] = 0;          //Clear compare register 0 event
        IRTimer();                                  // call the IR-receive function
        NRF_TIMER2->CC[0] += 50;
    }
}

/** TIMTER2 peripheral interrupt handler. This interrupt handler is called whenever there it a TIMER2 interrupt
 * Don't mess with this line. really.
 */
extern "C" {
void TIMER2_IRQHandler(void) {
    timer_pal();
}
}

#endif // NRF5
