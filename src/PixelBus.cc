#ifndef __PixelBus__
#define __PixelBus__

#include <Streaming.h>
#include <NeoPixelBus.h>

class PixelBus {

private:
	const float DEGRADE = 0.8;
    const uint8_t PIN, N;
	NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> *strip;
	float x;
	float v;
	uint32_t *pixels;
	uint32_t disp_mark;

	void rotate() {
		while (x <= 0) x += N;
		while (x >= N) x -= N;
	}

	void degrade(uint32_t &pixel) {
		pixel = (
			0x00 << 24 |
			uint32_t(float(pixel >> 16 & 0xFF) * DEGRADE) << 16 |
			uint32_t(float(pixel >> 8 & 0xFF) * DEGRADE) << 8 |
			uint32_t(float(pixel & 0xFF) * DEGRADE)
		);
	}

public:
    PixelBus (uint8_t _pin, uint8_t _n)
	: 	PIN(_pin),
		N(_n),
		strip(new NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod>(_n, _pin)),
		x(0.0),
		v(0.4)
	{}

	void begin() {
		pinMode(PIN, OUTPUT);
		strip->Begin();
		strip->Show();
		pixels = new uint32_t[N];
		clear_pixels();
		disp_mark = micros();
		Serial << "PixelBus ready" << endl;
	}

	void clear_pixels() {
		for (int i = 0; i < N; i++) {
			pixels[i] = 0x00000000;
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

	void all_on() {
		uint32_t bgr = 0x00ff1019;
		for (int i = 0; i < N; i++) {
			strip->SetPixelColor(i, bgr);
		}
		strip->Show();
	}

	void display() {
		uint32_t bgr = 0x00ff1019;


		pixels[(int)x] = bgr;
		for (int i = 0; i < N; i++) {
			if (i == int(x)) {
				RgbColor c(pixels[i] >> 16 & 0xFF, pixels[i] >> 8 & 0xFF, pixels[i] & 0xFF);
				strip->SetPixelColor(i, c);
			}
			else {
				degrade(pixels[i]);
				RgbColor c(pixels[i] >> 16 & 0xFF, pixels[i] >> 8 & 0xFF, pixels[i] & 0xFF);
				strip->SetPixelColor(i, c);
			}
		}
		strip->Show();
		disp_mark = micros();
	}

};

#endif
