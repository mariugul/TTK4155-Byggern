/*
 * testProgramAtmega162.c
 *
 * Created: 06.09.2019 13:49:13
 * Author : Marius C. K. Gulbrandsen
 */ 

#include <avr/io.h>
#include <stdio.h>
#include "uart.h"										// include uart driver

// UART macros
#define FOSC		4915200								// clock speed
#define BAUDRATE	9600								// baud rate for uart
#define MYUBRR		FOSC/16/BAUDRATE-1					// calculate the uart init

// TYPEDEFs
typedef unsigned char uchar;							// unsigned char typedef

int main(void)
{
    // setup pins
	DDRB  |= (1<<PB0);									// port b0 is an output
	PORTB |= (1<<PB0);									// port b0 is HIGH - turn on LED 
	
	// initialize UART
	uart_init(MYUBRR);
	
	// send UART test
	uart_send('a');
	uart_send('b');
	uart_send('c');

    // test printf function
    printf("Heisann");
	
	// main program
    while (true) 
    {	
		// poll for received data
		if(uart_hasData())								
		{
			// hold received data
			static uchar recv_char;			
			recv_char = uart_receive();	
			
			// echo back to terminal for verification		
			uart_send(recv_char);
		}
		
		
	}		
}




