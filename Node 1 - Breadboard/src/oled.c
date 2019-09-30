/*
 * oled.c
 *
 * Created: 28.09.2019 18:00:16
 *  Author: Marius
 */ 

#include "oled.h"

#define OLED_CMD_ADR      0x1000
#define OLED_DATA_ADR     0x1200
#define OLED_ADDR_SIZE    0x400

									
// Initialize oled
void oled_init()
{
    static FILE mystdout = FDEV_SETUP_STREAM(oled_put_char, NULL, _FDEV_SETUP_WRITE);
}

// Reset display
void oled_reset()
{
	
}

// Go to home screen
void oled_home()
{
	
}

// Go to specific line
void oled_goto_line(int line)
{
	
}

// Go to specific column
void oled_goto_column(int column)
{
	
}

// Clear specific line
void oled_clear_line(int line)
{
	
}

// Go to position
void oled_pos(int row, int column)
{
	
}

// Write char to screen
void oled_put_char(char c)
{
    volatile char* ext_oled_data = (char *) OLED_DATA_ADR;		// Start address for OLED data
    ext_oled_data = c;
}

// Write text to screen
void oled_print(char* string)
{
	volatile char* ext_oled_data = (char *) OLED_DATA_ADR;		// Start address for OLED data
	ext_oled_data = string;									    // Write to screen
}

// Write command
void oled_command(int command)
{
    volatile char* ext_oled_cmd = (char *) OLED_DATA_CMD;		// Start address for OLED command
	ext_oled_cmd = command;		                                    // write command
}