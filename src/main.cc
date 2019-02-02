#include <Wire.h>
#include <Adafruit_MotorShield.h>
// #include "utility/Adafruit_MS_PWMServoDriver.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *motor = AFMS.getMotor(4);

void setup() {
	Serial.begin(115200); // set up Serial library at 9600 bps
	Serial.println("Adafruit Motorshield v2 - DC Motor test!");

	AFMS.begin(); // create with the default frequency 1.6KHz

	// Set the speed to start, from 0 (off) to 255 (max speed)
	motor->setSpeed(255);
	motor->run(FORWARD);
	// turn on motor
	motor->run(RELEASE);
}

void loop() {
	uint8_t i;

	Serial.print("tick");

	motor->run(FORWARD);
	// for (i = 0; i < 255; i++) {
	// 	motor->setSpeed(i);
	// 	delay(10);
	// }
	// for (i = 255; i != 0; i--) {
	// 	motor->setSpeed(i);
	// 	delay(10);
	// }
	delay(3000);
	Serial.print("tock");

	motor->run(BACKWARD);
	// for (i = 0; i < 255; i++) {
	// 	motor->setSpeed(i);
	// 	delay(10);
	// }
	// for (i = 255; i != 0; i--) {
	// 	motor->setSpeed(i);
	// 	delay(10);
	// }
	delay(3000);
	Serial.print("tech");
	motor->run(RELEASE);
	delay(3000);
}
