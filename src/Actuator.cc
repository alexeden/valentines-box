#ifndef __Actuator__
#define __Actuator__

#include <Wire.h>
#include <Streaming.h>
#include <Adafruit_MotorShield.h>

enum OpenState {
	OPEN,
	MID,
	CLOSED
};

enum MotionState {
	OPENING = FORWARD,
	CLOSING = BACKWARD,
	IDLE = RELEASE
};

class Actuator {
private:
    const uint8_t neg_pin;
    const uint8_t wiper_pin;
    const uint8_t pos_pin;
    const uint8_t motor_num;

	Adafruit_MotorShield motor_shield;
	Adafruit_DCMotor *motor;
	MotionState motion_state;

	void set_motion_state(MotionState ms) {
		motor->run(ms);
		motion_state = ms;
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
		set_motion_state(IDLE);
	}

	bool is_opening() {
		return motion_state == OPENING;
	}

	bool is_closing() {
		return motion_state == CLOSING;
	}

	bool is_idle() {
		return motion_state == IDLE;
	}

	bool is_open() {
		return get_open_state() == OPEN;
	}

	bool is_closed() {
		return get_open_state() == CLOSED;
	}

	void open(uint16_t t = 10) {
		Serial << "OPENING!!!!!" << endl;

		while (!is_open()) {
			if (!is_opening()) {
				set_motion_state(OPENING);
			}
			// delay(t);
			yield();
		}
		set_motion_state(IDLE);
		Serial << "DONE OPENING!!!!!" << endl;
	}

	void close(uint16_t t = 10) {
		while (!is_closed()) {
			if (!is_closing()) {
				set_motion_state(CLOSING);
			}
			delay(t);
		}
		set_motion_state(IDLE);
	}

	float get_open_ratio() {
		uint16_t neg_rail = analogRead(neg_pin);
		uint16_t wiper = analogRead(wiper_pin);
		uint16_t pos_rail = analogRead(pos_pin);

		return ((float)wiper - (float)neg_rail) / ((float)pos_rail - (float)neg_rail);
	}

	OpenState get_open_state() {
		uint16_t neg_rail = analogRead(neg_pin);
		uint16_t wiper = analogRead(wiper_pin);
		uint16_t pos_rail = analogRead(pos_pin);

		// Serial << "get_open_state values: " << neg_rail << "\t" << wiper << "\t" << pos_rail << endl;

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
};


#endif
