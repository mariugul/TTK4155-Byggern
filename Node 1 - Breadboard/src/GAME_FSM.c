/*******************
 * 
 * CAN Status messages:
 * I - Init
 * R - Ready
 * G - Game over
 * Q - Quit / Reset
 * 
 *******************/

#include "../inc/GAME_FSM.h"
#include "../inc/menu.h"
#include "../inc/joystick.h"
#include "../inc/joystick_to_can.h"
#include "../inc/adc.h"
#include "../inc/can.h"
#include "../inc/gpio.h"
#include "../inc/oled.h"
#include <util/delay.h>




// Handle the transitions between the states
/*
void update_state(uint8_t play, uint8_t nodes_ready, uint8_t ball_detected)
{
    if (current_state == IDLE) {
        // Button press - select play
        if (play) {
            current_state = INIT;
        }

    } else if (current_state == INIT) {
        // Send over can and receive acc back
        // Init stuff
        if (nodes_ready) {
            current_state = RUNNING;
        }

    } else if (current_state == RUNNING) {
        // Send joy
        // Receive ball detect
        if (ball_detected) {
            current_state = GAME_OVER;
        }

    } else if (current_state == GAME_OVER) {
        // Wait a couple of loops
        // Go back to idle

    } else {
        current_state = IDLE;
    }
}
*/


void output_state()
{
    static state_t current_state = IDLE;

    if (current_state == IDLE) {
        printf("State: IDLE\n");
        // MENU
        const int button_pressed = gpio_read_button(push_r);// Push button right
        const joy_t joy = get_joystick();
        const menu_state current_selection = menu_highlight_handler(joy.dir_y);

        if (button_pressed && current_selection == PLAY) {
            current_state = INIT;
        }


    } else if (current_state == INIT) {
        printf("State: INIT\n");
        menu_init_print();
        
        // Send init message
        can_message msg = {
            .id = 1,
            .length = 1,
            .data[0] = 'I'
        };
        can_send(&msg);

		can_message node2 = can_receive();
        if (node2.id == 2 && node2.data[0] == 'R') {
            current_state = RUNNING;
        }


    } else if (current_state == RUNNING) {
        printf("State: RUNNING\n");
        menu_game_running_print();
        send_joystick_to_can();

        // Receive ball detected -> Game over
		can_message node2 = can_receive();
        if (node2.id == 3 && node2.data[0] == 'G') {
            current_state = GAME_OVER;
        }


    } else if (current_state == GAME_OVER) {
        printf("State: GAME_OVER\n");

        menu_game_over_print();

        // Send Quit message to node2
        can_message msg = {
            .id = 5,
            .length = 1,
            .data[0] = 'Q'
        };
        can_send(&msg);
		_delay_ms(50);
        can_send(&msg);
		_delay_ms(50);
        can_send(&msg);
		_delay_ms(50);

		_delay_ms(3000);
        menu_print();

    } else {
        printf("State: OTHERS\n");
        // should not come here
        // Disable stuff
        current_state = IDLE;
    }

}