
#ifndef __GAME_FSM_H__
#define __GAME_FSM_H__

typedef enum {
    IDLE,
    INIT,
    RUNNING,
    GAME_OVER,
    OTHERS
} state_t;

void fsm_node_1();

#endif