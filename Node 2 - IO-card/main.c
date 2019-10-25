/* NODE 2 - ATMEGA 2560 */

#include "inc/can.h"
#include "inc/pwm.h"
#include "inc/usart.h"
#include <avr/io.h> // AVR library for IO
#include <stdbool.h>
#include <stdio.h> // Standard library
#include <stdlib.h>

int main()
{

    // Initializers
    usart_init();
    pwm_init();

    // Loop
    while (true) {
        usart_send("Testing USART\n");
    }
}