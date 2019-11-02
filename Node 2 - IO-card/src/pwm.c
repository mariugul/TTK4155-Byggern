#include "../inc/pwm.h"
#include "../inc/gpio_defines.h"
#include "../inc/usart.h"

#define FOSC 16000000 // Clock speed
#define PRESC 256 // Prescaler
#define PERIOD 0.02 // 20ms period for PWM
uint32_t freq = FOSC/PRESC;

// Enable PWM
void pwm_init()
{
    // Set mode 14, Fast PWM 0CRnA (From table 17-2)
    SET_PIN(TCCR1B, WGM13);
    SET_PIN(TCCR1B, WGM12);
    SET_PIN(TCCR1A, WGM11);
    CLEAR_PIN(TCCR1A, WGM10);

    // Clear OC0A on compare match, non-inverting mode (From table 16-3)
    SET_PIN(TCCR1A, COM1A1);
    CLEAR_PIN(TCCR1A, COM1A0);

    // Set pin B5 to output
    SET_PORT(DDRB, OUTPUT, PORTB, PB5, LOW);

    // Set period
    pwm_set_period(PERIOD);
}

// Set the PWM period
void pwm_set_period(float period)
{
    // Set prescaler to 256
    SET_PIN(TCCR1B, CS12);
    CLEAR_PIN(TCCR1B, CS11);
    CLEAR_PIN(TCCR1B, CS10);

    // Set period to 20ms
    int period_calc = freq * period;
    ICR1 = period_calc;

    //***** DEBUG **************
    printf("freq: %d\n", freq);
    printf("period_calc: %d\n", period_calc);
    //**************************
}

// Set the PWM pulse width
void pwm_set_pulse_width(float joystick_pos)
{
    // Variables for calculation
    float const min = 0.0009; // Min pulse width [s]
    float const max = 0.0021; // Max pulse width [s]
    float const diff = max - min; // Differential of the allowed pulse width
    float const diff_median = diff / 2; // The middle value of the differential
    float const median = 255 / 2; // Joystick max value divided by 2

    // Calculations
    float pulse_width = ((joystick_pos / median) * diff_median) + min; // Calculate pulse width [s]
    int OCR = pulse_width * freq;

    // Set the pulse width
    OCR1A = OCR;

    //***** DEBUG **************
    printf("pulse_width: %.2f\n OCR1A: %d\n", pulse_width, OCR);
    //**************************
}


