#ifndef WORDCLOCK_AMBILIGHT_H
#define WORDCLOCK_AMBILIGHT_H
#include <Arduino.h>

#include "../config.h"
#include "../dnd.h"
#include "../led.h"

class Ambilight {
	public:
	static int Mode;
    static int refresh;

	static void display(int second);
};

#endif
