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

  last_sensor_left = false;
  last_sensor_right = false;
  if (line_left)
    last_sensor_left = true;
  if (line_right)
    last_sensor_right = true;

	switch (mode) {
	case Mode::FolgeLinie:			update_folge_linie(line_left, line_right, MOTOR_FOLGE_LINIE_SPEED); break;
	case Mode::LinksAusweichen:		update_links_ausweichen(line_left, line_right);	break;
	case Mode::RechtsAusweichen:	update_rechts_ausweichen(line_left, line_right); break;
	}  
}

void Linienfolger::update_folge_linie(bool line_left, bool line_right, int speed) {
  double error = 0.0;
  if (line_left)
    error = 1.0;
  else if (line_right)
    error = -1.0;
  if (line_left && line_right)
    error = 0.0;
  
  double pid_output = pid.update(error);
  set_left_motor(speed - pid_output);
  set_right_motor(speed + pid_output);
}

void Linienfolger::update_links_ausweichen(bool line_left, bool line_right) {
	if (line_left) {
    set_left_motor(0);
    set_right_motor(255);//MOTOR_AUSWEICH_SPEED);
	}
  else {
    update_folge_linie(line_left, line_right, MOTOR_FOLGE_LINIE_SPEED);
  }
}

void Linienfolger::update_rechts_ausweichen(bool line_left, bool line_right) {
	if (line_right) {
    set_left_motor(255);//MOTOR_AUSWEICH_SPEED);
    set_right_motor(0);
	}
  else {
    update_folge_linie(line_left, line_right, MOTOR_FOLGE_LINIE_SPEED);
  }
}

void Linienfolger::set_left_motor(int speed) {
  left_motor.set_speed(speed);
  last_motor_left = speed;
}

void Linienfolger::set_right_motor(int speed) {
  right_motor.set_speed(speed);
  last_motor_right = speed;
}
