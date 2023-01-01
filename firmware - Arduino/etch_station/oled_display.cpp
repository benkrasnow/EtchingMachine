
#include "oled_display.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "TMP37.h"
#include "user_setpoints.h"
#include "heat_control.h"
#include "state_machine.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void oled_init(void)
{
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.clearDisplay();
  display.display();
  display.setTextColor(SSD1306_WHITE);
}


void oled_blank(void)
{
  display.clearDisplay();
  display.display();
}

void oled_update(int time_run_remaining)
{
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.print("ACTUAL");
  display.setCursor(0, 36);
  display.print("SET");
  display.setCursor(0, 12);
  display.setTextSize(2);
  display.print(tmp37_get_temperature(),1);
  display.setCursor(0, 46);
  display.print(setpoints_get_temperature(),1);
  if(heat_get_state() > 0.001)
    {
      display.setCursor(70,12);
      display.setTextSize(1);
      display.print("HEAT ON");
    }


 display.setCursor(70,46);
 display.setTextSize(2);
 display.print(time_run_remaining/1000);
 display.setCursor(70,36);
 display.setTextSize(1);
 display.print("TIME");

 
 display.setCursor(70,0);
 display.setTextSize(1);
 switch(state_get_state())
  {
    case STATE_STARTUP:
      display.print("STARTUP");
      break;
    case STATE_HOMING:
      display.print("HOMING");
      break;
    case STATE_HEATING:
      display.print("HEATING");
      break;
    case STATE_READY:
      display.print("READY");
      break;
    case STATE_RUNNING:
      display.print("RUNNING");
      break;
    case STATE_PAUSED:
      display.print("PAUSED");
      break;
      
      
  }
  
  display.display();
  
}
