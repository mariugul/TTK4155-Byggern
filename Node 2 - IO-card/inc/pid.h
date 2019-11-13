#ifndef __PID_H__
#define __PID_H__

#include "../inc/Motor.h"
#include <stdint.h>
#include <avr/io.h>
#include <stdio.h>

void PID_Init();
void PID_Get_Pos();
void PID_Error_Calc();
void PID_Update_Last_Error();
void PID_Proportional_Calc();
void PID_Integral_Calc();
void PID_Derivative_Calc();
uint8_t PID_Speed_Calc();
direction_t PID_Direction_Calc();
void PID_Update_Pos(uint8_t joystick_pos);

#endif