#include <avr/interrupt.h>

#define PIND4MASK 0b00010000
#define PIND5MASK 0b00100000
#define PIND6MASK 0b01000000
#define PIND7MASK 0b10000000

volatile int ch1, ch2, ch3, ch4 = 0;
volatile unsigned long ch1timer, ch2timer, ch3timer, ch4timer;
volatile byte lastPINDValue = 0;

void setup() {
    cli();
    // When the PCIE2 bit is set (one) and the I-bit in the Status Register (SREG) is set (one), pin change interrupt 2 is
    // enabled. Any change on any enabled PCINT[23:16] pin will cause an interrupt. The corresponding interrupt of
    // Pin Change Interrupt Request is executed from the PCI2 Interrupt Vector. PCINT[23:16] pins are enabled
    // individually by the PCMSK2 Register.
    PCICR |= (1<<PCIE2);
    PCMSK2 = 0b11110000;
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

ISR(PCINT2_vect) {
    unsigned long timer = micros();
    
    if ((PIND ^ lastPINDValue) & PIND4MASK) { // PinX changed
        if (PIND & PIND4MASK) { // PinX is now 1, reset counter
            ch1timer = timer;
        } else { // PinX is now 0, calculate PWM
            ch1 = timer - ch1timer;
        }
    }
    if ((PIND ^ lastPINDValue) & PIND5MASK) { 
        if (PIND & PIND5MASK) {
            ch2timer = timer;
        } else {
            ch2 = timer - ch2timer;
        }
    }
    if ((PIND ^ lastPINDValue) & PIND6MASK) {
        if (PIND & PIND6MASK) {
            ch3timer = timer;
        } else {
            ch3 = timer - ch3timer;
        }
    }
    if ((PIND ^ lastPINDValue) & PIND7MASK) {
        if (PIND & PIND7MASK) {
            ch4timer = timer;
        } else {
            ch4 = timer - ch4timer;
        }
    }
    lastPINDValue = PIND;
}