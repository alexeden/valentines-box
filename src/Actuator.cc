#ifndef __Actuator__
#define __Actuator__

#include <Wire.h>
#include <Streaming.h>
#include <Adafruit_MotorShield.h>

enum ActuatorState {
	RETRACTED,
	MIDDLE,
	EXTENDED
};

enum MotorState {
	EXTEND = FORWARD,
	RETRACT = BACKWARD,
	STOP = RELEASE

	// OPENING = FORWARD,
	// EXTEND = BACKWARD,
	// STOP = RELEASE
};

class Actuator {
private:
    const uint8_t neg_pin;
    const uint8_t wiper_pin;
    const uint8_t pos_pin;
    const uint8_t motor_num;

	struct {
		uint8_t neg;
		uint8_t wiper;
		uint8_t pos;
	} pot;

	Adafruit_MotorShield motor_shield;
	Adafruit_DCMotor *motor;
	MotorState motor_state;

	void set_motor_state(MotorState ms) {
		motor->run(ms);
		motor_state = ms;
	}

	void update_pot() {
		pot.neg = analogRead(neg_pin);
		pot.wiper = analogRead(wiper_pin);
		pot.pos = analogRead(pos_pin);
	}

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
		motor->setSpeed(255);
		set_motor_state(STOP);
	}

	// State of actuator motion
	bool is_extending()		{ return motor_state == EXTEND;	 }
	bool is_retracting() 	{ return motor_state == RETRACT; }
	bool is_stopped() 		{ return motor_state == STOP;	 }


	// State of actuator position
	bool is_retracted() { return read_state() == RETRACTED; }
	bool is_extended() 	{ return read_state() == EXTENDED; 	}

	void retract() {
		while (!is_retracted()) {
			if (!is_retracting()) {
				set_motor_state(RETRACT);
			}
		}
		set_motor_state(STOP);
	}

	void extend() {
		while (!is_extended()) {
			if (!is_extending()) {
				set_motor_state(EXTEND);
			}
		}
		set_motor_state(STOP);
	}

	ActuatorState read_state() {
		update_pot();

		if (pot.wiper <= pot.neg) {
			return EXTENDED;
		}
		else if (pot.wiper >= pot.pos) {
			return RETRACTED;
		}
		else {
			return MIDDLE;
		}
	}
};


#endif
