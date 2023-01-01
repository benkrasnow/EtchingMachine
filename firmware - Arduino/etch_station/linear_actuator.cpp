#include<Arduino.h>
#include "linear_actuator.h"
#include "TeensyStep.h"
#include "pin_definitions.h"

Stepper motor(PIN_STEPPER_STEP, PIN_STEPPER_DIR);
StepControl controller;    // Use default settings 

int homed = 0;

void actuator_home(void)
{
  pinMode(PIN_HOME_SWITCH, INPUT_PULLUP);
  delay(1);
  motor.setMaxSpeed(700);
  motor.setAcceleration(80000);
  if(digitalRead(PIN_HOME_SWITCH) == 1)  //The home switch is already closed.  Move the carriage away so that we can return and catch the rising edge of the switch closure.
    {
      motor.setTargetRel(200);
      controller.move(motor);
    }
  
  motor.setTargetRel(-30000);  
  controller.moveAsync(motor);
  attachInterrupt(PIN_HOME_SWITCH, home_switch_triggered, RISING);
  
}

void actuator_stop(void)
{
  controller.stop();
}

int actuator_get_homed(void)
{
  return homed;
}

float actuator_get_pos(void)
{
  return ((float)motor.getPosition() / (MICROSTEPPING * STEPS_FULLTRAVEL));
}

void home_switch_triggered()
{
  detachInterrupt(PIN_HOME_SWITCH);
  controller.stop();
  motor.setPosition(0);
  homed = 1;
}


void actuator_move_async(float new_position, float new_speed)
{
  if(new_position <= 1.0 && new_position >= 0 && new_speed > 0.01 && new_speed <=1.0)
    {
       motor.setMaxSpeed(new_speed * MICROSTEPPING * MAXIMUM_RUN_SPEED);
       motor.setAcceleration(NORMAL_ACCELERATION * MICROSTEPPING);
       motor.setTargetAbs(new_position * MICROSTEPPING * STEPS_FULLTRAVEL);
       controller.moveAsync(motor);
    }
  
}

void actuator_move(float new_position, float new_speed)
{
  if(new_position <= 1.0 && new_position >= 0 && new_speed > 0.01 && new_speed <=1.0)
    {
       motor.setMaxSpeed(new_speed * MICROSTEPPING * MAXIMUM_RUN_SPEED);
       motor.setAcceleration(NORMAL_ACCELERATION * MICROSTEPPING);
       motor.setTargetAbs(new_position * MICROSTEPPING * STEPS_FULLTRAVEL);
       controller.move(motor);
    }
  
}
