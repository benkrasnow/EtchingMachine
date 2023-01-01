#include<Arduino.h>
#include "user_setpoints.h"
#include "pin_definitions.h"

float temperature_setpoint;
int runtime_setpoint;

void setpoints_read_all(void)
{
  analogReadResolution(16);
  analogReadAveraging(32);
  uint16_t raw_adc = analogRead(PIN_TEMPERATURE_1_SETPOINT);
  temperature_setpoint = ((float)raw_adc/65536.0)*50.0+10.0;
  runtime_setpoint = analogRead(PIN_TIME_SETPOINT) * 16;
}

float setpoints_get_temperature(void)
{
  return temperature_setpoint;
}


float setpoints_get_linear_home(void)
{
  return 0.05;
}

float setpoints_get_linear_start(void)
{
  return 0.2;
}

float setpoints_get_linear_end(void)
{
  return 0.8;
}

float setpoints_get_linear_speed(void)
{
  return 0.6;
}

int setpoints_get_run_time(void)
{
  return runtime_setpoint;
}
