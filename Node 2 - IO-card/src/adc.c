#include "../inc/ADC.h"
#include "../inc/GPIO_Defines.h"

#define BALL_SENSITIVITY 100

void ADC_Init()
{
    // Select Vref=AVcc
    ADMUX |= (1 << REFS0);
    //set prescaller to 128 and enable ADC
    //ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);

    // Enable ADC
    ADCSRA |= (1 << ADEN);
}

// Returns the ADC value
uint16_t ADC_Read_Raw()
{
    //ADMUX = (ADMUX & 0xF0) | (1 & 0x0F);
    //single conversion mode
    ADCSRA |= (1 << ADSC);
    // wait until ADC conversion is complete
    while (ADCSRA & (1 << ADSC))
        ;
    return ADC;
}

uint16_t ADC_Read()
{
    //return (float)ADC_read_raw() / 1023 * 5;
    return ADC_Read_Raw();
}

int Ball_Detected()
{
    return ADC_Read_Raw() < BALL_SENSITIVITY;
}