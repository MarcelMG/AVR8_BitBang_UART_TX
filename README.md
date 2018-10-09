Software ("bit-bang") UART Transmitter (  8 data bits, 1 stop bit, no parity ) for Attiny24A
this can easily be ported to other AVR8 µC's or might even work without changes on many of them

the Baud rate is calculated as follows:
BAUD = F_CPU / ( TIMER0_PRESCALER * (OCR0A + 1)
so we can modify the prescaler and/or the OCR0A value to achieve a certain baud rate.

In this example I am using the internal 8MHz oscillator as clock source, so F_CPU=8000000
and a baud rate of 9600.

The program can be compiled with avr-gcc and the avr-libc libraries.