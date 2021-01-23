#ifndef WORDCLOCK_LED_H
#define WORDCLOCK_LED_H

#define FASTLED_INTERNAL
#include <FastLED.h>

#define NUM_LEDS ((GRID_ROWS * GRID_COLS) + 4 + 120)

class Led {
  public:
    static CRGB ids[];
     
    static int numled_Grid;
    static int numled_Min;
    static int numled_Ambi;

    static int getLedId(int id);
    static void setup();
    static double getMaxBrightnessPercnt();
    static int getMaxNumberIlluminatedLeds();

    static void firstRun();
};

#endif
