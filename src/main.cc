#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Streaming.h>
#include <iterator>
#include <vector>
#include "Actuator.cc"
#include "Ping.cc"
#include "PixelBus.cc"
#include "Soundboard.cc"

Actuator *actuator = new Actuator(
	ACT_ADC_CS_PIN,
	ACT_WIPER_ADC_CHANNEL,
	ACT_POT_POS_ADC_CHANNEL,
	ACT_POT_NEG_ADC_CHANNEL,
	ACT_MOVING_LED_PIN,
	ACT_LIMIT_LED_PIN,
	MOTOR_NUM
);

Adafruit_SSD1306 *display = new Adafruit_SSD1306(128, 32, &Wire);

Ping *ping = new Ping(PING_PIN, PING_THRESHOLD_INCHES);

PixelBus *pixels = new PixelBus(NEOPIXEL_PIN, 20, 0.8);

Soundboard *soundboard = new Soundboard(SOUND_PIN, SOUND_CHANNEL, SOUND_RESOLUTION);

volatile ulong loop_delay = 10;
void isr_increase_delay();
void isr_decrease_delay();
void open_box();
void display_line(String str);
unsigned long close_timer_mark = millis();

void isr_a() { }
void isr_c() { }

void setup() {
	Serial.begin(115200);
	Serial << "Begin setup()" << endl;
	actuator->begin();
	display->begin(SSD1306_SWITCHCAPVCC, 0x3C);
	ping->begin();
	pixels->begin();
	soundboard->begin();
	display->clearDisplay();
	display->setTextSize(1);
	display->setTextColor(WHITE);
	soundboard->play_tune(chirp);
	Serial << "Extending actuator" << endl;
	while (!actuator->is_extended()) {
		actuator->extend();
	}
	soundboard->play_tune(chirp);
	Serial << "End setup()" << endl;
}


void loop() {
	actuator->update();

	// Trigger OPEN
	if (
		(actuator->is_extended() || actuator->is_extending())
		&& (ping->read_inches() <= PING_THRESHOLD_INCHES)
	) {
		pixels->all_on(GOLD);

		if (actuator->is_extended()) {
			soundboard->play_tune(tada);
		}
		else {
			soundboard->play_tune(chirp);
		}
		open_box();
	}
	// Trigger CLOSE
	else if (
		actuator->is_retracted()
		&& (millis() - close_timer_mark >= CLOSE_TIMER_MS)
		&& (ping->read_inches() > PING_THRESHOLD_INCHES)
	) {
		pixels->all_on(PINK);
		soundboard->play_tune(tada_reverse);
		actuator->extend();
		delay(500);
	}
	// All pixels on when in motion
	else if (actuator->is_extending() || actuator->is_retracting()) {
		pixels->all_on(actuator->is_extending() ? PINK : GOLD);
	}
	else {
		pixels->update();
		pixels->display(pixels->get_velocity() <= 0 ? GOLD : PINK);
			// actuator->is_retracted() ? GOLD : PINK);
	}

	display->clearDisplay();
	display->setCursor(0, 0);
	display->print("(-) ");
	display->print(actuator->get_pot_neg());
	display->print(" (+) ");
	display->println(actuator->get_pot_pos());
	display->print("(=) ");
	display->println(actuator->get_pot_wiper());
	if (actuator->is_extended()) {
		display->println("EXTENDED");
	}
	else if (actuator->is_retracted()) {
		display->println("RETRACTED");
	}
	else {
		display->println("---");
	}

	display->display();
	delay(2);
}

void open_box() {
	Serial << "Opening box" << endl;
	// long i = 0;
	while (!actuator->is_retracted()) {
		actuator->retract();

		// if (i++ % 100) {
		// 	actuator->print_pot();
		// }
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

pinMode(BUTTON_A, INPUT_PULLUP);
attachInterrupt(BUTTON_A, isr_a, FALLING);
pinMode(BUTTON_C, INPUT_PULLUP);
attachInterrupt(BUTTON_C, isr_c, FALLING);

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
