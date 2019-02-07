#include <Adafruit_GFX.h>
#include <Adafruit_MotorShield.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_SSD1306.h>
#include <Streaming.h>
#include <Wire.h>
// #include <driver/touch_pad.h>
#include "Actuator.cc"
#include "CapacitiveSensor.h"
#include "Ping.cc"
#include "Pixels.cc"

Actuator actuator(
	ACT_POT_NEG_PIN,
	ACT_POT_WIPER_PIN,
	ACT_POT_POS_PIN,
	MOTOR_NUM
);

Adafruit_SSD1306 *display = new Adafruit_SSD1306(128, 32, &Wire);

CapacitiveSensor touch_sense = CapacitiveSensor(CAP_SEND_PIN, CAP_RECV_PIN);
uint16_t touch_samples = 30;

// Pixels *pixels = new Pixels(NEOPIXEL_PIN, 20);

void setup() {
	Serial.begin(115200);
	pinMode(BUTTON_A, INPUT_PULLUP);
	pinMode(BUTTON_B, INPUT_PULLUP);
	pinMode(BUTTON_C, INPUT_PULLUP);
	actuator.begin();
	// pixels -> begin();
	touch_sense.reset_CS_AutoCal();
	display -> begin(SSD1306_SWITCHCAPVCC, 0x3C);
	display -> clearDisplay();
	display -> setTextSize(2);      // Normal 1:1 pixel scale
	display -> setTextColor(WHITE); // Draw white text
}

void loop() {
	if(!digitalRead(BUTTON_A)) {
		touch_samples++;
		delay(100);
	}
	else if (!digitalRead(BUTTON_C)) {
		touch_samples -= touch_samples > 0 ? 1 : 0;
		delay(100);
	}

	long touch_value = touch_sense.capacitiveSensor(touch_samples);
	// pixels -> update();
	// pixels -> display();
	display -> clearDisplay();
	display -> setCursor(0, 0);
	display -> println(touch_samples);
	display -> println(touch_value);
	// display -> println(pixels->get_x());
	display -> display();
	delay(10);
}
