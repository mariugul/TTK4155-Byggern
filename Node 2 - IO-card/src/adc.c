/*********************************************************
 *             Analog to Digital Converter               *
 *                                                       *
 *  The ADC will read the IR diode values for detecting  *
 *  the ball.                                            *
 *														 *
 * By: Marius C. K. Gulbrandsen and Daniel Rahme         *
 *********************************************************/

// Includes
//---------------------------------------------------
#include "../inc/ADC.h"
#include "../inc/GPIO_Defines.h"
#include "../inc/USART.h"

// Definitions
//---------------------------------------------------
#define BALL_SENSITIVITY 40

// Function Definitions
//---------------------------------------------------

void ADC_Init()
{
    printf("<ADC Initialized>\n");
    // Select Vref=AVcc
    ADMUX |= (1 << REFS0) | (1 << 0); // ADC1
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

int ADC_Ball_Detected()
{
    return ADC_Read_Raw() < BALL_SENSITIVITY;
}