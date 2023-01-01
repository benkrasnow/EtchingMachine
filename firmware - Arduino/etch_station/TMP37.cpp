#include <Arduino.h>
#include "TMP37.h"
#include "pin_definitions.h"


float temperature_one;



void tmp37_read_temperature(void)
{
  analogReadResolution(16);
  analogReadAveraging(32);
  uint16_t raw_adc_temperature = analogRead(PIN_TMP37_1);
  temperature_one = ((((float)raw_adc_temperature/65536.0)*3.3-0.5)/0.02)+25.0;
}

float tmp37_get_temperature(void)
{
  return temperature_one;
}
