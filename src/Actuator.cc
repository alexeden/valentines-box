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
};

struct Pot {
	uint16_t neg;
	uint16_t wiper;
	uint16_t pos;
};

class Actuator {
private:
	const uint8_t limit_led_pin;
	const uint8_t moving_led_pin;
	const uint8_t stopped_led_pin;
    const uint8_t motor_num;
    const uint8_t neg_pin;
    const uint8_t pos_pin;
    const uint8_t wiper_pin;
	Pot pot;

	Adafruit_MotorShield motor_shield;
	Adafruit_DCMotor *motor;
	MotorState motor_state;

	void set_motor_state(MotorState ms) {
		motor->run(ms);
		motor_state = ms;
	}

public:
    Actuator (
		uint8_t _neg_pin,
		uint8_t _wiper_pin,
		uint8_t _pos_pin,
		uint8_t _stopped_led_pin,
		uint8_t _moving_led_pin,
		uint8_t _limit_led_pin,
		uint8_t _motor_num
    )
	: 	neg_pin(_neg_pin),
		wiper_pin(_wiper_pin),
		pos_pin(_pos_pin),
		motor_num(_motor_num),
		stopped_led_pin(_stopped_led_pin),
		moving_led_pin(_moving_led_pin),
		limit_led_pin(_limit_led_pin),
		motor_shield(Adafruit_MotorShield())
	{
		motor = motor_shield.getMotor(motor_num);
	}

	void begin() {
		motor_shield.begin();
		motor->setSpeed(255);
		pinMode(stopped_led_pin, OUTPUT);
		pinMode(moving_led_pin, OUTPUT);
		pinMode(limit_led_pin, OUTPUT);
		update();
		set_motor_state(STOP);
	}

	void update() {
		pot.neg = analogRead(neg_pin);
		pot.pos = analogRead(pos_pin);

		float sum = 0;
		uint8_t readings = 20;
		for (uint8_t i = 0; i < readings; i++) {
			float value = (float)analogRead(wiper_pin);
			// Serial << value << '\t';
			sum += value;
		}
		// Serial << endl;
		pot.wiper = (uint16_t)(sum / readings);
	}

	// State of actuator motion
	bool is_extending()		{ return motor_state == EXTEND;	 }
	bool is_retracting() 	{ return motor_state == RETRACT; }
	bool is_stopped() 		{ return motor_state == STOP;	 }


	// State of actuator position
	bool is_retracted() { return pot.wiper >= pot.pos; }
	bool is_extended() 	{ return pot.wiper <= pot.neg; 	}

	void retract() {
		update();
		if (is_retracted()) {
			Serial << "Forcing STOP because actuator is fully retracted" << endl;
			set_motor_state(STOP);
		}
		else {
			set_motor_state(RETRACT);
		}
	}

	void extend() {
		update();
		if (is_extended()) {
			Serial << "Forcing STOP because actuator is fully extended" << endl;
			set_motor_state(STOP);
		}
		else {
			set_motor_state(EXTEND);
		}
	}

	void print_pot() {
		Serial << motor_state << '\t' << pot.wiper << '\t' << pot.neg << '\t' << pot.pos << endl;
	}

	uint16_t get_pot_wiper() { return pot.wiper; }
	uint16_t get_pot_pos() { return pot.pos; }
	uint16_t get_pot_neg() { return pot.neg; }
};


#endif
