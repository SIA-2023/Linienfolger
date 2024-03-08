#include "Motor.h"

Motor left_motor;
Motor right_motor;

bool last_time_left = false;
bool last_time_right = false;

bool is_line(int value) {  
  return value > 250;
}

void setup() {
    left_motor.init(7, 8, 10, true);
    right_motor.init(5, 6, 9);
}

void forward() {
    left_motor.set_speed(255);
    right_motor.set_speed(255);
}

void left() {
    left_motor.set_speed(0);
    right_motor.set_speed(255);
}

void right() {
    left_motor.set_speed(255);
    right_motor.set_speed(0);
}

void loop() {
    int left_value = analogRead(A5);
    int right_value = analogRead(A4);

    bool sensor_left = is_line(left_value);
    bool sensor_right = is_line(right_value);

    if (!sensor_left && !sensor_right) {
      if (last_time_left)
        left();
      else if (last_time_right)
        right();
      else
        forward();
      return;
    }
    
    last_time_left = false;
    last_time_right = false;
        
    if (sensor_left && !sensor_right) {
      left();
      last_time_left = true;
    }
    else if (sensor_right && !sensor_left) {
      right();
      last_time_right = true;
    }
    else
      forward();
}
