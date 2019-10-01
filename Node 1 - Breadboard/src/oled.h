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
void oled_goto_column(uint8_t column);		// Go to specific column
void oled_clear_line(int line);				// Clear specific line

void oled_pos(int row, int column);			// Go to position
void oled_write_data(uint8_t data);         // Write data
void oled_write_cmd(uint8_t cmd);           // Write command

void oled_print(char* str);					// Write text to screen
void oled_print_inv(char* str);				// Print inverted text to screen
void oled_put_char(unsigned char c);		// Print char to screen
void oled_put_char_inv(unsigned char c);	// Print inverted char to screen

void oled_fill_line(uint8_t line);			// Fill current line
void oled_set_addr_mode(int mode);			// This can proably be removed
void oled_print_logo();						// Put raw hex data like logos

#endif