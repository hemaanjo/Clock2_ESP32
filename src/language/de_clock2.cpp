#include <Arduino.h>

#include "de_clock2.h"

#include "../config.h"
#include "../dnd.h"
#include "../led.h"

void Grid_de_clock2::showGrid(bool inLoop) {
  if(inLoop) {
      if(Config::useTypewriter) {
        FastLED.setBrightness(Config::brightness * 255);
        FastLED.show();
        delay(Config::Typewriterdelay);
      }
  }
  else {
      /* code */
      if(Config::useTypewriter==false){
        FastLED.setBrightness(Config::brightness * 255);
        FastLED.show();
      }
  }
}

void Grid_de_clock2::setSingleMinute(int minute){
  inute = minute % 5;
  Serial.printf("SingleMinute=%d\n",minute  );
  Led::clearSection(0);
  for(int i = 0; i < minute; i++) {
    Led::ids[Led::idxled_Min+i].setRGB(Config::color_fg.r, Config::color_fg.g, Config::color_fg.b);
  }
  FastLED.setBrightness(Config::brightness * 255);
  FastLED.show();
}

void Grid_de_clock2::setSecond(int second) {
  
//  Serial.printf("setSecond Ambilight=%d\n",Config::ambilight);
//  Serial.printf("setSecond Config::ambilight_startIDX=%d\n",Config::ambilight_startIDX);
//  Serial.printf("setSecond Config::ambilight_leds=%d\n",Config::Config::ambilight_leds);
//return;

  switch(Config::ambilight) {
    case 0: break;
    case 1: // Seconds :-)
      int secidx;
      if(second <= 30) {
        secidx = Led::idxled_Ambi + 60 - (second-1)*2;
      } else {
        secidx = Led::idxled_Ambi + Led::numled_Ambi - (second-30-1)*2;
      } 
      for(int i = Led::idxled_Ambi; i<Led::idxled_Ambi+Led::numled_Ambi; i+=2) {
        if(i == secidx) {
          Led::ids[i].setRGB(Config::ambilight_color.r,Config::ambilight_color.g,Config::ambilight_color.b);
          Led::ids[i+1].setRGB(Config::ambilight_color.r,Config::ambilight_color.g,Config::ambilight_color.b);
        } else {
          Led::ids[i].setRGB(0,0,0);
          Led::ids[i+1].setRGB(0,0,0);
        }
      }
      break;
    case 2: 
      //for(int i = Config::ambilight_startIDX; i<Config::ambilight_startIDX+Config::ambilight_leds; i++) {
      //  Led::ids[i].setRGB(Config::ambilight_color.r,Config::ambilight_color.g,Config::ambilight_color.b);
      //  };
      break;
  }
  if(Config::ambilight == 1){
     FastLED.setBrightness(Config::brightness * 255);
     FastLED.show();
 //    Serial.printf("setSecond %d",second);
  }
}


void Grid_de_clock2::setTime(int hour, int minute) {
  if(hour == -1 || minute == -1) {
    return;
  }

  if(DND::active(hour, minute)) {
    for(int i = 0; i < NUM_LEDS; i++) {
      Led::ids[i].setRGB(0, 0, 0);
      }
    FastLED.show();
    return;
  }

  int singleMinute = minute % 5;
  int hourLimit = 6;

  minute = (minute - (minute % 5));

  if(minute >= 25) {
	hour += 1;
  }

  minute = minute / 5;
  hour = hour % 12;

  Led::clearSection(0);
  /*if (singleMinute != 0) {
    // nur Minuten löschen
    Grid_de_clock2::setSingleMinute(singleMinute);
    Grid_de_clock2::showGrid(false);
    return;
  }
*/
  Led::clearSection(1);
// Es ist
  for(int i = 0; i < 5; i++) {
    Led::ids[Led::getLedId(Grid_de_clock2::time_it_is[i])].setRGB(Config::color_fg.r, Config::color_fg.g, Config::color_fg.b);
    Grid_de_clock2::showGrid(true);
  }

  for(int m = 0; m < 12; m++) {
	  if(Grid_de_clock2::time_minutes[minute][m] >= 0) {
	    Led::ids[Led::getLedId(Grid_de_clock2::time_minutes[minute][m])].setRGB(Config::color_fg.r, Config::color_fg.g, Config::color_fg.b);
	    Grid_de_clock2::showGrid(true);
    }
  }

  if(hour == 1 && minute == 0) {
	hourLimit = 3;
  }

  for(int h = 0; h < hourLimit; h++) {
	  if(Grid_de_clock2::time_hours[hour][h] >= 0) {
	    Led::ids[Led::getLedId(Grid_de_clock2::time_hours[hour][h])].setRGB(Config::color_fg.r, Config::color_fg.g, Config::color_fg.b);
	    Grid_de_clock2::showGrid(true);
    }
  }

/*
  if(GRID_SINGLE_MINUTES == 1) {
	// single minutes
	for(int s = (NUM_LEDS - 4); s < (NUM_LEDS - 4 + singleMinute); s++) {
	  Led::ids[s].setRGB(Config::color_fg.r, Config::color_fg.g, Config::color_fg.b);
    Grid_de_clock2::showGrid(true);
	}
  } else {
	for(int s = 0; s < singleMinute; s++) {
	  Led::ids[s].setRGB(Config::color_fg.r, Config::color_fg.g, Config::color_fg.b);
    Grid_de_clock2::showGrid(true);
	}
  }
*/
//  FastLED.setBrightness(Config::brightness * 255);
  Grid_de_clock2::showGrid(false);
}

