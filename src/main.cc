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
Ping *ping = new Ping(PING_PIN);
// Pixels *pixels = new Pixels(NEOPIXEL_PIN, 20);

void setup() {
	Serial.begin(115200);
	pinMode(BUTTON_A, INPUT_PULLUP);
	pinMode(BUTTON_B, INPUT_PULLUP);
	pinMode(BUTTON_C, INPUT_PULLUP);
	actuator.begin();
	// pixels -> begin();
	display -> begin(SSD1306_SWITCHCAPVCC, 0x3C);
	display -> clearDisplay();
	display -> setTextSize(2);      // Normal 1:1 pixel scale
	display -> setTextColor(WHITE); // Draw white text
}

void loop() {
	long prox = ping -> read_inches();
	// pixels -> update();
	// pixels -> display();
	display -> clearDisplay();
	display -> setCursor(0, 0);
	display -> println("Proximity");
	display -> print(prox);
	display -> println("\"");
	// display -> println(pixels->get_x());
	display -> display();
	delay(100);
}
