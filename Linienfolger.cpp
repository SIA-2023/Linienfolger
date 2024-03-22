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

void Linienfolger::update_folge_linie(bool line_left, bool line_right, int speed) {
	/*if (!line_left && !line_right) {
		if (last_time_left) {
      left_motor.set_speed(0);
      right_motor.set_speed(speed);
		}
		else if (last_time_right) {
      left_motor.set_speed(speed);
      right_motor.set_speed(0);
		}
		else {
      left_motor.set_speed(speed);
      right_motor.set_speed(speed);
		}
		return;
	}*/

  last_time_left = false;
  last_time_right = false;
  if (line_left)
    last_time_left = true;
  if (line_right)
    last_time_right = true;

  double error = 0.0;
  if (line_left)
    error = 1.0;
  else if (line_right)
    error = -1.0;
  
  double pid_output = pid.update(error);
  left_motor.set_speed(180 - pid_output);
  right_motor.set_speed(180 + pid_output);
	/*if (line_left && !line_right)
		left(speed);
	else if (line_right && !line_left)
		right(speed);
	else
		forward(speed);*/
}

void Linienfolger::update_links_ausweichen(bool line_left, bool line_right) {
	if (line_left) {
    left_motor.set_speed(0);
    right_motor.set_speed(MOTOR_AUSWEICH_SPEED);
	}
	else
		update_folge_linie(line_left, line_right, MOTOR_AUSWEICH_SPEED);
}

void Linienfolger::update_rechts_ausweichen(bool line_left, bool line_right) {
	if (line_right) {
    left_motor.set_speed(MOTOR_AUSWEICH_SPEED);
    right_motor.set_speed(0);
	}
	else
		update_folge_linie(line_left, line_right, MOTOR_AUSWEICH_SPEED);
}
