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

    usart_send('A');
    usart_send('\n');
    printf("Hej!\n");
    // Loop
    while (true) {
    }
}