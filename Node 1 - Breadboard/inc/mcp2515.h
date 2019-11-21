/*********************************************************
 *             CAN Controller: MCP2515                   *
 *                                                       *
 * This is the CAN Driver for controlling the CAN Bus.   *
 * It used an SPI driver to function with the Atmega162 *
 * By: Marius C. K. Gulbrandsen and Daniel Rahme         *
 *********************************************************/

// Header Guard
//---------------------------------------------------
#ifndef __MCP2515_H_              
#define __MCP2515_H__

// Includes
//---------------------------------------------------
#include <avr/io.h>
#include <stdbool.h>

// Function Prototypes
//---------------------------------------------------
uint8_t mcp_init(uint8_t mode);
void    mcp_reset();
uint8_t mcp_read(uint8_t address);
void    mcp_write(uint8_t address, uint8_t data); 
void    mcp_rts(uint8_t transmitt); 
uint8_t mcp_read_status();
void    mcp_bit_mod(uint8_t address, uint8_t mask, uint8_t data);
void    mcp_activate();
void    mcp_deactivate();

#endif 