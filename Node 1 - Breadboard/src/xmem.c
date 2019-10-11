#include "../inc/xmem.h"

void xmem_init()                      // Initialize external memory
{
	MCUCR =  (1 << SRE);	     	  // Activate external memory
	SFIOR =  (1 << XMM2);			  // Mask JTAG pins
}