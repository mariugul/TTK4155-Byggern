/* * menu.h
 *
 *  Created: 14.10.2019 11:04
 *  Author: Daniel
 */ 

#ifndef __MENU_H__                              // HEADER GUARD
#define __MENU_H__

typedef enum {
    PLAY,
    HIGHSCORE,
    ABOUT,
	HOME,
    NOTHING
} menu_state;

void menu_print();
void menu_highlight(menu_state selection);
menu_state menu_highlight_handler(enum direction dir);
void do_menu_selection(menu_state selection);

#endif