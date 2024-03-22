#pragma once

class PID {
public:
	double kp = 0.0;
	double ki = 0.0;
	double kd = 0.0;

  PID(double kp, double ki, double kd) : kp(kd), ki(ki), kd(kd) {}

	double update(double error);

private:
	unsigned long prev_micros = 0;
	double error_sum = 0.0;
	double last_error = 0.0;
};
