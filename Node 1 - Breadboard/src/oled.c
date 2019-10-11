/*
 * oled.c
 *
 * Created: 28.09.2019 18:00:16
 *  Author: Marius
 */ 

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "../inc/oled.h"
#include "../inc/fonts.h"
#include "../inc/logo.h"


#define OLED_CMD_ADR      0x1000
#define OLED_DATA_ADR     0x1200
#define OLED_ADDR_SIZE    0x400

#define HORIZONTAL 0x00 
#define PAGE       0x02
									
void oled_init()						// Initialize OLED
{	
	// OLED setup
	oled_write_cmd(0xae);				// display off
	oled_write_cmd(0xa1);				//segment remap
	oled_write_cmd(0xda);				//common pads hardware: alternative
	oled_write_cmd(0x12);
	oled_write_cmd(0xc8);				//common output scan direction:com63~com0
	oled_write_cmd(0xa8);				//multiplex ration mode:63
	oled_write_cmd(0x3f);
	oled_write_cmd(0xd5);				//display divide ratio/osc. freq. mode
	oled_write_cmd(0x80);
	oled_write_cmd(0x81);				//contrast control
	oled_write_cmd(0x50);	
	oled_write_cmd(0xd9);				//set pre-charge period
	oled_write_cmd(0x21);
	
	oled_write_cmd(0x20);				//Set Memory Addressing Mode
	oled_write_cmd(PAGE);			
	
	oled_write_cmd(0xdb);				//VCOM deselect level mode
	oled_write_cmd(0x30);
	oled_write_cmd(0xad);				//master configuration
	oled_write_cmd(0x00);
	oled_write_cmd(0xa4);				//out follows RAM content
	oled_write_cmd(0xa6);				//set normal display
	oled_write_cmd(0xaf);				// display on
	
	oled_reset();		
}


void oled_reset()						// Reset display
{
	const int LINES = 8;
	for (int i = 0; i < LINES; i++)			// Clear screen
		oled_clear_line(i);
		
	oled_home();							// Go to home position
}


void oled_home()						// Go to home screen
{
	oled_goto_line(0);
	//oled_pos(0, 0);						// Go to start position
}


void oled_goto_line(int line)			// Go to specific line
{
	oled_write_cmd(0xB0 + line);		// Go to line
	oled_goto_column(0);				// Set cursor to start of line
	
}


void oled_goto_column(uint8_t column)	// Go to specific column
{	
	int lower = column % 16;
	int upper = column / 16;
		
	oled_write_cmd(lower);
	oled_write_cmd(16 + upper);	
}


void oled_clear_line(int line)			// Clear specific line
{
	oled_pos(line, 0);					// Go to line start position
	
	const int COL = 128;				
	for (int i = 0; i < COL; i++) {		// Clear line
		oled_write_data(0x00);
	}
	oled_goto_line(line);				// Move cursor to start of line
}


void oled_pos(int row, int column)		// Go to position
{
	oled_goto_line(row);
	oled_goto_column(column);
}


void oled_write_data(uint8_t data)		// Write char to screen
{
    volatile char* ext_oled_data = (char *) OLED_DATA_ADR;		// Start address for OLED data
    ext_oled_data[0] = data;
}


void oled_write_cmd(uint8_t cmd)		// Write command
{
	volatile char* ext_oled_cmd = (char *) OLED_CMD_ADR;		// Start address for OLED command
	ext_oled_cmd[0] = cmd;		                                    // write command
}


void oled_put_char(unsigned char c)		// Put character
{
	uint8_t print_char = c - 32;
	uint8_t font_size  = 8;				// Size of the different fonts. Needs to be calculated.
	
	for (int i = 0; i < font_size; i++)
		oled_write_data(pgm_read_word(&font8[print_char][i]));
}

void oled_put_char_inv(unsigned char c)	// Put inverted character
{
	uint8_t print_char = c - 32;
	uint8_t font_size  = 8;				// Size of the different fonts. Needs to be calculated.
	
	for (int i = 0; i < font_size; i++)
		oled_write_data(~pgm_read_word(&font8[print_char][i]));
}

void oled_print(char* str)			// Print text to screen
{			
	for (int i = 0; i < strlen(str); i++)
		oled_put_char(str[i]);					// write to screen
}

void oled_print_inv(char* str)		// Print inverted text to screen
{
	for (int i = 0; i < strlen(str); i++)
		oled_put_char_inv(str[i]);					// write to screen
}


void oled_fill_line(uint8_t line)		// Fill current line
{
	oled_pos(line, 0);					
	
	for (int i = 0; i < 50; i++)		// Fill line
		oled_write_data(0xFF);
	
	oled_pos(line, 0);					// Set cursor to start of line
}

/* Probably not needed */

void oled_set_addr_mode(int mode)		// Set address mode
{
	if(mode == PAGE)	
	{
		oled_write_cmd(0x20);				//Set Memory Addressing Mode
		oled_write_cmd(PAGE);			//Select page addressing mode
	}
	if(mode == HORIZONTAL)
	{
		oled_write_cmd(0x20);				//Set Memory Addressing Mode
		oled_write_cmd(HORIZONTAL);
	}
}

void oled_print_logo()				// Put raw hex data like logos
{
	for (int j = 1; j <= 64 ; j++)
	{
		oled_write_data(pgm_read_word(&smol_logo[j]));
	}
	
}