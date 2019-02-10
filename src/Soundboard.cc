#ifndef __Soundboard__
#define __Soundboard__

#include <Streaming.h>

class Soundboard {
private:
	const uint8_t pin;
	const uint8_t channel;

public:
	Soundboard (uint8_t _pin) : pin(_pin) {}
};
#endif
