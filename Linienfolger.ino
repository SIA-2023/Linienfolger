#include "Motor.h"

Motor left_motor;
Motor right_motor;

bool last_time_left = false;
bool last_time_right = false;

#define DEBUG false

bool is_line(int value) {  
  return value > 250;
}

void setup() {
#if DEBUG
    Serial.begin(9600);
#endif
  
    left_motor.init(7, 8, 10, true);
    right_motor.init(5, 6, 9);
}

void loop() {
    int left_value = analogRead(A5);
    int right_value = analogRead(A4);

#if DEBUG
    Serial.print("L: ");
    Serial.print(left_value);
    Serial.print(" R: ");
    Serial.println(right_value);
#endif
    
    bool sensor_left = is_line(left_value);
    bool sensor_right = is_line(right_value);

    bool left = false;
    bool right = false;
  
    if (sensor_left && !sensor_right) {
      left = true;
    }
    if (sensor_right && !sensor_left) {
      right = true;
    }
    if (/*sensor_links && sensor_rechts || */!sensor_left && !sensor_right) {
      if (last_time_left)
        left = true;
      if (last_time_right)
        right = true;
    }
    else {
      
      last_time_left = sensor_left;
      last_time_right = sensor_right;
    }
    
    left_motor.set_speed(left ? 80 : 255);
    right_motor.set_speed(right ? 80 : 255);

}
