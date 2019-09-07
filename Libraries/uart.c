#include "uart.h"                       // include header file
#include <avr/io.h>                    // include avr library


/*_________________________________
  \     Variable declarations     /
   \____________________________*/
/*
typedef struct uart
{
	bool received_data;
}uart;
*/


/*_________________________________
  \     Function definitions      /
   \____________________________*/


// initialize the uart
void uart_init(unsigned int ubrr)  
{
	// set baud rate
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)(ubrr);
	
	// enable receive and transmitt
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	
	// set frame format
	UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);
	
	// setup stream for printf
	FILE uart_stream = FDEV_SETUP_STREAM(uart_printf, NULL, _FDEV_SETUP_WRITE);
	stdout = &uart_stream;														
}
     
// send data
void uart_send(unsigned char data)               
{
    //wait for empty transmit buffer
	while(!uart_isReady());
	
	//put data on buffer	 
	UDR0 = data;
}

// receive data
unsigned char uart_receive()            
{
	/**************************************** /
	/*** This check is now done in main ***** /
	/***   Keeping this for reference   ***** /
	/**************************************** /
	/	// wait for data in buff              / 
	/	//while ( !(UCSR0A & (1<<RXC0)) )	  /	
	/*---------------------------------------*/
	
	// return received data
	return UDR0;
}

// check if transmitt buffer is ready
bool uart_isReady()                     
{
    if(!(UCSR0A & (1<<UDRE0)))
        return true;                    // return true if uart is ready to transmitt
    else 
        return false;                   // if not, return false
}

// check for data in the HW buffer
bool uart_hasData()						
{
	if (UCSR0A & (1<<RXC0))				
		return true;					// return true if data in buffer
	else
		return false;					// if not, return false
}

// stream handler for printf
int uart_printf(char c, FILE *stream)			 
{
	uart_send(c);
	return 0;
}



