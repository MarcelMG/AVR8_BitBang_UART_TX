/**
  @brief Software ("bit-bang") UART Transmitter (8 data bits, 1 stop bit, no parity)
    for Attiny24A/44A/84A using the internal 8MHz oscillator as clock source
    (c) 2018
    @author Marcel Meyer-Garcia
    see LICENCE.txt 
    
    which can be found in
    https://github.com/MarcelMG/AVR8_BitBang_UART_TX 
    which says MIT Licensed,
    
    adapted for USBASP/atmega8 by
    (c) 2022
    @author Jussi Rasku 
    and added this header and documentation while at it.
 **/ 

#include "bitbang_uart_tx.h"

volatile uint16_t tx_shift_reg = 0;

void BBUART_init(){
   //set TX pin as output
   BBUART_TX_DDR |= (1<<BBUART_TX_DDR_PIN);
   BBUART_TX_PORT |= (1<<BBUART_TX_PIN);
   // Use I/O clock
   ASSR = 0;
   //set prescaler to 8 and set timer to CTC mode
   TCCR2 = (1<<CS21)|(1<<WGM21);
   //enable output compare interrupt
   TIMSK |= (1<<OCIE2);
   //set compare value to 155 to achieve a 9600 baud rate (i.e. 104µs)
   //together with the 12MHz/8=1MHz timer0 clock
   /*NOTE: since this is not very accurate, this value can be tuned
     to achieve the desired baud rate, so if it doesn't work with the nominal value (103), try
     increasing or decreasing the value by 1 or 2 */
   OCR2 = 155;
   //enable interrupts
   sei();
}

// Interrupt handler for timer2 (on Atmega8) compare
ISR(TIMER2_COMP_vect)
{
   uint16_t local_tx_shift_reg = tx_shift_reg;
   //output LSB of the TX shift register at the TX pin
   if( local_tx_shift_reg & 0x01 )
   {
      BBUART_TX_PORT |= (1<<BBUART_TX_PIN);
   }
   else
   {
      BBUART_TX_PORT &=~ (1<<BBUART_TX_PIN);
   }
   //shift the TX shift register one bit to the right
   local_tx_shift_reg >>= 1;
   tx_shift_reg = local_tx_shift_reg;
   //if the stop bit has been sent, the shift register will be 0
   //and the transmission is completed, so we can stop & reset timer
   if(!local_tx_shift_reg)
   {
      TCCR2 = 0;
      TCNT2 = 0;
   }
}

uint8_t BBUART_tx(char character)
{
   uint16_t local_tx_shift_reg = tx_shift_reg;
   //if sending the previous character is not yet finished, return
   // (transmission is finished when tx_shift_reg == 0)
   if(local_tx_shift_reg){return 0;}
   //fill the TX shift register witch the character to be sent
   // and the start & stop bits (start bit (1<<0) is already 0)
   local_tx_shift_reg = (character<<1) | (1<<9); //stop bit (1<<9)
   tx_shift_reg = local_tx_shift_reg;
   //start the timer with a prescaler of 8
   TCCR2 = (1<<CS21)|(1<<WGM21);
   return 1;
}

 void BBUART_tx_str(char* string){
   while( *string ){
      //wait until previous transmission is finished
      while(tx_shift_reg);
      BBUART_tx( *string++ );
    }
    while(tx_shift_reg);
}
 
