#include "../inc/Servo.h"
#include "../inc/PWM.h"

// Initialize Servo
void Servo_Init()
{
    printf("<Servo Initialized>\n");
    PWM_Init();

    // Start in the middle
    float start_pos = 127.5;
    Servo_Set_Pos(start_pos);
}

// Returns Servo position from joystick values (pulse width in seconds)
void Servo_Set_Pos(float joystick_pos)
{
    // ! Joystick_pos has to be ADC values (0-255)
    // ! and not percentage values (-100 to 100).

    // Joystick max and min values
    uint8_t max = 255;
    uint8_t min = 0;

    // Error check and set the joystick position value
    if (joystick_pos > max)
        PWM_Set_Pulse_Width(max);

    else if (joystick_pos < min)
        PWM_Set_Pulse_Width(min);

    else
        PWM_Set_Pulse_Width(joystick_pos);
}
