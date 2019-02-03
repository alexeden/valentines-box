#include <Adafruit_MotorShield.h>
#include <Streaming.h>
#include <Wire.h>
#include "Actuator.cc"
#include "Ping.cc"

Actuator actuator(
	ACT_POT_NEG_PIN,
	ACT_POT_WIPER_PIN,
	ACT_POT_POS_PIN,
	MOTOR_NUM
);

Ping ping(PING_PIN);

void setup() {
	Serial.begin(115200);
	actuator.begin();
}

void loop() {
	actuator.open();
	delay(2000);
	actuator.close();
	delay(2000);
}