//String Grid_de_clock2::Layout = "clock2";
/*
0     1     2     3     4     5     6     7     8     9     10
E     S     K     I     S     T     A     F     Ü     N     F  
11    12    13    14    15    16    17    18    19    20    21
Z     E     H     N     Z     W     A     N     Z     I     G
22    23    24    25    26    27    28    29    30    31    32
D     R     E     I     V     I     E     R     T     E      L
33    34    35    36    37    38    39    40    41    42    43
V     O     R     F     U     N     K     N     A     C     H
44    45    46    47    48    49    50    51    52    53    54
H     A     L     B     A     E     L     F     Ü     N     F
55    56    57    58    59    60    61    62    63    64    65
E     I     N     S     X     A     M     Z     W     E     I
66    67    68    69    70    71    72    73    74    75    76
D     R     E     I     P     M     J     V     I     E     R
77    78    79    80    81    82    83    84    85    86    87
S     E     C     H     S     N     L     A     C     H     T
88    89    90    91    92    93    94    95    96    97    98
S     I     E     B     E     N     Z     W     Ö     L     F
99    100   101   102   103   104   105   106   107   108   109
Z     E     H     N     E     U     N     K     U     H     R
*/


int Grid_de_clock2::time_it_is[5] = {0, 1, 3, 4, 5}; // es ist

int Grid_de_clock2::time_minutes[12][12] = {
  {107, 108, 109,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1}, // uhr
  {  7,   8,   9,  10,  40,  41,  42,  43,  -1,  -1,  -1,  -1}, // fünf nach
  { 11,  12,  13,  14,  40,  41,  42,  43,  -1,  -1,  -1,  -1}, // zehn nach
  { 26,  27,  28,  29,  30,  31,  32,  40,  41,  42,  43,  -1}, // viertel nach
  { 15,  16,  17,  18,  19,  20,  21,  40,  41,  42,  43,  -1}, // zwanzig nach
  {  7,   8,   9,  10,  33,  34,  35,  44,  45,  46,  47,  -1}, // fünf vor halb
  { 44,  45,  46,  47,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1}, // halb
  {  7,   8,   9,  10,  40,  41,  42,  43,  44,  45,  46,  47}, // fünf nach halb
  { 15,  16,  17,  18,  19,  20,  21,  33,  34,  35,  -1,  -1}, // zwanzig vor
  { 26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  -1,  -1}, // viertel vor
  { 11,  12,  13,  14,  33,  34,  35,  -1,  -1,  -1,  -1,  -1}, // zehn vor
  {  7,   8,   9,  10,  33,  34,  35,  -1,  -1,  -1,  -1,  -1}  // fünf vor
};

int Grid_de_clock2::time_hours[12][6] = {
  { 94,  95,  96,  97,  98,  -1}, // zwölf
  { 55,  56,  57,  58,  -1,  -1}, // eins
  { 62,  63,  64,  65,  -1,  -1}, // zwei
  { 66,  67,  68,  69,  -1,  -1}, // drei
  { 73,  74,  75,  76,  -1,  -1}, // vier
  { 51,  52,  53,  54,  -1,  -1}, // fünf
  { 77,  78,  79,  80,  81,  -1}, // sechs
  { 88,  89,  90,  91,  92,  93}, // sieben
  { 84,  85,  86,  87,  -1,  -1}, // acht
  {102, 103, 104, 105,  -1,  -1}, // neun
  { 99, 100, 101, 102,  -1,  -1}, // zehn
  { 49,  50,  51,  -1,  -1,  -1}  // elf 
};

/*
int Grid_de_clock2::time_it_is[5] = {0, 1, 3, 4, 5}; // es ist

int Grid_de_clock2::time_minutes[12][12] = {
  {107, 108, 109,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1}, // uhr
  {  7,   8,   9,  10,  35,  36,  37,  38,  -1,  -1,  -1,  -1}, // fünf nach
  { 11,  12,  13,  14,  35,  36,  37,  38,  -1,  -1,  -1,  -1}, // zehn nach
  { 26,  27,  28,  29,  30,  31,  32,  35,  36,  37,  38,  -1}, // viertel nach
  { 15,  16,  17,  18,  19,  20,  21,  35,  36,  37,  38,  -1}, // zwanzig nach
  {  7,   8,   9,  10,  39,  40,  41,  44,  45,  46,  47,  -1}, // fünf vor halb
  { 44,  45,  46,  47,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1}, // halb
  {  7,   8,   9,  10,  35,  36,  37,  38,  44,  45,  46,  47}, // fünf nach halb
  { 15,  16,  17,  18,  19,  20,  21,  39,  40,  41,  -1,  -1}, // zwanzig vor
  { 26,  27,  28,  29,  30,  31,  32,  39,  40,  41,  -1,  -1}, // viertel vor
  { 11,  12,  13,  14,  39,  40,  41,  -1,  -1,  -1,  -1,  -1}, // zehn vor
  {  7,   8,   9,  10,  39,  40,  41,  -1,  -1,  -1,  -1,  -1}  // fünf vor
};

int Grid_de_clock2::time_hours[12][6] = {
  { 49,  50,  51,  52,  53,  -1}, // zwölf
  { 57,  58,  59,  60,  -1,  -1}, // eins
  { 55,  56,  57,  58,  -1,  -1}, // zwei
  { 67,  68,  69,  70,  -1,  -1}, // drei
  { 84,  85,  86,  87,  -1,  -1}, // vier
  { 73,  74,  75,  76,  -1,  -1}, // fünf
  {100, 101, 102, 103, 104,  -1}, // sechs
  { 60,  61,  62,  63,  64,  65}, // sieben
  { 89,  90,  91,  92,  -1,  -1}, // acht
  { 80,  81,  82,  83,  -1,  -1}, // neun
  { 93,  94,  95,  96,  -1,  -1}, // zehn
  { 77,  78,  79,  -1,  -1,  -1}  // elf
};
*/