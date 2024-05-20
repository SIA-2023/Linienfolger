#pragma once

#include "Arduino.h"
#include "PID.h"

#define PIN_SENSOR_LEFT A4
#define PIN_SENSOR_RIGHT A5

#define SENSOR_THRESHOLD 250

#define PIN_MOTOR_LEFT_IN1 7
#define PIN_MOTOR_LEFT_IN2 8
#define PIN_MOTOR_LEFT_PWM 10

#define PIN_MOTOR_RIGHT_IN1 5
#define PIN_MOTOR_RIGHT_IN2 6
#define PIN_MOTOR_RIGHT_PWM 9

#define MOTOR_FOLGE_LINIE_SPEED 127
#define MOTOR_AUSWEICH_SPEED 125

#include "Motor.h"

class Linienfolger {
public:
	void setup();
	void update();
	
	enum class Mode {
		FolgeLinie,
		LinksAusweichen,
		RechtsAusweichen,
	};

	Mode mode = Mode::FolgeLinie;

  PID pid = PID(0.5, 0.5, 1.0, 127.5);
  
  bool last_sensor_left = false;
  bool last_sensor_right = false;

  int last_motor_left = 0;
  int last_motor_right = 0;
  
private:
	void update_folge_linie(bool line_left, bool line_right, int speed);
	void update_links_ausweichen(bool line_left, bool line_right);
	void update_rechts_ausweichen(bool line_left, bool line_right);

  void set_left_motor(int speed);
  void set_right_motor(int speed);

	static bool is_line(int value);

private:
  Motor left_motor;
  Motor right_motor;
};
