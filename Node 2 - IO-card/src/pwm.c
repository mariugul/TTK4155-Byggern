#include "../inc/pwm.h"
#include "../inc/gpio_defines.h"

// Enable PWM
void pwm_init()
{
    // Set mode 14, Fast PWM 0CRnA (From table 17-2)
    SET_PIN(TCCR1B, WGM13);
    SET_PIN(TCCR1B, WGM12);
    SET_PIN(TCCR1A, WGM11);
    CLEAR_PIN(TCCR1A, WGM10);

    // Clear OC0A on compare match, non-inverting mode (From table 16-3)
    SET_PIN(TCCR1A, COM1A0);
    CLEAR_PIN(TCCR1A, COM1A1);

    // Set pin B7 to output
    SET_PORT(DDRB, OUTPUT, PORTB, PB5, LOW);
}

/* 
ICR = period
OCRA DUTY 
*/
