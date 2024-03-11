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

Motor left_motor;
Motor right_motor;

bool last_time_left = false;
bool last_time_right = false;

#include "Fernbedienung.h"

enum class Mode {
  FolgeLinie,
  LinksAusweichen,
  RechtsAusweichen,
} mode = Mode::FolgeLinie;

bool is_line(int value) {  
  return value > SENSOR_THRESHOLD;
}

void update_folge_linie(bool line_left, bool line_right);
void update_links_ausweichen(bool line_left, bool line_right);
void update_rechts_ausweichen(bool line_left, bool line_right);

void setup() {
    left_motor.init(PIN_MOTOR_LEFT_IN1, PIN_MOTOR_LEFT_IN2, PIN_MOTOR_LEFT_PWM, true);
    right_motor.init(PIN_MOTOR_RIGHT_IN1, PIN_MOTOR_RIGHT_IN2, PIN_MOTOR_RIGHT_PWM);
}

void loop() {
  if (fernbedienung_recieved_new()) {
    switch (fernbedienung_get_current_command()) {
      case FernbedienungCommand::Taster1:
        mode = Mode::FolgeLinie;
        break;
      case FernbedienungCommand::Taster2:
        mode = Mode::LinksAusweichen;
        break;
      case FernbedienungCommand::Taster3:
        mode = Mode::RechtsAusweichen;
        break;
    }
  }

  bool line_left = is_line(analogRead(PIN_SENSOR_LEFT));
  bool line_right = is_line(analogRead(PIN_SENSOR_RIGHT));

  switch (mode) {
    case Mode::FolgeLinie: update_folge_linie(line_left, line_right, MOTOR_TOP_SPEED); break;
    case Mode::LinksAusweichen: update_links_ausweichen(line_left, line_right); break;
    case Mode::RechtsAusweichen: update_rechts_ausweichen(line_left, line_right); break;
  }  
}

void forward(int speed) {
    left_motor.set_speed(speed);
    right_motor.set_speed(speed);
}

void left(int speed) {
    left_motor.set_speed(0);
    right_motor.set_speed(speed);
}

void right(int speed) {
    left_motor.set_speed(speed);
    right_motor.set_speed(0);
}

void update_folge_linie(bool line_left, bool line_right, int speed) {
  if (!line_left && !line_right) {
    if (last_time_left)
      left(speed);
    else if (last_time_right)
      right(speed);
    else
      forward(speed);
    return;
  }
  
  last_time_left = false;
  last_time_right = false;
      
  if (line_left && !line_right) {
    left(speed);
    last_time_left = true;
  }
  else if (line_right && !line_left) {
    right(speed);
    last_time_right = true;
  }
  else
    forward(speed);
}

void update_links_ausweichen(bool line_left, bool line_right) {
  if (line_left)
    left(MOTOR_AUSWEICH_SPEED);
  else
    update_folge_linie(line_left, line_right, MOTOR_AUSWEICH_SPEED);
}

void update_rechts_ausweichen(bool line_left, bool line_right) {
  if (line_right)
    right(MOTOR_AUSWEICH_SPEED);
  else
    update_folge_linie(line_left, line_right, MOTOR_AUSWEICH_SPEED);
}
