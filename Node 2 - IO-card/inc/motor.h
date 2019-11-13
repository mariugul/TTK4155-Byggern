#ifndef __MOTOR_H__
#define __MOTOR_H__

#include <avr/io.h>
#include "../inc/GPIO_Defines.h"
#include <stdio.h>

typedef enum{left, right, stop} direction_t;

int16_t Motor_Read();
void Motor_Init();
void Motor_Encoder_Reset();
void Motor_Set_Dir(direction_t dir);
void Motor_Set_Speed(uint8_t speed);
void Motor_Move(uint8_t dir, uint8_t speed);

#endif