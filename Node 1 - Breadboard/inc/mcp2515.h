 /*Low level driver for setting up the CAN controller 
  *and accessing its control and status registers
  */

#ifndef __MCP2515_H_              // HEADER GUARD
#define __MCP2515_H__

#include <avr/io.h>
#include <stdbool.h>


void    mcp_init();
void    mcp_reset();
uint8_t mcp_read(uint8_t address);
void    mcp_write(uint8_t address, uint8_t data);
void    mcp_rts(uint8_t transmitt_buffer);
uint8_t mcp_read_status();
void    mcp_bit_mod(uint8_t address, uint8_t mask, uint8_t data);
void    mcp_activate();
void    mcp_deactivate();

#endif 