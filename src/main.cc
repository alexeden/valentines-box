#include <Adafruit_GFX.h>
#include <Adafruit_MotorShield.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_SSD1306.h>
#include <Streaming.h>
#include <Wire.h>
#include "Actuator.cc"
#include "Neopixels.cc"

Actuator actuator(
	ACT_POT_NEG_PIN,
	ACT_POT_WIPER_PIN,
	ACT_POT_POS_PIN,
	MOTOR_NUM
);

Adafruit_SSD1306 display(128, 32, &Wire);
Neopixels pixels(NEOPIXEL_PIN);

void setup() {
	Serial.begin(115200);
	actuator.begin();
	display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
	display.clearDisplay();
	display.display();
}

void loop() {
	actuator.open();
	delay(2000);
	actuator.close();
	delay(2000);
}
