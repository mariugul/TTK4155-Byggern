/*
 * uart_test.c
 *
 * Created: 06.09.2019 13:49:13
 * Author : Marius C. K. Gulbrandsen
 */

#include <avr/io.h>                     // AVR library for IO
#include <stdio.h>                      // Standard library
#include "uart.h"                       // UART driver
#include "led.h"


int main(void)
{
    // Initialize
    led_init();
    uart_init();

    // Send UART test
    uart_send('a');
    uart_send('b');
    uart_send('c');

    // Test printf function
    printf("Heisann");

    // Main program loop
    while (true) {
        
        // UART echoing
        if (uart_has_data()) {
            unsigned char rx_char = uart_receive();
            uart_send(rx_char);     
        }
    }
}
