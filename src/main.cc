#include <Adafruit_GFX.h>
#include <Adafruit_MotorShield.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_SSD1306.h>
#include <Streaming.h>
#include <Wire.h>
#include <iterator>
#include <vector>
#include "Actuator.cc"
#include "Ping.cc"
#include "Pixels.cc"
#include "Soundboard.cc"

Actuator *actuator = new Actuator(ACT_POT_NEG_PIN, ACT_POT_WIPER_PIN, ACT_POT_POS_PIN, MOTOR_NUM);
Adafruit_SSD1306 *display = new Adafruit_SSD1306(128, 32, &Wire);
Ping *ping = new Ping(PING_PIN);
Pixels *pixels = new Pixels(NEOPIXEL_PIN, 20);
Soundboard *soundboard = new Soundboard(SOUND_PIN, SOUND_CHANNEL, SOUND_RESOLUTION);

volatile ulong loop_delay = 10;
void isr_increase_delay();
void isr_decrease_delay();
void open_box();
void display_line(String str);
unsigned long close_timer_mark = millis();

void setup() {
	Serial.begin(115200);
	// pinMode(BUTTON_A, INPUT_PULLUP);
	// attachInterrupt(BUTTON_A, isr_increase_delay, FALLING);
	// pinMode(BUTTON_B, INPUT_PULLUP);
	// pinMode(BUTTON_C, INPUT_PULLUP);
	// attachInterrupt(BUTTON_C, isr_decrease_delay, FALLING);

	actuator->begin();
	// pixels->begin();
	soundboard->begin();
	display->begin(SSD1306_SWITCHCAPVCC, 0x3C);
	display->clearDisplay();
	display->setTextSize(1);
	display->setTextColor(WHITE);
	// while (!actuator->is_extended()) {
	// 	actuator->extend();
	// }

}

void print_sound_freq() {
	display->clearDisplay();
	display->setCursor(0, 0);
	display->println(ledcReadFreq(SOUND_CHANNEL));
	display->display();
}

void loop() {
	actuator->update();
	// // Trigger OPEN
	// if (
	// 	(actuator->is_extended() || actuator->is_extending())
	// 	&& (ping->read_inches() <= PING_THRESHOLD_INCHES)
	// ) {
	// 	Serial << "TRIGGERING OPEN" << endl;
	// 	if (actuator->is_extended()) {
	// 		Serial << "PLAYING SOUND" << endl;
	// 	}

	// 	open_box();
	// }
	// // Trigger CLOSE
	// else if (actuator->is_retracted() && (millis() - close_timer_mark >= CLOSE_TIMER_MS)) {
	// 	Serial << "TRIGGERING CLOSE" << endl;
	// 	actuator->extend();
	// }

	// display->clearDisplay();
	// display->setCursor(0, 0);
	// display->print("Wiper");
	// display->println(actuator->get_wiper());
	// display->print("Extended? ");
	// display->println(actuator->is_extended() ? "Yes" : "No");
	// display->print("Retracted? ");
	// display->println(actuator->is_retracted() ? "Yes" : "No");
	// display->println(ping->read_inches());
	// display->display();

	delay(5);
	// display_line(String(ping->read_inches()));
	// display_line("Retracting...");
	// while (!box_is_open()) {
	// 	open_box();
	// }
	// display_line("done retracting!");
	// delay(1000);

	// display_line("Extending...");
	// while (!box_is_closed()) {
	// 	close_box();
	// }
	// display_line("done extending!");
	// delay(1000);

	// if (actuator->is_closed() || actuator->is_closing()) {
	// 	long prox = ping->read_inches();
	// 	display->print(prox);

	// 	if (prox > PING_THRESHOLD_INCHES) {
	// 		// Make a sound
	// 		// Open
	// 		// Reset close timer
	// 	}
	// }
	// pixels->update();
	// pixels->display();
}

void open_box() {
	Serial << "Opening box" << endl;
	long i = 0;
	while (!actuator->is_retracted()) {
		actuator->retract();

		if (i++ % 100) {
			actuator->print_pot();
		}
	}
	Serial << "Box should be open, setting close timer mark" << endl;
	close_timer_mark = millis();
}

void display_line(String str) {
	display->clearDisplay();
	display->setCursor(0, 0);
	display->println(str);
	display->display();
}

void isr_increase_delay() {
	loop_delay += loop_delay >= 100 ? 50 : 5;
}

void isr_decrease_delay() {
	loop_delay -= loop_delay > 100 ? 50 : 5;
	if (loop_delay <= 0) loop_delay = 0;
}


/*
uint16_t min_wiper_value = 0xFFF;
uint16_t max_wiper_value = 0x000;

void print_pot_pins() {
	auto wiper = analogRead(ACT_POT_WIPER_PIN);
	min_wiper_value = min(wiper, min_wiper_value);
	max_wiper_value = max(wiper, max_wiper_value);

	display->clearDisplay();
	display->setCursor(0, 0);
	display->print(min_wiper_value);
	display->setCursor(64, 0);
	display->println(analogRead(ACT_POT_NEG_PIN));
	display->println(wiper);
	display->print(max_wiper_value);
	display->setCursor(64, display->getCursorY());
	display->println(analogRead(ACT_POT_POS_PIN));
	display->display();
}
*/
