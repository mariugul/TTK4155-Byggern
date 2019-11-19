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
#include "../inc/adc.h"

// Defines
//---------------------------------------------------
#define OLED_BASE 0x1000
#define ADC_BASE 0x1400
#define SRAM_BASE 0x1800

#define OLED_ADDR_SIZE 0x400
#define ADC_ADDR_SIZE 0x400
#define SRAM_ADDR_SIZE 0x800

// Function Definitions
//---------------------------------------------------
void adc_test(void)
{
    volatile char* ext_ram = (char*)ADC_BASE; // Start address for the SRAM
    uint16_t ext_ram_size = ADC_ADDR_SIZE;

    for (uint16_t i = 0; i < ext_ram_size; i++) {
        uint8_t retreived_value = ext_ram[i];
    }
    printf("Written to all ADC addresses - DONE\n");
}

void adc_init()
{
    //volatile char* ext_ram = (char*)ADC_BASE; // Start address for the SRAM
    // init code
    // calibrate
}

int adc_read(uint8_t channel)
{
    // Channel address for channel 1, 2, 3, 4
    const uint8_t mux_address[4] = { 0x04, 0x05, 0x06, 0x07 };
    volatile char* ext_ram = (char*)ADC_BASE; // Start address for the SRAM

    // Write to channel address mux
    ext_ram[0] = mux_address[channel]; // Channel start from 1
    for (volatile uint32_t i = 0; i < 1000; i++)
        ; // wait for conversion

    return ext_ram[0]; // return read value
}

pos_t pos_read()
{
    return (pos_t) {
        .joy_x = Pos_to_percent(ADC_Read(JOY_X)), // change with read function
        .joy_y = Pos_to_percent(ADC_Read(JOY_Y)),
        .slider_l = Pos_to_percent(ADC_Read(SLIDER_L)), // change with read function
        .slider_r = Pos_to_percent(ADC_Read(SLIDER_R)),
        .button = Gpio_Read_Button(3)
    };
}
