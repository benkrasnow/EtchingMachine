#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H


#define STATE_STARTUP 1
#define STATE_HOMING 2
#define STATE_HEATING 3
#define STATE_READY 4
#define STATE_RUNNING 5
#define STATE_PAUSED 6
#define STATE_ENDING 7


int state_get_state(void);
void state_set_state(int newstate);


#endif
