#include <FastLED.h>
#include <ArduinoOTA.h>
#include "OTA.h"

#define NUM_LEDS 28
#define DATA_PIN 22
#define LED_DELAY 50
#define LED_WAIT 1000

CRGB leds[NUM_LEDS];
    
void setup() {
  ota::setup();
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness( 40 );

}

void loop() {
  ota::loop();
  for(int col = 0; col < 3; col++) {
    for(int i = 0; i < NUM_LEDS; i++) {
      int led = i;
      switch(col) {
        case 0: leds[led] = CRGB::Red; break;
        case 1: leds[led] = CRGB::Green; break;
        case 2: leds[led] = CRGB::Blue; break;
        }
       
      FastLED.show();
      delay(LED_DELAY);
      
      /*leds[led] = CRGB::Black;
      FastLED.show();
      delay(LED_DELAY);*/
    }
  }

    for(int i = 0; i < NUM_LEDS; i++) {
      int led = i;
      leds[led] = CRGB::White; 
      
    }
    FastLED.show();
    delay(LED_WAIT);

    for(int i = 0; i < NUM_LEDS; i++) {
      int led = i;
      leds[led] = CRGB::Black; 
      
    }

    FastLED.show();
}
