#ifndef __Actuator__
#define __Actuator__

#include <Wire.h>
#include <Streaming.h>
#include <Adafruit_MCP3008.h>
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
	int neg;
	int wiper;
	int pos;
};

class Actuator {
private:
    // const uint8_t neg_pin;
    // const uint8_t wiper_pin;
    // const uint8_t pos_pin;
    const uint8_t adc_cs_pin;
    const uint8_t adc_wiper_channel;
    const uint8_t adc_pot_pos_channel;
    const uint8_t adc_pot_neg_channel;
	const uint8_t moving_led_pin;
	const uint8_t limit_led_pin;
    const uint8_t motor_num;

	Pot pot;
	Adafruit_MCP3008 adc;
	Adafruit_MotorShield motor_shield;
	Adafruit_DCMotor *motor;
	MotorState motor_state;

	void set_motor_state(MotorState ms) {
		if (ms != motor_state) {
			motor->run(ms);
			motor_state = ms;

			switch (ms) {
				case EXTEND:
				case RETRACT: {
					digitalWrite(moving_led_pin, HIGH);
					break;
				}
				case STOP: {
					digitalWrite(moving_led_pin, LOW);
					break;
				}
			}
		}
	}

public:
    Actuator(
		uint8_t _adc_cs_pin,
		uint8_t _adc_wiper_channel,
		uint8_t _adc_pot_pos_channel,
		uint8_t _adc_pot_neg_channel,
		uint8_t _moving_led_pin,
		uint8_t _limit_led_pin,
		uint8_t _motor_num
    )
	: 	adc_cs_pin(_adc_cs_pin),
		adc_wiper_channel(_adc_wiper_channel),
		adc_pot_pos_channel(_adc_pot_pos_channel),
		adc_pot_neg_channel(_adc_pot_neg_channel),
		moving_led_pin(_moving_led_pin),
		limit_led_pin(_limit_led_pin),
		motor_num(_motor_num),
		motor_shield(Adafruit_MotorShield())
	{
		motor = motor_shield.getMotor(motor_num);
	}

	void begin() {
		adc.begin(adc_cs_pin);
		motor_shield.begin();
		motor->setSpeed(255);
		pinMode(moving_led_pin, OUTPUT);
		pinMode(limit_led_pin, OUTPUT);
		digitalWrite(moving_led_pin, LOW);
		digitalWrite(limit_led_pin, LOW);
		// update();
		set_motor_state(STOP);
		Serial << "Actuator ready" << endl;
	}

	void update() {
		int pos, neg, wiper;

		while (true) {
			pos = adc.readADC(adc_pot_pos_channel);
			neg = adc.readADC(adc_pot_neg_channel);
			wiper = adc.readADC(adc_wiper_channel);
			// print_pot();
			if (wiper <= pos && wiper >= neg) break;
			// if (neg <= 10 && pos >= 1021 && wiper <= pos && wiper >= neg) break;
		}

		pot.pos = pos;
		pot.neg = neg;
		pot.wiper = wiper;

		if (is_retracting() && is_retracted()) {
			Serial << "Forcing STOP because actuator is fully retracted" << endl;
			set_motor_state(STOP);
		}
		else if (is_extending() && is_extended()) {
			Serial << "Forcing STOP because actuator is fully extended" << endl;
			set_motor_state(STOP);
		}

		// Update the limit pin
		digitalWrite(limit_led_pin, is_retracted() || is_extended() ? HIGH : LOW);
	}

	// State of actuator motion
	bool is_extending()	 { return motor_state == EXTEND;	}
	bool is_retracting() { return motor_state == RETRACT; 	}
	bool is_stopped()    { return motor_state == STOP;	 	}


	// State of actuator position
	bool is_retracted() { return pot.wiper >= pot.pos - 10; }
	bool is_extended() 	{ return pot.wiper <= pot.neg + 5;	}

	void retract() {
		update();
		set_motor_state(RETRACT);
	}

	void extend() {
		update();
		set_motor_state(EXTEND);
	}

	void print_pot() {
		Serial << motor_state << '\t' << pot.wiper << '\t' << pot.neg << '\t' << pot.pos << endl;
	}

	int get_pot_wiper() { return pot.wiper; }
	int get_pot_pos() { return pot.pos; }
	int get_pot_neg() { return pot.neg; }
};


#endif
