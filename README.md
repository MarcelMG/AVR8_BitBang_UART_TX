Fork of Software ("bit-bang") UART Transmitter (  8 data bits, 1 stop bit, no parity ) for Attiny24A.

This fork is indended for Atmega8a as it is found on USBASP programmer (12 MHz clock).
The modifications are related to timing and use of timer2 instead of timer0.
In addition the code in this fork is reorganized to be #included from separate file and some documentation added.

the Baud rate is calculated as follows:
BAUD = F_CPU / ( TIMER_PRESCALER * (OCR + 1)
so we can modify the prescaler to achieve a certain baud rate.

In this fork we use external 12MHz oscillator as clock source, so F_CPU=12000000
and a baud rate of 9600.

The program can be compiled with avr-gcc and the avr-libc libraries.


