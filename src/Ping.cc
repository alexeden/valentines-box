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

	long _last_inches;

public:
	Ping (uint8_t _pin) : pin(_pin), _last_inches(0) {}

	long read_inches() {
		long inches = read() / 74 / 2;
		_last_inches = inches;
		return inches;
	}

	long last_inches() {
		return _last_inches;
	}
};
#endif
