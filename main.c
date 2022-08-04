/*  Software ("bit-bang") UART Transmitter (8 data bits, 1 stop bit, no parity)
    for Attiny24A/44A/84A using the internal 8MHz oscillator as clock source
    (c) 2018 Marcel Meyer-Garcia
    see LICENCE.txt
 */

#include <util/delay.h>
#include "bitbang_uart_tx.h"


int main(void)
{
   BBUART_init();

   while(1)
   {
    BBUART_tx_str("Hello world!\n");
    _delay_ms(100);
   }

   return 0;
}