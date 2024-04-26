#include "PID.h"
#include "Arduino.h"

double PID::update(double error) {
	unsigned long now = millis();
	double delta_time = (double)(now - prev_millis);    

  double max_integrate = max_output_range * (1.0 / ki);
  
	// integral
	error_sum += (error * delta_time);
  if (error_sum < -max_integrate) error_sum = -max_integrate;
  if (error_sum > max_integrate) error_sum = max_integrate;

	double derivative;
  if (delta_time != 0.0)
    derivative = (error - last_error) / delta_time;

	double output = kp * error + ki * error_sum + kd * derivative;

  if (delta_time != 0.0)
	  last_error = error;
	prev_millis = now;

	return output;
}
