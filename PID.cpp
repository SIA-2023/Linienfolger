#include "PID.h"
#include "Arduino.h"

double PID::update(double error) {
	unsigned long now = micros();
	double delta_time = (double)(now - prev_micros);
	
	// integral
	error_sum += (error * delta_time);

	double derivative = (error - last_error) / delta_time;

	double output = kp * error + ki * error_sum + kd * derivative;

	last_error = error;
	prev_micros = now;

	return output;
}