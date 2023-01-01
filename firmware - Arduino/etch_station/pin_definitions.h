#ifndef PIN_DEFINITIONS_H
#define PIN_DEFINITIONS_H

#define PIN_I2C_SDA0 18
#define PIN_I2C_SCL0 19

#define PIN_TMP37_1 A7

#define PIN_TEMPERATURE_1_SETPOINT A8
#define PIN_TIME_SETPOINT A9

#define PIN_HEATER_SSR 26

#define PIN_PUMP 24

#define PIN_STEPPER_STEP 31
#define PIN_STEPPER_DIR 32


#define PIN_BUTTON_GREEN 1
#define PIN_BUTTON_YEL1 2
#define PIN_BUTTON_YEL2 3
#define PIN_BUTTON_RED 4



#define PIN_HOME_SWITCH 17


/*  defined(__MK64FX512__) || defined(__MK66FX1M0__)
 * void usingInterrupt(uint8_t n) {
      if (n == 3 || n == 4 || (n >= 25 && n <= 28) || (n >= 39 && n <= 42)) {
        usingInterrupt(IRQ_PORTA);
      } else if (n == 0 || n == 1 || (n >= 16 && n <= 19) || (n >= 29 && n <= 32) || (n >= 43 && n <= 46) || n == 49 || n == 50) {
        usingInterrupt(IRQ_PORTB);
      } else if ((n >= 9 && n <= 13) || n == 15 || n == 22 || n == 23 || (n >= 35 && n <= 38)) {
        usingInterrupt(IRQ_PORTC);
      } else if (n == 2 || (n >= 5 && n <= 8) || n == 14 || n == 20 || n == 21 || n == 47 || n == 48 || (n >= 51 && n <= 55)) {
        usingInterrupt(IRQ_PORTD);
      } else if (n == 24 || n == 33 || n == 36 || n == 56 || n == 57) {
        usingInterrupt(IRQ_PORTE);

 */


#endif
