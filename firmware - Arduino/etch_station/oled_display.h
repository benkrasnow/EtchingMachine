#ifndef OLED_DISPLAY_H
#define OLED_DISPLAY_H

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define SCREEN_ADDRESS 0x3D
#define OLED_RESET     -1 

void oled_init(void);

void oled_update(int time_run_remaining);
void oled_blank(void);

#endif
