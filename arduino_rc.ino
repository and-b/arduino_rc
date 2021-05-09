#include <avr/interrupt.h>

#define PINB0MASK 0b00000001
#define PINB1MASK 0b00000010
#define PINB2MASK 0b00000100
#define PINB3MASK 0b00001000

int ch1, ch2, ch3, ch4 = 0;
unsigned long ch1timer, ch2timer, ch3timer, ch4timer;
byte lastPINBValue = 0;

void setup() {
    cli();
    // When the PCIE0 bit is set (one) and the I-bit in the Status Register (SREG) is set (one), pin change interrupt 0 is
    // enabled. Any change on any enabled PCINT[7:0] pin will cause an interrupt. The corresponding interrupt of Pin
    // Change Interrupt Request is executed from the PCI0 Interrupt Vector. PCINT[7:0] pins are enabled individually
    // by the PCMSK0 Register.
    // PCINT[7:0] -> PB0-5 -> D8-13
    PCICR = 1;
    PCMSK0 = 0b00001111;
    sei();
    Serial.begin(9600);
}

void loop() {
    Serial.print("Ch1:");
    Serial.print(ch1);
    Serial.print(" Ch2:");
    Serial.print(ch2);
    Serial.print(" Ch3:");
    Serial.print(ch3);
    Serial.print(" Ch4:");
    Serial.println(ch4);
    
    delay(250);
}

ISR(PCINT0_vect) {
    unsigned long timer = micros();
    
    if ((PINB ^ lastPINBValue) & PINB0MASK) { // pinB0 changed
        if (PINB & PINB0MASK) { // PinB0 is now 1, reset counter
            ch1timer = timer;
        } else { // PinB0 is now 0, calculate PWM
            ch1 = timer - ch1timer;
        }
    }
    if ((PINB ^ lastPINBValue) & PINB1MASK) { 
        if (PINB & PINB1MASK) {
            ch2timer = timer;
        } else {
            ch2 = timer - ch2timer;
        }
    }
    if ((PINB ^ lastPINBValue) & PINB2MASK) {
        if (PINB & PINB2MASK) {
            ch3timer = timer;
        } else {
            ch3 = timer - ch3timer;
        }
    }
    if ((PINB ^ lastPINBValue) & PINB3MASK) {
        if (PINB & PINB3MASK) {
            ch4timer = timer;
        } else {
            ch4 = timer - ch4timer;
        }
    }
    lastPINBValue = PINB;
}