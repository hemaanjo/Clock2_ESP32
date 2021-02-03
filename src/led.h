#ifndef WORDCLOCK_LED_H
#define WORDCLOCK_LED_H

#define FASTLED_INTERNAL
#include <FastLED.h>

#define NUM_LEDS ((GRID_ROWS * GRID_COLS) + 4 + 120)

class LED_SECTION {
  public:
    const int Minutes = 0;
    const int Grid = 1;
    const int Ambilight = 2;
};

class Led {
  public:
    static CRGB ids[];
     
    static int numled_Grid;
    static int numled_Min;
    static int numled_Ambi;
    static int idxled_Grid;
    static int idxled_Min;
    static int idxled_Ambi;

    static int getLedId(int id);
    static void setup();
    static double getMaxBrightnessPercnt();
    static int getMaxNumberIlluminatedLeds();

    static void showAmbilight();
    static void clearSection(LED_SECTION);

    static void firstRun();
};

#endif
