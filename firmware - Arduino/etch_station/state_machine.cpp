#include<Arduino.h>
#include "state_machine.h"

int current_state = 1;

int state_get_state(void)
{
  return current_state;
}


void state_set_state(int newstate)
{
  current_state = newstate;
}
