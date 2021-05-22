This project is a simple implementation of a RC 4 channels receiver using Arduino Nano - atmega328p

It uses the PCINT interrupt to check if a pin hans changed is level

The 4 channels must be connected to pins D4->D7 (PD4 -> PD7), which are on PORTD

From ATMega328 datasheet - page 97:
PD7 
    AIN1 (Analog Comparator Negative Input)
    PCINT23 (Pin Change Interrupt 23)
PD6
    AIN0 (Analog Comparator Positive Input)
    OC0A (Timer/Counter0 Output Compare Match A Output)
    PCINT22 (Pin Change Interrupt 22)
PD5
    T1 (Timer/Counter 1 External Counter Input)
    OC0B (Timer/Counter0 Output Compare Match B Output)
    PCINT21 (Pin Change Interrupt 21)
PD4
    XCK (USART External Clock Input/Output)
    T0 (Timer/Counter 0 External Counter Input)
    PCINT20 (Pin Change Interrupt 20)
PD3
    INT1 (External Interrupt 1 Input)
    OC2B (Timer/Counter2 Output Compare Match B Output)
    PCINT19 (Pin Change Interrupt 19)
PD2 
    INT0 (External Interrupt 0 Input)
    PCINT18 (Pin Change Interrupt 18)
    PD1 TXD (USART Output Pin)
    PCINT17 (Pin Change Interrupt 17)
PD0 
    RXD (USART Input Pin)
    PCINT16 (Pin Change Interrupt 16)

So the corresponding PCINTx interrupts are PCINT[16:23].
The PCICR – Pin Change Interrupt Control Register is used to enable interrupt per PCINT[16:23], corresponding to PORTD. This is done setting bit PCIE2. PCINT[23:16] pins are enabled individually by the PCMSK2 Register.

Remember that:
- PORTD: is the data register, and is used to set values for output pins, or to set the pull-up resistors for input pins. If PORTxn is written logic one when the pin is configured as an output pin, the port pin is driven high (one). If PORTxn is written logic zero when the pin is configured as an output pin, the port pin is driven low (zero). If PORTxn is written logic one when the pin is configured as an input pin, the pull-up resistor is activated.
- DDRD: is the direction data register, used to configure a pin as input(0) / output(1) (default is input). The DDxn bit in the DDRx Register selects the direction of this pin. If DDxn is written logic one, Pxn is configured as an output pin. If DDxn is written logic zero, Pxn is configured as an input pin.
- PIND: is the register used to read pin inputs. Independent of the setting of Data Direction bit DDxn, the port pin can be read through the PINxn Register bit.

The PWM times are calculated using the standard Arduino micros() function, which on the Atmega328 has a resolution if 4 microseconds. So the values are approximated by a step of 4

