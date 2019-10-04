/* * menu.h
 *
 *  Created: 14.10.2019 11:04
 *  Author: Daniel
 */ 
#include "adc.h"
#include "menu.h"
#include "oled.h"


void menu_print()
{
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
menu_state menu_highlight_handler(enum direction dir)
{
    static uint8_t pos = 0; // TODO: Needs a clear
    const uint8_t num_of_states = 3;
    const menu_state states[3] = {PLAY, HIGHSCORE, ABOUT};

    // Early exit
    if (dir != DOWN && dir != UP) return states[pos];

    if (dir == DOWN) {
        pos = (pos + 1) % num_of_states;
    }
    else if (dir == UP) {
        pos = (pos - 1 + num_of_states) % num_of_states;
    }

    menu_print();
    menu_highlight(states[pos]);

    return states[pos];
}

void do_menu_selection(menu_state selection)
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