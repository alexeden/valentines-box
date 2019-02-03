#include <Wire.h>
#include <Streaming.h>
#include <Adafruit_MotorShield.h>
#include "Actuator.cc"

static const uint8_t POT_NEG 	= A2; // orange
static const uint8_t POT_WIPER 	= A3; // purple
static const uint8_t POT_POS 	= A4; // yellow
static const uint8_t MOTOR		= 4;


enum OpenState {
	OPEN,
	MID,
	CLOSED
};

Actuator actuator = Actuator(ACT_POT_NEG_PIN, ACT_POT_WIPER_PIN, ACT_POT_POS_PIN, MOTOR_NUM);

// Create the motor shield object with the default I2C address
// Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Select which 'port' M1, M2, M3 or M4. In this case, M1
// Adafruit_DCMotor *motor = AFMS.getMotor(MOTOR_NUM);

float get_open_ratio(uint8_t neg_pin, uint8_t wiper_pin, uint8_t pos_pin);
OpenState get_open_state(uint8_t neg_pin, uint8_t wiper_pin, uint8_t pos_pin);


void setup() {
	Serial.begin(115200);

	// AFMS.begin();
	actuator.begin();
	// // Set the speed to start, from 0 (off) to 255 (max speed)
	// motor->setSpeed(255);
	// // turn on motor
	// motor->run(RELEASE);
}

void loop() {
	float ratio = get_open_ratio(POT_NEG, POT_WIPER, POT_POS);

	Serial.print("ratio: ");
	Serial.println(ratio);


	// Serial.print("tick");

	// motor->run(FORWARD);
	// for (i = 0; i < 255; i++) {
	// 	motor->setSpeed(i);
	// 	delay(10);
	// }
	// for (i = 255; i != 0; i--) {
	// 	motor->setSpeed(i);
	// 	delay(10);
	// }
	delay(500);
	// Serial.print("tock");

	// motor->run(BACKWARD);
	// for (i = 0; i < 255; i++) {
	// 	motor->setSpeed(i);
	// 	delay(10);
	// }
	// for (i = 255; i != 0; i--) {
	// 	motor->setSpeed(i);
	// 	delay(10);
	// }
	// delay(3000);
	// Serial.print("tech");
	// motor->run(RELEASE);
	// delay(3000);
}

float get_open_ratio(
	uint8_t neg_pin,
	uint8_t wiper_pin,
	uint8_t pos_pin
) {
	uint16_t neg_rail = analogRead(neg_pin);
	uint16_t wiper = analogRead(wiper_pin);
	uint16_t pos_rail = analogRead(pos_pin);

	return ((float)wiper - (float)neg_rail) / ((float)pos_rail - (float)neg_rail);
}

OpenState get_open_state(
	uint8_t neg_pin,
	uint8_t wiper_pin,
	uint8_t pos_pin
) {
	uint16_t neg_rail = analogRead(neg_pin);
	uint16_t wiper = analogRead(wiper_pin);
	uint16_t pos_rail = analogRead(pos_pin);

	if (wiper <= neg_rail) {
		return CLOSED;
	}
	else if (wiper >= pos_rail) {
		return OPEN;
	}
	else {
		return MID;
	}
}
