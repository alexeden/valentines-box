#include <Wire.h>
#include <Streaming.h>
#include <Adafruit_MotorShield.h>
#include "Actuator.cc"


Actuator actuator = Actuator(ACT_POT_NEG_PIN, ACT_POT_WIPER_PIN, ACT_POT_POS_PIN, MOTOR_NUM);

// Create the motor shield object with the default I2C address
// Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Select which 'port' M1, M2, M3 or M4. In this case, M1
// Adafruit_DCMotor *motor = AFMS.getMotor(MOTOR_NUM);

void setup() {
	Serial.begin(115200);
	actuator.begin();
}

void loop() {
	actuator.open(50);

	delay(2000);

	actuator.close(50);

	delay(2000);
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
