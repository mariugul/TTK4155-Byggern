/* NODE 2 - ATMEGA 2560 */

#include "inc/can.h"
#include "inc/servo.h"
#include "inc/usart.h"
#include <avr/io.h> 
#include <stdbool.h>
#include <stdio.h> 
#include <stdlib.h>

int main()
{
    // Initializers
    usart_init();
    servo_init();

    // Test UART
    usart_send('T');
    usart_send('\n');
    usart_send('A');

    // Loop
    while (true) {
        // code
    }
}