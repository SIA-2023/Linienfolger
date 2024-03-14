#include "Linienfolger.h"

bool Linienfolger::is_line(int value) {  
  return value > SENSOR_THRESHOLD;
}

void Linienfolger::setup() {
	left_motor.init(PIN_MOTOR_LEFT_IN1, PIN_MOTOR_LEFT_IN2, PIN_MOTOR_LEFT_PWM, true);
	right_motor.init(PIN_MOTOR_RIGHT_IN1, PIN_MOTOR_RIGHT_IN2, PIN_MOTOR_RIGHT_PWM);
}

void Linienfolger::update() {
	bool line_left = is_line(analogRead(PIN_SENSOR_LEFT));
	bool line_right = is_line(analogRead(PIN_SENSOR_RIGHT));

	switch (mode) {
	case Mode::FolgeLinie:			update_folge_linie(line_left, line_right, MOTOR_TOP_SPEED); break;
	case Mode::LinksAusweichen:		update_links_ausweichen(line_left, line_right);	break;
	case Mode::RechtsAusweichen:	update_rechts_ausweichen(line_left, line_right); break;
	}  
}

void Linienfolger::forward(int speed) {
	left_motor.set_speed(speed);
	right_motor.set_speed(speed);
	last_time_left = false;
	last_time_right = false;
}

void Linienfolger::left(int speed) {
	left_motor.set_speed(0);
	right_motor.set_speed(speed);
	last_time_left = true;
	last_time_right = false;
}

void Linienfolger::right(int speed) {
	left_motor.set_speed(speed);
	right_motor.set_speed(0);
	last_time_right = true;
	last_time_left = false;
}

void Linienfolger::update_folge_linie(bool line_left, bool line_right, int speed) {
	if (!line_left && !line_right) {
		if (last_time_left)
			left(speed);
		else if (last_time_right)
			right(speed);
		else
			forward(speed);
		return;
	}


	if (line_left && !line_right)
		left(speed);
	else if (line_right && !line_left)
		right(speed);
	else
		forward(speed);
}

void Linienfolger::update_links_ausweichen(bool line_left, bool line_right) {
	if (line_left)
		left(MOTOR_AUSWEICH_SPEED);
	else
		update_folge_linie(line_left, line_right, MOTOR_AUSWEICH_SPEED);
}

void Linienfolger::update_rechts_ausweichen(bool line_left, bool line_right) {
	if (line_right)
		right(MOTOR_AUSWEICH_SPEED);
	else
		update_folge_linie(line_left, line_right, MOTOR_AUSWEICH_SPEED);
}
