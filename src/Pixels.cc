#ifndef __Pixels__
#define __Pixels__

#include <Wire.h>
#include <Streaming.h>
#include <Adafruit_NeoPixel.h>

class Pixels {

private:
	const float DEGRADE = 0.8;
    const uint8_t PIN, N;
	Adafruit_NeoPixel *strip;
	float x;
	float v;
	uint32_t *pixels;
	uint32_t disp_mark;

	void rotate() {
		while (x <= 0) {
			x += N;
		}
		while (x >= N) {
			x -= N;
		}
	}

	void reverse() {
		if (x > N || x < 0) {
			v *= -1;
		}
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
    Pixels (uint8_t _pin, uint8_t _n)
	: 	PIN(_pin),
		N(_n),
		strip(new Adafruit_NeoPixel(_n, _pin, NEO_GRB + NEO_KHZ800)),
		x(0.0),
		v(0.4)
	{}

	void begin() {
		pinMode(PIN, OUTPUT);
		strip -> begin();
		strip -> show();
		pixels = new uint32_t[N];
		clear_pixels();
		disp_mark = micros();
	}

	void clear_pixels() {
		for (int i = 0; i < N; i++) {
			pixels[i] = 0x00000000;
		}
	}

	// void set_speed(u)

	void update() {
		// pull = p;
		// if(pull < 0) {
		// 	min_pull = min(min_pull, sqrt(pull));
		// }
		// else if(pull > 0) {
		// 	max_pull = max(max_pull, sqrt(pull));
		// }
		// pull_force += p;
		// // Degrade the pull force
		// if(pull == 0) pull_force *= 0.1;
		// float net = 0;
		// float drag = abs(v);
		// drag *= v > 0 ? -1 : 1;
		// net += drag;
		// net += pull_force;
		// net /= MASS;
		// a = net;
		// v = 100;
		x += v;
		reverse();
	}

	int8_t get_x() {
		return (int)x;
	}

	void display() {
		uint32_t bgr = 0x00ff1019;

		pixels[(int)x] = bgr;
		for (int i = 0; i < N; i++) {
			if (i == int(x)) {
				strip -> setPixelColor(i, pixels[i]);
			}
			else {
				degrade(pixels[i]);
				strip -> setPixelColor(i, pixels[i]);
			}
		}
		strip -> show();

		disp_mark = micros();
	}

};

#endif
