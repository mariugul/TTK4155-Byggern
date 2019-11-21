/*********************************************************
 *                      OLED Menu                        *
 *                                                       *
 * These are the functions to control the OLED menu.     *
 *                                                       *
 * By: Marius C. K. Gulbrandsen and Daniel Rahme         *
 *********************************************************/

// Header Guard
//---------------------------------------------------
#ifndef __MENU_H__
#define __MENU_H__

// Includes
//---------------------------------------------------
#include "../inc/joystick.h" // For "direction_t" typedef

// Typedefs
//---------------------------------------------------
typedef enum
{
    PLAY,
    HIGHSCORE,
    ABOUT,
    HOME,
    NOTHING
} menu_state;

// Function Prototypes
//---------------------------------------------------
void menu_init();
void menu_print();
void menu_init_print();
void menu_about_print();
void menu_game_running_print();
void menu_game_over_print();
void menu_highlight(menu_state selection);
menu_state menu_highlight_handler(direction_t dir);
void menu_selection(menu_state selection);

#endif