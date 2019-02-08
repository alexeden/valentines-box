#include <Adafruit_GFX.h>
#include <Adafruit_MotorShield.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_SSD1306.h>
#include <Streaming.h>
#include <Wire.h>
#include "Actuator.cc"
#include "Ping.cc"
#include "Pixels.cc"

Actuator actuator(
	ACT_POT_NEG_PIN,
	ACT_POT_WIPER_PIN,
	ACT_POT_POS_PIN,
	MOTOR_NUM
);

Adafruit_SSD1306 *display = new Adafruit_SSD1306(128, 32, &Wire);
// Ping *ping = new Ping(PING_PIN);
Pixels *pixels = new Pixels(NEOPIXEL_PIN, 20);

uint8_t open_threshold_inches = 12;
volatile ulong loop_delay = 10;

void increase_delay() {
	loop_delay += loop_delay >= 100 ? 50 : 5;
	// delay(5);
}

void decrease_delay() {
	loop_delay -= loop_delay > 100 ? 50 : 5;
	if (loop_delay <= 0) loop_delay = 0;
	// delay(5);
}

void setup() {
	Serial.begin(115200);
	pinMode(BUTTON_A, INPUT_PULLUP);
	attachInterrupt(BUTTON_A, increase_delay, FALLING);
	pinMode(BUTTON_B, INPUT_PULLUP);
	pinMode(BUTTON_C, INPUT_PULLUP);
	attachInterrupt(BUTTON_C, decrease_delay, FALLING);
	actuator.begin();
	pixels -> begin();
	display -> begin(SSD1306_SWITCHCAPVCC, 0x3C);
	display -> clearDisplay();
	display -> setTextSize(2);      // Normal 1:1 pixel scale
	display -> setTextColor(WHITE); // Draw white text
}

void loop() {
	// if (actuator.is_closed() || actuator.is_closing()) {
	// 	long prox = ping -> read_inches();
	// 	display -> print(prox);

	// 	if (prox > open_threshold_inches) {
	// 		// Make a sound
	// 		// Open
	// 		// Reset close timer
	// 	}
	// }
	pixels -> update();
	pixels -> display();
	display -> clearDisplay();
	display -> setCursor(0, 0);
	display -> print("Delay ");
	display -> println(loop_delay);
	display -> print("Pixel ");
	display -> println(pixels->get_x());
	display -> display();
	delay(loop_delay);
}
