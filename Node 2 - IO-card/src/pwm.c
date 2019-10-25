#include "../inc/pwm.h"
#include "../inc/gpio_defines.h"

// Enable PWM
pwm_init()
{
    // Set mode 15, Fast PWM 0CRnA (Table 17-2)
    SET_PIN(TCCR1A, WGM13);
    SET_PIN(TCCR1A, WGM12);
    SET_PIN(TCCR1B, WGM11);
    SET_PIN(TCCR1B, WGM10);

    // Set compare Match (Table 16-2)
    SET_PIN(TCCR1A, COM1A0);
    CLEAR_PIN(TCCR1A, COM1A0);
}
