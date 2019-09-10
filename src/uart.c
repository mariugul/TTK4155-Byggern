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
	fdevopen(uart_printf, uart_receive);													
}
     
// send data
void uart_send(unsigned char data)               
{
    //wait for empty transmit buffer
	while(!uart_is_ready());
	
	//put data on buffer	 
	UDR0 = data;
}

// receive data
unsigned char uart_receive()            
{
	// return received data
	return UDR0;
}

// check if transmitt buffer is ready
bool uart_is_ready()                     
{
	// return true if transmitt buffer is not busy
    return((UCSR0A & (1<<UDRE0)));
}

// check for data in the HW buffer
bool uart_has_data()						
{
	// return true if data in buffer
	return (UCSR0A & (1<<RXC0));
}

// stream handler for printf
int uart_printf(char c, FILE *stream)			 
{
	uart_send(c);
	return 0;
}



