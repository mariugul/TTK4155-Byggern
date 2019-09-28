/*
 * joystick.c
 *
 * Created: 17.09.2019 10:48:38
 *  Author: Marius
 */ 

#include "adc.h"

#define OLED_BASE	   0x1000
#define ADC_BASE	   0x1400
#define SRAM_BASE	   0x1800

#define OLED_ADDR_SIZE 0x400
#define ADC_ADDR_SIZE  0x400
#define SRAM_ADDR_SIZE 0x800



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
	return (pos_t){
		.joy_x    = pos_to_percent( adc_read(JOY_X)    ),				// change with read function
		.joy_y    = pos_to_percent( adc_read(JOY_Y)    ),
		.slider_l = pos_to_percent( adc_read(SLIDER_L) ),			    // change with read function
		.slider_r = pos_to_percent( adc_read(SLIDER_R) ),
		.button   = 69
	};
}

int pos_to_percent(int pos)
{
	return  (float)pos / 128 * 100 - 100;
}

enum direction j_pos(int joy_x, int joy_y)
{
	static int threshold = 10;			// the tolerable difference from 0
	static int angle     = 50;			// the sideways angle
	
	// left
	if(joy_x < -threshold && joy_y > joy_x && joy_y < -joy_x)
		return LEFT;
	
	// right
	else if(joy_x > threshold && joy_y < joy_x && joy_y > -joy_x)
		return RIGHT;
		
	// down
	else if(joy_y < -threshold && joy_x < -joy_y && joy_x > joy_y )
	return DOWN;
	
	// up
	else if(joy_y > threshold && joy_x < joy_y && joy_x > -joy_y)
		return UP;
	
	// neutral
	else if(joy_x < threshold && joy_x > -threshold && joy_y < threshold && joy_y > -threshold )
		return NEUTRAL;
}

// Differential mode:
// Channel  MA4 MA3 MA2 MA0
// CH1:     0   1   0   0
// CH2:     0   1   0   1
// CH3:     0   1   1   0
// CH4:     0   1   1   1
