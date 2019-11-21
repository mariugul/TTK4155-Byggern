/*********************************************************
 *                  XMEM for EEPROM                      *
 *                                                       *
 * This files initializes the program memory.            *
 *														 *
 * By: Marius C. K. Gulbrandsen and Daniel Rahme         *
 *********************************************************/

// Includes
//---------------------------------------------------
#include "../inc/xmem.h"

// Function Definitions
//---------------------------------------------------
void xmem_init() // Initialize external memory
{
    MCUCR = (1 << SRE); // Activate external memory
    SFIOR = (1 << XMM2); // Mask JTAG pins
}