#ifndef __Ping__
#define __Ping__

#include <Streaming.h>

static const unsigned long ECHO_PULSE_MIN_US = 115;
static const unsigned long ECHO_PULSE_MAX_US = 18500000;

class Ping {
private:
	const uint8_t pin;
	const unsigned long threshold_inches;
	const unsigned long timeout_us;

public:
	Ping (
		uint8_t _pin,
		unsigned long _threshold_inches
	)
	: 	pin(_pin),
		threshold_inches(_threshold_inches),
		timeout_us(_threshold_inches * 74 * 2)
	{}

	void begin() {
		Serial << "Threshold in inches:\t" << threshold_inches << endl;
		Serial << "Timeout in microseconds:\t" << timeout_us << endl;
		Serial << "Ping ready" << endl;
	}

	unsigned long read_us() {
		pinMode(pin, OUTPUT);
		digitalWrite(pin, LOW);
		delayMicroseconds(2);
		digitalWrite(pin, HIGH);
		delayMicroseconds(5);
		digitalWrite(pin, LOW);
		pinMode(pin, INPUT);
		// Average max 21608
		// Average min 296
		return pulseIn(pin, HIGH, 4 * timeout_us);
	}


	unsigned long read_inches() {
		long reading = read_us();

		if (reading == 0) {
			return 146 * 74 * 2;
		}
		else {
			return reading / 74 / 2;
		}
	}
};
#endif
