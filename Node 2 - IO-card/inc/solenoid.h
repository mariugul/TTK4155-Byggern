#ifndef __SOLENOID_H__
#define __SOLENOID_H__

#include <avr/io.h>
#include <stdbool.h>

void Solenoid_Init();
bool Solenoid_Pulse();
void Solenoid_Activate();
void Solenoid_Decativate();

/*INTERRUPT HANDLER HERE*/
void Solenoid_IRQ_Handler();

#endif