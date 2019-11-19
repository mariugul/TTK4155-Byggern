/*********************************************************
 *                      OLED Menu                        *
 *                                                       *
 * These are the functions to control the OLED menu.     *
 *                                                       *
 * By: Marius C. K. Gulbrandsen and Daniel Rahme         *
 *********************************************************/

// Define for the clock. Needs to be before delay library.
//---------------------------------------------------
#define F_CPU 4915200 // Clock speed

// Includes
//---------------------------------------------------
#include "../inc/menu.h"
#include "../inc/adc.h"
#include "../inc/joystick.h"
#include "../inc/oled.h"
#include <util/delay.h>


// Function Definitions
//---------------------------------------------------

void menu_init()
{
    oled_print("WELCOME!");
    oled_pos(4, 0);
    oled_print_inv("*ENTER GAME*");

    // Wait to display welcome screen
    //oled_print_logo();
    _delay_ms(3000);

    menu_print();
}

void menu_print()
{
    oled_reset();
    oled_goto_line(0);
    oled_print("--- Home ---");

    oled_goto_line(2);
    oled_print("Play");

    oled_goto_line(4);
    oled_print("Highscore");

    oled_goto_line(6);
    oled_print("About");
}

void menu_highlight(menu_state selection)
{
    if (selection == PLAY) {
        oled_goto_line(2);
        oled_print_inv("Play");

    } else if (selection == HIGHSCORE) {
        oled_goto_line(4);
        oled_print_inv("Highscore");

    } else if (selection == ABOUT) {
        oled_goto_line(6);
        oled_print_inv("About");
    }
}

// Highlight and return chosen selection state
menu_state menu_highlight_handler(direction_t dir)
{
    static uint8_t pos = 0; // TODO: Needs a clear
    const uint8_t num_of_states = 3;
    const menu_state states[3] = { PLAY, HIGHSCORE, ABOUT };

    // Early exit
    if (dir != DOWN && dir != UP)
        return states[pos];

    if (dir == DOWN) {
        pos = (pos + 1) % num_of_states;
    } else if (dir == UP) {
        pos = (pos - 1 + num_of_states) % num_of_states;
    }

    menu_print();
    menu_highlight(states[pos]);

    return states[pos];
}

void menu_selection(menu_state selection)
{
    if (selection == PLAY) {
        // Execute play
        printf("PLAY selected\n");

    } else if (selection == HIGHSCORE) {
        // Execute highscore
        printf("HIGHSCORE selected\n");

    } else if (selection == ABOUT) {
        // Execute about
        printf("ABOUT selected\n");
    } else {
        // Error
        printf("Error, no such selection\n");
    }
}