#include <Adafruit_GFX.h>
#include <Adafruit_MotorShield.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_SSD1306.h>
#include <Streaming.h>
#include <Wire.h>
#include "Actuator.cc"
#include "Pixels.cc"

Actuator actuator(
	ACT_POT_NEG_PIN,
	ACT_POT_WIPER_PIN,
	ACT_POT_POS_PIN,
	MOTOR_NUM
);

Adafruit_SSD1306 *display = new Adafruit_SSD1306(128, 32, &Wire);
Pixels *pixels = new Pixels(NEOPIXEL_PIN, 20);

void setup() {
	Serial.begin(115200);
	actuator.begin();
	pixels -> begin();
	display -> begin(SSD1306_SWITCHCAPVCC, 0x3C);
	display -> clearDisplay();
	display -> setTextSize(2);      // Normal 1:1 pixel scale
	display -> setTextColor(WHITE); // Draw white text
	// display -> setCursor(0, 0);     // Start at top-left corner
	// display -> cp437(true);         // Use full 256 char 'Code Page 437' font
	// display -> println("HIIIIIII");
	// display -> display();
}

int i = 0;

void loop() {
	pixels -> update();
	pixels -> display();
	display -> clearDisplay();
	display -> setCursor(0, 0);
	// display -> println(++i);
	display -> println(pixels->get_x());
	display -> display();
	delay(10);
	// // actuator.open();
	// delay(2000);
	// actuator.close();
	// delay(2000);
}
