#ifndef __Soundboard__
#define __Soundboard__

#include <Streaming.h>
#include <iterator> // for iterators
#include <vector> // for vectors
#include <array>

static const std::vector<note_t> NOTES = {
	// Note			Octave 4	Octave 5
	NOTE_C, 	// 	261.63		523.26
	NOTE_Cs, 	// 	277.19		554.39
	NOTE_D, 	// 	293.69		587.39
	NOTE_Eb, 	// 	311.13		622.26
	NOTE_E, 	// 	329.63		659.26
	NOTE_F, 	// 	349.25		698.52
	NOTE_Fs, 	// 	370.00		740.00
	NOTE_G, 	// 	392.00		784.01
	NOTE_Gs, 	// 	415.32		830.63
	NOTE_A, 	// 	440.01		880.01
	NOTE_Bb, 	// 	466.19		932.40
	NOTE_B,		// 	493.88		987.75
	NOTE_MAX
};

// using TuneSegment = std::tuple<note_t, unsigned double>;

// static const PROGMEM uint tada[][2] = {
static const std::vector<std::array<uint, 2>> tada = {
	{ NOTE_C, 100 },
	{ NOTE_Cs, 225 },
	{ NOTE_Eb, 100 },
	{ NOTE_E, 225 },
	{ NOTE_Bb, 100 },
	{ NOTE_B, 350 }
};

class Soundboard {
private:
public:
	const long freq;
	const uint8_t channel;
	const uint8_t octave;
	const uint8_t pin;
	const uint8_t resolution;

	Soundboard (
		uint8_t _pin,
		uint8_t _octave,
		uint8_t _channel = 0,
		uint8_t _resolution = 16,
		long _freq = 1E6
	)
	: 	pin(_pin),
		channel(_channel),
		freq(_freq),
		octave(_octave),
		resolution(_resolution)
	{}

	void begin() {
		ledcSetup(channel, freq, resolution);
		ledcAttachPin(pin, channel);
	}

	double play_note(uint note) {
		return ledcWriteNote(channel, (note_t)note, octave);
	}

	void mute() {
		ledcWriteTone(channel, 0);

	}

	void play_tada() {
		for (auto seg = tada.begin(); seg < tada.end(); seg++) {
			play_note((*seg)[0]);
			delay((*seg)[1]);
		}
		mute();
	}
};
#endif
