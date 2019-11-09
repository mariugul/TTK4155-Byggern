#include "../inc/adc.h"
#include "../inc/gpio_defines.h"

#define BALL_SENSITIVITY 100

void adc_init()
{
    // Select Vref=AVcc
    ADMUX |= (1 << REFS0);
    //set prescaller to 128 and enable ADC
    //ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);

    // Enable ADC
    ADCSRA |= (1 << ADEN);
}

// Returns the ADC value
uint16_t adc_read_raw()
{
    //ADMUX = (ADMUX & 0xF0) | (1 & 0x0F);
    //single conversion mode
    ADCSRA |= (1 << ADSC);
    // wait until ADC conversion is complete
    while (ADCSRA & (1 << ADSC))
        ;
    return ADC;
}

uint16_t adc_read()
{
    //return (float)adc_read_raw() / 1023 * 5;
    return adc_read_raw();
}

int ball_detected()
{
    return adc_read_raw() < BALL_SENSITIVITY;
}