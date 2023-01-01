#ifndef LINEAR_ACTUATOR_H
#define LINEAR_ACTUATOR_H

#define MICROSTEPPING 8
#define STEPS_FULLTRAVEL 1150
#define MAXIMUM_RUN_SPEED 1500
#define NORMAL_ACCELERATION 2500


void actuator_home(void);
void actuator_move_async(float new_position, float new_speed);
void actuator_move(float new_position, float new_speed);
void actuator_stop(void);
int actuator_get_homed(void);
void home_switch_triggered();

float actuator_get_pos(void);

#endif
