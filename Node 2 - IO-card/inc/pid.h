#ifndef __PID_H__
#define __PID_H__

void PID_Init();
void PID_Update();
void PID_Get_Pos();
void PID_Update_Pos(uint8_t joystick_pos);
void PID_Error_Calc();
void PID_Integral_Calc();
void PID_Derivative_Calc();
void PID_Ctrl_Var_calc();

#endif