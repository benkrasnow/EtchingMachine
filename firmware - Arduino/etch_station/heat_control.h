#ifndef HEAT_CONTROL_H
#define HEAT_CONTROL_H

float heat_get_state(void);
void heat_SSR_update(void);
void heat_control_loop(float cur_setpoint, float cur_temperature);



#endif
