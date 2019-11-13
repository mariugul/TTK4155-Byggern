#ifndef __DAC_H__
#define __DAC_H__

#include <stdint.h>
#include <stdio.h>

void DAC_Init();
void DAC_Send(uint8_t data);

#endif