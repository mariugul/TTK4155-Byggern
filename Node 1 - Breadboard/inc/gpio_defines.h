/* These are the defines used in gpio.c to set pins. */
#include <avr/io.h>

#define SET_OUTPUT(reg, pin) (reg |= (1 << pin))   // Set PORTx to output
#define SET_INPUT(reg, pin) (reg &= ~(1 << pin))   // Set PORTx to input
#define SET_PIN(port, pin) (port |= (1 << pin))    // Set PINx to HIGH
#define CLEAR_PIN(port, pin) (port &= ~(1 << pin)) // Set PINx to LOW

#define PIN_LED PB0     // Status LED
#define PIN_LBUT PB1    // Left push button on board
#define PIN_RBUT PB2    // Right push button on board
#define PIN_JBUT PB3    // Joystick push button on board
#define PIN_MCP_INT PB4 // MCP2515 output interrupt pin

#define OUTPUT 1 // Decides to define pin as OUTPUT
#define INPUT 0  // Decides to define pin as INPUT
#define HIGH 1   // Decides to define pin as HIGH
#define LOW 0    // Decides to define pin as LOW

/* Sets the port to either output or input and also sets it to HIGH or LOW.*/
#define SET_PORT(reg, io, port, pin, val)               \
    ({                                                  \
        /*OUTPUT was selected*/                         \
        if ((io) == OUTPUT)                             \
        {                                               \
            SET_OUTPUT(reg, pin);                       \
                                                        \
            /*Set HIGH OR LOW*/                         \
            if (val == HIGH)                            \
                SET_PIN(port, pin);                     \
            else                                        \
                CLEAR_PIN(port, pin);                   \
        }                                               \
                                                        \
        /*INPUT was selected*/                          \
        else if ((io) == INPUT)                         \
        {                                               \
            SET_INPUT(reg, pin);                        \
                                                        \
            /*Set HIGH OR LOW*/                         \
            if (val == HIGH)                            \
                SET_PIN(port, pin);                     \
            else                                        \
                CLEAR_PIN(port, pin);                   \
        }                                               \
    })
