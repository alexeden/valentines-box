#ifndef __Neopixels__
#define __Neopixels__

#include <Wire.h>
#include <Streaming.h>
#include <Adafruit_NeoPixel.h>

class Neopixels {

private:
    const uint8_t pin;

public:
    Neopixels (
		uint8_t _pin
	)
	: pin(_pin)
	{}

	void begin() {
		pinMode(pin, OUTPUT);
	}
};

#endif
