/*
 * IRsendDemo.cpp
 *
 * Demonstrates sending IR codes in standard format with address and command
 *
 * An IR LED must be connected to Arduino PWM pin 3 (IR_SEND_PIN).
 *
 *
 *  Copyright (C) 2020-2021  Armin Joachimsmeyer
 *  armin.joachimsmeyer@gmail.com
 *
 *  This file is part of Arduino-IRremote https://github.com/z3t0/Arduino-IRremote.
 */

//#define EXCLUDE_EXOTIC_PROTOCOLS // saves around 240 bytes program space if IrSender.write is used
#include <IRremote.h>
#if defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__) || defined(__AVR_ATtiny87__) || defined(__AVR_ATtiny167__)
#include "ATtinySerialOut.h"
#endif

// On the Zero and others we switch explicitly to SerialUSB
#if defined(ARDUINO_ARCH_SAMD)
#define Serial SerialUSB
#endif

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(115200);
#if defined(__AVR_ATmega32U4__) || defined(SERIAL_USB) || defined(SERIAL_PORT_USBVIRTUAL)  || defined(ARDUINO_attiny3217)
    delay(4000); // To be able to connect Serial monitor after reset or power up and before first printout
#endif
    // Just to know which program is running on my Arduino
    Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));
    Serial.print(F("Ready to send IR signals at pin "));
    Serial.println(IR_SEND_PIN);

#if defined(USE_SOFT_SEND_PWM) || defined(USE_NO_SEND_PWM)
    IrSender.begin(IR_SEND_PIN, true); // Specify send pin and enable feedback LED at default feedback LED pin
#else
    IrSender.begin(true); // Enable feedback LED at default feedback LED pin
#endif
}

/*
 * Set up the data to be sent.
 * For most protocols, the data is build up with a constant 8 (or 16 byte) address
 * and a variable 8 bit command.
 * There are exceptions like Sony and Denon, which have 5 bit address.
 */
uint16_t sAddress = 0x0102;
uint8_t sCommand = 0x34;
uint8_t sRepeats = 0;

