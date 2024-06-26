#pragma once

class PID {
public:
	double kp = 0.0;
	double ki = 0.0;
	double kd = 0.0;
  double max_output_range = 0.0;

  PID(double kp, double ki, double kd, double max_output_range)
    : kp(kp),
      ki(ki),
      kd(kd),
      max_output_range(max_output_range) {}

	double update(double error);

private:
	unsigned long prev_millis = 0;
	double error_sum = 0.0;
	double last_error = 0.0;
};
