/*********************************************************
 *             NODE 1 - Ping Pong Game                   *
 *     This is the main file for controlling Node 1.     *
 *														 *
 * By: Marius C. K. Gulbrandsen and Daniel Rahme         *
 *********************************************************/

// Header Guard
//---------------------------------------------------
#ifndef __MAIN_H_
#define __MAIN_H_

// Definitions
//---------------------------------------------------

// This is the oscillator speed. It needs to be defined first because of util/delay library.
#define F_CPU 16000000UL

// Typedefs
//---------------------------------------------------
typedef enum {
    IDLE,
    INIT,
    RUNNING,
    GAME_OVER,
    OTHERS
} state_t;

// Function Prototypes
//---------------------------------------------------
void fsm_node_1();

#endif
//---------------------------------------------------
// End Main.h
//---------------------------------------------------