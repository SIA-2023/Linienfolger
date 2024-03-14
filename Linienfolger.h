#pragma once

#include "Arduino.h"

#define PIN_SENSOR_LEFT A5
#define PIN_SENSOR_RIGHT A4

#define SENSOR_THRESHOLD 250

#define PIN_MOTOR_LEFT_IN1 7
#define PIN_MOTOR_LEFT_IN2 8
#define PIN_MOTOR_LEFT_PWM 10

#define PIN_MOTOR_RIGHT_IN1 5
#define PIN_MOTOR_RIGHT_IN2 6
#define PIN_MOTOR_RIGHT_PWM 9

#define MOTOR_TOP_SPEED 255
#define MOTOR_AUSWEICH_SPEED 150

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

private:
	void forward(int speed);
	void left(int speed);
	void right(int speed);

	void update_folge_linie(bool line_left, bool line_right, int speed);
	void update_links_ausweichen(bool line_left, bool line_right);
	void update_rechts_ausweichen(bool line_left, bool line_right);

	static bool is_line(int value);

private:
	Motor left_motor;
	Motor right_motor;
	bool last_time_left = false;
	bool last_time_right = false;
};