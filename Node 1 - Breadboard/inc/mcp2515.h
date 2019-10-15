 /*Low level driver for setting up the CAN controller 
  *and accessing its control and status registers
  */

#ifndef __MCP2515_H_              // HEADER GUARD
#define __MCP2515_H__

#include <avr/io.h>
#include <stdbool.h>


uint8_t mcp_init(uint8_t mode);
void    mcp_reset();
uint8_t mcp_read(uint8_t address);
void    mcp_write(uint8_t address, uint8_t data); 
void    mcp_rts(uint8_t transmitt); 
uint8_t mcp_read_status();
void    mcp_bit_mod(uint8_t address, uint8_t mask, uint8_t data);
void    mcp_activate();
void    mcp_deactivate();
void    mcp_prepare_message(uint8_t id, uint8_t data_lenght);

#endif 