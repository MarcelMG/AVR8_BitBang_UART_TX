/**
  Software ("bit-bang") UART Transmitter (8 data bits, 1 stop bit, no parity)
    for Attiny24A/44A/84A using the internal 8MHz oscillator as clock source
    (c) 2018 Marcel Meyer-Garcia
    see LICENCE.txt 
    
    in
    https://github.com/MarcelMG/AVR8_BitBang_UART_TX 
    which says MIT Licensed,
    
    adapted for USBASP/atmega8 by
    (c) 2022 Jussi Rasku 
    and added this header and documentation while at it.
 **/ 

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#ifndef SOFT_UART_TX_H_   /* Include guard */
#define SOFT_UART_TX_H_

// On USBASP this is the JP1 _or_ PIN5/reset on the header
#define TX_PORT PORTB 
#define TX_PIN  PB2
#define TX_DDR  DDRB
#define TX_DDR_PIN DDB2

volatile uint16_t tx_shift_reg;

/** @brief Called to initialize tiny UART.
 * 
 * Sets the TX pin to output and configures Atmega8 Timer2 to 9600 8n1.
 * The timer setup assumes 12 MHz clock. Finally, interrupts are enabled
 * with AVR sei()-call in the end.
 */
static void init_tiny_uart();

/** @brief Transmits one 8-bit character via UART pin.
 *  @param character to transmit.
 *  @return The number of characters send.
 *           If 0, previous trasmit has not ended and the attempt is aborted.
*/
static uint8_t UART_tx(char character);
/** @brief Transmits the given null-terminated string.
 * 
 *  Note that this is a blocking operation that returns when the entire
 *  string has been transmitted.
 * 
 *  @param string to transmit. 
 */
static void UART_tx_str(char* string);

#endif // SOFT_UART_TX_H_