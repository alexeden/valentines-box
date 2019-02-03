#ifndef __Ping__
#define __Ping__

#include <Wire.h>
#include <Streaming.h>


class Ping {
private:
	const uint8_t pin;

	long read() {
		pinMode(pin, OUTPUT);
		digitalWrite(pin, LOW);
		delayMicroseconds(2);
		digitalWrite(pin, HIGH);
		delayMicroseconds(5);
		digitalWrite(pin, LOW);
		pinMode(pin, INPUT);
		return pulseIn(pin, HIGH);
	}
public:
	Ping (uint8_t _pin) : pin(_pin) {}

	long read_inches() {
		return read() / 74 / 2;
	}
};
#endif
