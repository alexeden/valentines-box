#ifndef __PixelBus__
#define __PixelBus__

#include <Streaming.h>
#include <NeoPixelBus.h>

static const RgbColor PINK(0xFF, 0x10, 0x19);
static const RgbColor GOLD(255, 170, 10);

class PixelBus {

private:
    const uint8_t PIN, N;
	const float DECAY;
	NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> *strip;
	float x;
	float v;
	RgbColor *pixels;
	uint32_t disp_mark;

	void rotate() {
		while (x <= 0) x += N;
		while (x >= N) x -= N;
	}

	void apply_decay(RgbColor &color) {
		color.R = uint8_t(float(color.R) * DECAY);
		color.G = uint8_t(float(color.G) * DECAY);
		color.B = uint8_t(float(color.B) * DECAY);
	}

public:
    PixelBus (
		uint8_t _pin,
		uint8_t _n,
		float _decay
	)
	: 	PIN(_pin),
		N(_n),
		DECAY(_decay),
		strip(new NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod>(_n, _pin)),
		x(0.0),
		v(0.4)
	{}

	void begin() {
		pinMode(PIN, OUTPUT);
		strip->Begin();
		strip->Show();
		pixels = new RgbColor[N];
		clear_pixels();
		disp_mark = micros();
		Serial << "PixelBus ready" << endl;
	}

	void clear_pixels() {
		for (int i = 0; i < N; i++) {
			pixels[i] = RgbColor(0, 0, 0);
		}
	}

	void update() {
		x += v;
		if (x > N || x < 0) {
			v *= -1;
		}
	}

	int8_t get_x() {
		return (int)x;
	}

	void all_on(const RgbColor& color) {
		for (int i = 0; i < N; i++) {
			strip->SetPixelColor(i, color);
		}
		strip->Show();
	}

	float get_velocity() {
		return v;
	}

	void display(const RgbColor& color) {
		pixels[(int)x] = color;

		for (int i = 0; i < N; i++) {
			if (i == int(x)) {
				strip->SetPixelColor(i, pixels[i]);
			}
			else {
				apply_decay(pixels[i]);
				strip->SetPixelColor(i, pixels[i]);
			}
		}
		strip->Show();
		disp_mark = micros();
	}

};

#endif
