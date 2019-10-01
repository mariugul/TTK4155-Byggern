/*
 * oled.h
 *
 * Created: 28.09.2019 18:00:29
 *  Author: Marius
 */ 

#ifndef __OLED_H__                           // HEADER GUARD
#define __OLED_H__

#include <avr/io.h>							// Include AVR library


void oled_init();							// Initialize oled
void oled_reset();							// Reset display
void oled_home();							// Go to home screen
void oled_goto_line(int line);				// Go to specific line
void oled_goto_column(int column);			// Go to specific column
void oled_clear_line(int line);				// Clear specific line
void oled_pos(int row, int column);			// Go to position
void oled_put_char(char c);                 // Write char to screen
void oled_print(char* string);					// Write text to screen
void oled_command(int cmd);                 // Write command

#endif