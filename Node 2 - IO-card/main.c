#include <avr/io.h> // AVR library for IO
#include <stdio.h> // Standard library
#include <stdlib.h>
#include <stdbool.h>
#include "inc/can.h"
#include "inc/usart.h"


int main()
{

    // Initializers
	usart_init();

    // Loop
    while (true) {
        usart_send("Testing USART\n");
    }
}