void loop() {
    /*
     * Print values
     */
    Serial.println();
    Serial.print(F("address=0x"));
    Serial.print(sAddress, HEX);
    Serial.print(F(" command=0x"));
    Serial.print(sCommand, HEX);
    Serial.print(F(" repeats="));
    Serial.print(sRepeats);
    Serial.println();
    Serial.flush();

    Serial.println(F("Send NEC with 8 bit address"));
    IrSender.sendNEC(sAddress & 0xFF, sCommand, sRepeats);
    delay(2000); // delay must be greater than 5 ms (RECORD_GAP_MICROS), otherwise the receiver sees it as one long signal

    Serial.println(F("Send NEC with 16 bit address"));
    IrSender.sendNEC(sAddress, sCommand, sRepeats);
    delay(2000);

    if (sRepeats == 0) {
#if !defined(__AVR_ATtiny85__)
        /*
         * Send constant values only once in this demo
         */
        Serial.println(F("Sending NEC Pronto data with 8 bit address 0x80 and command 0x45 and no repeats"));
        IrSender.sendPronto(F("0000 006D 0022 0000 015E 00AB " /* Pronto header + start bit */
                "0017 0015 0017 0015 0017 0017 0015 0017 0017 0015 0017 0015 0017 0015 0017 003F " /* Lower address byte */
                "0017 003F 0017 003E 0017 003F 0015 003F 0017 003E 0017 003F 0017 003E 0017 0015 " /* Upper address byte (inverted at 8 bit mode) */
                "0017 003E 0017 0015 0017 003F 0017 0015 0017 0015 0017 0015 0017 003F 0017 0015 " /* command byte */
                "0019 0013 0019 003C 0017 0015 0017 003F 0017 003E 0017 003F 0017 0015 0017 003E " /* inverted command byte */
                "0017 0806"), 0); //stop bit, no repeat possible, because of missing repeat pattern
        delay(2000);
#endif
        /*
         * With sendNECRaw() you can send even "forbidden" codes with parity errors
         */
        Serial.println(
                F(
                        "Send NEC with 16 bit address 0x0102 and command 0x34 with NECRaw(0xCC340102) which results in a parity error, since 34 == ~CB and not C0"));
        IrSender.sendNECRaw(0xC0340102, sRepeats);
        delay(2000);

        /*
         * With Send sendNECMSB() you can send your old 32 bit codes.
         * To convert one into the other, you must reverse the byte positions and then reverse all positions of each byte.
         * Example:
         * 0xCB340102 byte reverse -> 0x020134CB bit reverse-> 40802CD3
         */
        Serial.println(F("Send NEC with 16 bit address 0x0102 and command 0x34 with old 32 bit format MSB first"));
        IrSender.sendNECMSB(0x40802CD3, 32, false);
        delay(2000);
    }

    Serial.println(F("Send Apple"));
    IrSender.sendApple(sAddress, sCommand, sRepeats);
    delay(2000);

    Serial.println(F("Send Panasonic"));
    IrSender.sendPanasonic(sAddress, sCommand, sRepeats);
    delay(2000);

    Serial.println(F("Send Kaseikyo with 0x4711 as Vendor ID"));
    IrSender.sendKaseikyo(sAddress, sCommand, sRepeats, 0x4711);
    delay(2000);

    Serial.println(F("Send Denon"));
    IrSender.sendDenon(sAddress, sCommand, sRepeats);
    delay(2000);

    Serial.println(F("Send Denon/Sharp variant"));
    IrSender.sendSharp(sAddress, sCommand, sRepeats);
    delay(2000);

    Serial.println(F("Send Sony/SIRCS with 7 command and 5 address bits"));
    IrSender.sendSony(sAddress, sCommand, sRepeats);
    delay(2000);

    Serial.println(F("Send Sony/SIRCS with 7 command and 8 address bits"));
    IrSender.sendSony(sAddress, sCommand, sRepeats, SIRCS_15_PROTOCOL);
    delay(2000);

    Serial.println(F("Send Sony/SIRCS with 7 command and 13 address bits"));
    IrSender.sendSony(sAddress, sCommand, sRepeats, SIRCS_20_PROTOCOL);
    delay(2000);

    Serial.println(F("Send RC5"));
    IrSender.sendRC5(sAddress, sCommand, sRepeats, true);
    delay(2000);

    Serial.println(F("Send RC5X with command + 0x40"));
    IrSender.sendRC5(sAddress, sCommand + 0x40, sRepeats, true);
    delay(2000);

    Serial.println(F("Send RC6"));
    IrSender.sendRC6(sAddress, sCommand, sRepeats, true);
    delay(2000);

#if !defined(__AVR_ATtiny85__) // code does not fit in program space of ATtiny85
    /*
     * Next example how to use the IrSender.write function
     */
    IRData IRSendData;
    // prepare data
    IRSendData.address = sAddress;
    IRSendData.command = sCommand;
    IRSendData.flags = IRDATA_FLAGS_EMPTY;

    IRSendData.protocol = SAMSUNG;
    Serial.print(F("Send "));
    Serial.println(getProtocolString(IRSendData.protocol));
    IrSender.write(&IRSendData, sRepeats);
    delay(2000);

    IRSendData.protocol = JVC; // switch protocol
    Serial.print(F("Send "));
    Serial.println(getProtocolString(IRSendData.protocol));
    IrSender.write(&IRSendData, sRepeats);
    delay(2000);

    IRSendData.protocol = LG;
    Serial.print(F("Send "));
    Serial.println(getProtocolString(IRSendData.protocol));
    IrSender.write(&IRSendData, sRepeats);
    delay(2000);

    if (sRepeats == 0) {
        /*
         * Send constant values only once in this demo
         * This value is the valid LG turn off command which violates the parity rule
         * All other commands obey this rule.
         * see: https://github.com/Arduino-IRremote/Arduino-IRremote/tree/master/examples/LGACSendDemo
         */
        Serial.println(F("Send LGRaw 0x88C0051 with \"parity error\" since C+0+0+5 != 1"));
        IrSender.sendLGRaw(0x88C0051, sRepeats);
        delay(2000);
    }

    IRSendData.protocol = BOSEWAVE;
    Serial.println(F("Send Bosewave with no address and 8 command bits"));
    IrSender.write(&IRSendData, sRepeats);
    delay(2000);

    /*
     * LEGO is difficult to receive because of its short marks and spaces
     */
    Serial.println(F("Send Lego with 2 channel and with 4 command bits"));
    IrSender.sendLegoPowerFunctions(sAddress, sCommand, LEGO_MODE_COMBO, true);
    delay(2000);

    /*
     * Force buffer overflow
     */
    Serial.println(F("Force buffer overflow by sending 100 marks and spaces"));
    for (unsigned int i = 0; i < RAW_BUFFER_LENGTH; ++i) {
        IrSender.mark(400);
        IrSender.space(400);
    }
    delay(2000);

    /*
     * Increment values
     * Also increment address just for demonstration, which normally makes no sense
     */
    sAddress += 0x0101;
    sCommand += 0x11;
    sRepeats++;
    // clip repeats at 4
    if (sRepeats > 4) {
        sRepeats = 4;
    }
#endif // !defined(__AVR_ATtiny85__)

    delay(4000); // additional delay at the end of each loop
}
