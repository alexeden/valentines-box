#include <Wire.h>
#include <Adafruit_MotorShield.h>

static const uint8_t POT_NEG 	= A2; // orange
static const uint8_t POT_WIPER 	= A3; // purple
static const uint8_t POT_POS 	= A4; // yellow
static const uint8_t MOTOR		= 4;


// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *motor = AFMS.getMotor(MOTOR);

void setup() {
	Serial.begin(115200);

	// AFMS.begin();

	// Set the speed to start, from 0 (off) to 255 (max speed)
	// motor->setSpeed(255);
	// motor->run(FORWARD);
	// turn on motor
	// motor->run(RELEASE);
}

// uint16_t wiper = 0x00;

void loop() {
	uint16_t neg_rail = analogRead(POT_NEG);
	uint16_t wiper = analogRead(POT_WIPER);
	uint16_t pos_rail = analogRead(POT_POS);

	float ratio = ((float)wiper - (float)neg_rail) / ((float)pos_rail - (float)neg_rail);
	// wiper = analogRead(A2);

	Serial.print("ratio: ");
	Serial.println(ratio);
	// Serial.print("\ta2: ");
	// Serial.print(a2);
	// Serial.print("\ta3: ");
	// Serial.print(a3);
	// Serial.print("\ta4: ");
	// Serial.println(a4);

	// Serial.println(wiper);

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
