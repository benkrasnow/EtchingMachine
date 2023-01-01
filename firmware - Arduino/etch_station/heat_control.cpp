#include<Arduino.h>
#include "heat_control.h"
#include "pin_definitions.h"

float heater_state = 0;

void heat_control_loop(float cur_setpoint, float cur_temperature)
{
  if(cur_setpoint > 10.0 && cur_setpoint < 60.0 && cur_temperature > 1.0 && cur_temperature < 60.0)
    {
      if(cur_temperature < cur_setpoint)
        {
          heater_state = 1.0;
        }
      else
       {
          heater_state = 0;
       }
    }
   else
   {
    heater_state = 0;
    //perhaps set a fault condition here
   }
}

void heat_SSR_update(void)
{
  pinMode(PIN_HEATER_SSR, OUTPUT);
  
  if(heater_state > 0.5)
    {
      digitalWrite(PIN_HEATER_SSR, HIGH);
    }
   else
    {
      digitalWrite(PIN_HEATER_SSR, LOW);   
    }
}

float heat_get_state(void)
{
  return heater_state;
}
