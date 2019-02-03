#ifndef __Actuator__
#define __Actuator__

#include <Wire.h>
#include <Adafruit_MotorShield.h>

class Actuator {
private:
    const uint8_t neg_pin;
    const uint8_t wiper_pin;
    const uint8_t pos_pin;
    const uint8_t motor_num;

	Adafruit_MotorShield motor_shield;
	Adafruit_DCMotor *motor;

public:
    Actuator (
		uint8_t _neg_pin,
		uint8_t _wiper_pin,
		uint8_t _pos_pin,
		uint8_t _motor_num
    )
	: 	neg_pin(_neg_pin),
		wiper_pin(_wiper_pin),
		pos_pin(_pos_pin),
		motor_num(_motor_num),
		motor_shield(Adafruit_MotorShield())
	{
		motor = motor_shield.getMotor(motor_num);
	}


	void begin() {
		motor_shield.begin();

		// Set the speed to start, from 0 (off) to 255 (max speed)
		motor->setSpeed(255);
		// turn on motor
		motor->run(RELEASE);
	}
};


#endif
