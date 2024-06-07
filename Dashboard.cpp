#include "Dashboard.h"

void Dashboard::setup() {
  Serial.begin(115200);
}

void Dashboard::daten_empfangen(Linienfolger& linienfolger) {
  if (Serial.available()) {
    // format: "{target}{value}\n";
    String command = Serial.readStringUntil('\n');
    char target = command.charAt(0);
    double value = command.substring(1).toFloat();
    switch (target) {
      case 'p': linienfolger.pid.kp = value; break;
      case 'i': linienfolger.pid.ki = value; break;
      case 'd': linienfolger.pid.kd = value; break;
    }
  }
}

void Dashboard::daten_senden(const Linienfolger& linienfolger) {
  Serial.print(linienfolger.last_motor_left);
  Serial.print(',');
  Serial.print(linienfolger.last_motor_right);
  Serial.print(',');
  Serial.print(linienfolger.last_sensor_left);
  Serial.print(',');
  Serial.print(linienfolger.last_sensor_right);
  Serial.print(',');
  Serial.print((float)linienfolger.pid.kp);
  Serial.print(',');
  Serial.print((float)linienfolger.pid.ki);
  Serial.print(',');
  Serial.print((float)linienfolger.pid.kd);
  Serial.print('\n');
}
