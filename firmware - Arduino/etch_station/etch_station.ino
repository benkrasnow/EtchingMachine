#include <SPI.h>
#include <Wire.h>

#include "pin_definitions.h"
#include "oled_display.h"
#include "TMP37.h"
#include "user_setpoints.h"
#include "state_machine.h"
#include "heat_control.h"
#include "linear_actuator.h"

#define OLED_TIMEOUT_MS 600000  //after 10 minutes blank the OLED until a button is pushed

IntervalTimer sysupdate;

unsigned long time_last_UI_event;
elapsedMillis time_since_last_loop;
int time_run_remaining;


void setup() {
  Serial.begin(9600);
  
  NVIC_SET_PRIORITY(IRQ_PORTA, 255);  //TeensyStep requires its internal library interrupts to have a higher priority than most other interrupts.  These IRQs are for gpio, which are used only for UI, and hence don't need high priority anyway.
  NVIC_SET_PRIORITY(IRQ_PORTB, 255);
  NVIC_SET_PRIORITY(IRQ_PORTC, 255);
  NVIC_SET_PRIORITY(IRQ_PORTD, 255);
  NVIC_SET_PRIORITY(IRQ_PORTE, 255); 
  
  pinMode(PIN_BUTTON_GREEN, INPUT_PULLUP);
  pinMode(PIN_BUTTON_YEL1, INPUT_PULLUP);
  pinMode(PIN_BUTTON_YEL2, INPUT_PULLUP);
  pinMode(PIN_BUTTON_RED, INPUT_PULLUP);
  pinMode(0,OUTPUT);
  pinMode(PIN_PUMP, OUTPUT);
  digitalWrite(PIN_PUMP, LOW);
  digitalWrite(0, LOW);
  
  attachInterrupt(PIN_BUTTON_GREEN, green_button_isr, FALLING);
  attachInterrupt(PIN_BUTTON_RED, red_button_isr, FALLING);
  
  oled_init();
  
  sysupdate.priority(160);  //TeensyStep's interrupts must have a higher priority, and the library probably defaults to 128, so we must use interrupts with lower priority (higher numeric value)
  sysupdate.begin(system_update, 50000);

  state_set_state(STATE_STARTUP);
}


void green_button_isr()
{
  time_last_UI_event = millis();
  if(state_get_state() == STATE_HEATING || state_get_state() == STATE_READY)
    {
      actuator_stop();
      actuator_move_async(setpoints_get_linear_start(), setpoints_get_linear_speed());
      time_since_last_loop = 0;
      state_set_state(STATE_RUNNING);
    }
}

void red_button_isr()
{
  time_last_UI_event = millis();
  if(state_get_state() == STATE_RUNNING)
      {
        actuator_stop();
        actuator_move_async(setpoints_get_linear_home(), setpoints_get_linear_speed());
        state_set_state(STATE_READY);
        time_run_remaining = setpoints_get_run_time();
      }
}




void loop() {
  if(state_get_state() == STATE_STARTUP)
    {
      actuator_home();
      state_set_state(STATE_HOMING);
    }
  
  if(state_get_state() == STATE_HOMING && actuator_get_homed() == 1 )
    {
       state_set_state(STATE_HEATING);
       actuator_move(setpoints_get_linear_home(),setpoints_get_linear_speed());
    }
  
  if(state_get_state() == STATE_HEATING && abs(setpoints_get_temperature() - tmp37_get_temperature()) < 1.5)
    {
      state_set_state(STATE_READY);
    }
  
  if(state_get_state() == STATE_READY && abs(setpoints_get_temperature() - tmp37_get_temperature()) > 3)
    {
      state_set_state(STATE_HEATING);
    }

  
  if(state_get_state() == STATE_RUNNING)
    {
      digitalWrite(PIN_PUMP, HIGH);
      time_run_remaining = time_run_remaining - time_since_last_loop;
      time_since_last_loop = 0;
      if(abs(actuator_get_pos() - setpoints_get_linear_start()) < 0.0001)
        {
          actuator_move_async(setpoints_get_linear_end(), setpoints_get_linear_speed());
        }
      if(abs(actuator_get_pos() - setpoints_get_linear_end()) < 0.0001)
        {
           actuator_move_async(setpoints_get_linear_start(), setpoints_get_linear_speed());   
        }

      if(time_run_remaining <= 0)
        {
          actuator_stop();
          actuator_move_async(setpoints_get_linear_home(), setpoints_get_linear_speed());
          state_set_state(STATE_READY);
        }  
    }
    
  if(state_get_state() != STATE_RUNNING)
    {
      digitalWrite(PIN_PUMP, LOW);
      time_run_remaining = setpoints_get_run_time();
    }
  
   delay(10);
}



void system_update()
{
  tmp37_read_temperature();
  setpoints_read_all();
  heat_control_loop(setpoints_get_temperature(), tmp37_get_temperature());
  heat_SSR_update();
  
  if ( (millis() - time_last_UI_event) <  OLED_TIMEOUT_MS)
    {
      oled_update(time_run_remaining);
    }
  else
    {
      oled_blank();
    }
}
