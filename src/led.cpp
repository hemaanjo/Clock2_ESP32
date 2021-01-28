
#include "grid.h"
#include "led.h"
#include "config.h"

int Led::numled_Ambi{};
int Led::numled_Grid{};
int Led::numled_Min{};

CRGB Led::ids[NUM_LEDS];

void Led::setup() {
  Led::numled_Ambi = Config::ambilight_leds;
  Led::numled_Grid = GRID_COLS * GRID_ROWS;
  Led::numled_Min = 4;
  
  FastLED.addLeds<NEOPIXEL, PIN4DATA>(Led::ids, Led::numled_Grid+Led::numled_Min+Led::numled_Ambi);
  FastLED.setBrightness(50);

  for(int i = 0; i < Led::numled_Grid+Led::numled_Min+Led::numled_Ambi; i++) {
    Led::ids[i].setRGB(0, 0, 0);
  }
  
  FastLED.show();
  
}

int Led::getLedId(int id) {
  int col = id % GRID_COLS;
  int row = (floor)(id / GRID_COLS);
  int led = 0;

  if(GRID_FIRST == 3) {
    led = (row % 2 != GRID_ROWS % 2) ? (GRID_ROWS - row) * GRID_COLS - 1 - col : (GRID_ROWS - row - 1) * GRID_COLS + col;
  } else if(GRID_FIRST == 2) {
    led = (row % 2 == GRID_ROWS % 2) ? (GRID_ROWS - row) * GRID_COLS - 1 - col : (GRID_ROWS - row - 1) * GRID_COLS + col;
  } else if(GRID_FIRST == 1) {
    led = (row % 2 == 0) ? ((row * GRID_COLS) + col) : ((row + 1) * GRID_COLS) - col - 1;
  } else if(GRID_FIRST == 0) {
    led = (row % 2 == 1) ? ((row * GRID_COLS) + col) : ((row + 1) * GRID_COLS) - col - 1;
  }

  if(GRID_SINGLE_MINUTES == 0) {
    led += 4;
  }
  return led;
}

double Led::getMaxBrightnessPercnt() {
  const int max_consumption = getMaxNumberIlluminatedLeds() * CONSUMPTION_PER_LED;
  const double brightness_percnt = (Config::power_supply - CONSUMPTION_D1_MINI) / (double) max_consumption;

  return (brightness_percnt >= 1.0) ? 1.0 : brightness_percnt;
}

int Led::getMaxNumberIlluminatedLeds() {
  int max_time_it_is = sizeof(Grid::time_it_is)/sizeof(Grid::time_it_is[0]);
  int max_time_minutes = sizeof(Grid::time_minutes[0])/sizeof(Grid::time_minutes[0][0]);
  int max_time_hours = sizeof(Grid::time_hours[0])/sizeof(Grid::time_hours[0][0]);

  return max_time_it_is + max_time_minutes + max_time_hours;
}

#define LED_DELAY 10
#define LED_WAIT 1000

void Led::firstRun(){

  for(int col = 0; col < 3; col++) {
    for(int i = 0; i < Led::numled_Grid+Led::numled_Min+Led::numled_Ambi; i++) {
      int led = i;
      switch(col) {
        case 0: Led::ids[led] = CRGB::Red; break;
        case 1: Led::ids[led] = CRGB::Green; break;
        case 2: Led::ids[led] = CRGB::Blue; break;
        }
       
      FastLED.show();
      delay(LED_DELAY);
      
      /*leds[led] = CRGB::Black;
      FastLED.show();
      delay(LED_DELAY);*/
    }
  }

    //for(int i = 0; i < Led::numled_Grid+Led::numled_Min+Led::numled_Ambi; i++) {
    //  int led = i;
    //  Led::ids[led] = CRGB::White; 
    //  
    //}
    //FastLED.show();
    //delay(LED_WAIT);

    for(int i = NUM_LEDS; i >= 0; i--) {
      int led = i;
      Led::ids[led] = CRGB::Black; 
      
    }

    FastLED.show();

}
