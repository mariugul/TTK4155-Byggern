
#include "../inc/GAME_FSM.h"
#include "../inc/menu.h"
#include "../inc/joystick.h"
#include "../inc/joystick_to_can.h"
#include "../inc/adc.h"
#include "../inc/can.h"
#include "../inc/gpio.h"
#include "../inc/oled.h"
#include <util/delay.h>




void output_state()
{
    static state_t current_state = IDLE;

    //--------------------------//
    //---------- IDLE ----------//
    //--------------------------//
    if (current_state == IDLE) {
        printf("State: IDLE\n");
        // MENU
        const int button_pressed    = gpio_read_button(push_r);// Push button right
        const joy_t joy             = get_joystick();
        const menu_state current_selection = menu_highlight_handler(joy.dir_y);

        if (button_pressed && current_selection == PLAY) {
            current_state = INIT;
        }

        can_send_reset();
        _delay_ms(100);

    //--------------------------//
    //---------- INIT ----------//
    //--------------------------//
    } else if (current_state == INIT) {
        printf("State: INIT\n");
        menu_init_print();
        
        // Send init message
        can_send_init();
        _delay_ms(100);

        // Send ready
		can_message node2 = can_receive();
        if (node2.id == NODE2_READY_ID && node2.data[0] == 'R') {
            current_state = RUNNING;

            // Send start
            for (int i = 0; i < 10; i++) {
                can_send_start();
                _delay_ms(100);
            }
        }


    //-----------------------------//
    //---------- RUNNING ----------//
    //-----------------------------//
    } else if (current_state == RUNNING) {
        printf("State: RUNNING\n");
        menu_game_running_print();
        send_joystick_to_can();

        // Receive ball detected -> Game over
		can_message node2 = can_receive();
        if (node2.id == NODE2_GAME_OVER_ID && node2.data[0] == 'G') {
            current_state = GAME_OVER;
        }


    //-------------------------------//
    //---------- GAME OVER ----------//
    //-------------------------------//
    } else if (current_state == GAME_OVER) {
        printf("State: GAME_OVER\n");
        menu_game_over_print();

        // Send Quit message to node2 10 times
        for (int i = 0; i < 10; i++) {
            can_send_reset();
            _delay_ms(1000);
        }

		_delay_ms(3000);
        menu_print();
        current_state = IDLE;

    //-------------------------------//
    //---------- OTHERS -------------//
    //-------------------------------//
    } else {
        printf("State: OTHERS\n");
        // should not come here
        // Disable stuff
        menu_print();
        current_state = IDLE;
    }

}