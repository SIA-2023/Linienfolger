// Author: Peter Hennig

#pragma once

enum class MotorDirection {
  Forward,
  Backward
};

class Motor {
public:
  Motor() {}

  void init(int in1, int in2, int pwm, bool builtin_reverse = false) {
	m_In1 = in1;
	m_In2 = in2;
	m_PWM = pwm;
	m_BuiltinReverse = builtin_reverse;

	pinMode(m_PWM, OUTPUT);
	pinMode(m_In1, OUTPUT);
	pinMode(m_In2, OUTPUT);

	set_direction(MotorDirection::Forward);
  }

  // Set the direction of the motor (forward/backward)
  void set_direction(MotorDirection motorDirection) {
	bool forward = motorDirection == MotorDirection::Forward;
	if (m_BuiltinReverse) forward = !forward;
	digitalWrite(m_In1, forward);
	digitalWrite(m_In2, !forward);
  }

  void turn_on() {
	set_direction(MotorDirection::Forward);
  }

  void turn_off() {
	digitalWrite(m_In1, LOW);
	digitalWrite(m_In2, LOW);
  }

#define MAX_MOTOR_SPEED 255
#define MIN_MOTOR_SPEED 85
  // Set target speed of the motor (0, 85 - 255)
  void set_speed(int rotation_speed) {
	if (rotation_speed < MIN_MOTOR_SPEED) {
	  if (rotation_speed < 42) rotation_speed = 0;
	  else if (rotation_speed > 42) rotation_speed = 42;
	}
	rotation_speed = constrain(rotation_speed, 0, MAX_MOTOR_SPEED);
	analogWrite(m_PWM, rotation_speed);
  }

private:
  int m_PWM, m_In1, m_In2;
  bool m_BuiltinReverse;
};