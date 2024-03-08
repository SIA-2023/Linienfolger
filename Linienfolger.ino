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

#include "Motor.h"

Motor left_motor;
Motor right_motor;

bool last_time_left = false;
bool last_time_right = false;

bool is_line(int value) {  
  return value > SENSOR_THRESHOLD;
}

void setup() {
    left_motor.init(PIN_MOTOR_LEFT_IN1, PIN_MOTOR_LEFT_IN2, PIN_MOTOR_LEFT_PWM, true);
    right_motor.init(PIN_MOTOR_RIGHT_IN1, PIN_MOTOR_RIGHT_IN2, PIN_MOTOR_RIGHT_PWM);
}

void forward() {
    left_motor.set_speed(MOTOR_TOP_SPEED);
    right_motor.set_speed(MOTOR_TOP_SPEED);
}

void left() {
    left_motor.set_speed(0);
    right_motor.set_speed(MOTOR_TOP_SPEED);
}

void right() {
    left_motor.set_speed(MOTOR_TOP_SPEED);
    right_motor.set_speed(0);
}

void loop() {
    int left_value = analogRead(PIN_SENSOR_LEFT);
    int right_value = analogRead(PIN_SENSOR_RIGHT);

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
