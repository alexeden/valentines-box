#ifndef __Soundboard__
#define __Soundboard__

#include <Streaming.h>
#include <iterator>
#include <vector>
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
	NOTE_MAX	// 	MUTE
};

using Tune = std::vector<std::array<uint, 3>>;

static const Tune tada = {
	{ NOTE_C, 75, 5 },
	{ NOTE_Cs, 200, 5 },
	{ NOTE_Eb, 75, 5 },
	{ NOTE_E, 200, 5 },
	{ NOTE_Bb, 75, 5 },
	{ NOTE_B, 325, 5 }
};

static const Tune tada_reverse = {
	{ NOTE_B, 325, 5 },
	{ NOTE_Bb, 75, 5 },
	{ NOTE_E, 200, 5 },
	{ NOTE_Eb, 75, 5 },
	{ NOTE_Cs, 200, 5 },
	{ NOTE_C, 75, 5 }
};

static const Tune chirp = {
	{ NOTE_A, 100, 6 },
	{ NOTE_MAX, 25, 6 },
	{ NOTE_A, 100, 6 },
	{ NOTE_MAX, 25, 6 },
	{ NOTE_A, 100, 6 }
};


class Soundboard {
private:
public:
	const uint8_t pin;
	const uint8_t channel;
	const uint8_t resolution;
	const long freq;

	Soundboard (
		uint8_t _pin,
		uint8_t _channel = 0,
		uint8_t _resolution = 16,
		long _freq = 1E6
	)
	: 	pin(_pin),
		channel(_channel),
		resolution(_resolution),
		freq(_freq)
	{}

	void begin() {
		ledcSetup(channel, freq, resolution);
		ledcAttachPin(pin, channel);
		Serial << "Soundboard ready" << endl;
	}

	double play_note(uint note, uint8_t oct = 5) {
		return ledcWriteNote(channel, (note_t)note, oct);
	}

	void mute() {
		ledcWriteTone(channel, 0);
	}

	void play_tune(const Tune& tune) {
		for (auto seg = tune.begin(); seg < tune.end(); seg++) {
			auto note = (*seg)[0];
			auto octave = (*seg)[2];
			if (note == NOTE_MAX) {
				mute();
			}
			else {
				play_note(note, octave);
			}
			delay((*seg)[1]);
		}
		mute();
	}
};
#endif
