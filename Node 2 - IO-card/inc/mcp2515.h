 /*Low level driver for setting up the CAN controller 
  *and accessing its control and status registers
  */

#ifndef __MCP2515_H_              // HEADER GUARD
#define __MCP2515_H__

#include <avr/io.h>
#include <stdbool.h>
#include <stdio.h>

uint8_t MCP_Init(uint8_t mode);
void    MCP_Reset();
uint8_t MCP_Read(uint8_t address);
void    MCP_Write(uint8_t address, uint8_t data); 
void    MCP_Rts(uint8_t transmitt); 
uint8_t MCP_Read_Status();
void    MCP_Bit_Mod(uint8_t address, uint8_t mask, uint8_t data);
void    MCP_Activate();
void    MCP_Deactivate();

#endif 