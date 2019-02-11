#ifndef __Ping__
#define __Ping__

#include <Streaming.h>

class Ping {
private:
	const uint8_t pin;

	unsigned long read() {
		pinMode(pin, OUTPUT);
		digitalWrite(pin, LOW);
		delayMicroseconds(2);
		digitalWrite(pin, HIGH);
		delayMicroseconds(5);
		digitalWrite(pin, LOW);
		pinMode(pin, INPUT);
		// Average max 21608
		// Average min 296
		return pulseIn(pin, HIGH, 10000);
	}


public:
	Ping (uint8_t _pin) : pin(_pin) {}

	unsigned long read_inches() {
		long reading = read();

		if (reading == 0) {
			return 146 * 74 * 2;
		}
		else {
			return reading / 74 / 2;
		}
	}
};
#endif
