#ifndef USER_SETPOINTS_H
#define USER_SETPOINTS_H


void setpoints_read_all(void);
float setpoints_get_temperature(void);
float setpoints_get_linear_start(void);
float setpoints_get_linear_end(void);
float setpoints_get_linear_speed(void);
float setpoints_get_linear_home(void);
int setpoints_get_run_time(void);


#endif
