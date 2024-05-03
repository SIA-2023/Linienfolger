#include "Linienfolger.h"
#include "Fernbedienung.h"

#define ENABLE_DASHBOARD 0
#define ENABLE_FERNBEDIENUNG 0

#if ENABLE_FERNBEDIENUNG
Fernbedienung fernbedienung;
#endif
Linienfolger linienfolger;

void setup() {
#if ENABLE_FERNBEDIENUNG
	fernbedienung.setup();
#endif

	linienfolger.setup();
	linienfolger.mode = Linienfolger::Mode::FolgeLinie;

#if ENABLE_DASHBOARD
  Serial.begin(115200);
#endif
}

void loop() {
#if ENABLE_DASHBOARD
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
#endif

#if ENABLE_FERNBEDIENUNG
	if (fernbedienung.has_received_new()) {
		switch (fernbedienung.get_current_command()) {
		case Fernbedienung::Command::Taster1:	linienfolger.mode = Linienfolger::Mode::FolgeLinie; break;
		case Fernbedienung::Command::Taster2:	linienfolger.mode = Linienfolger::Mode::LinksAusweichen; break;
		case Fernbedienung::Command::Taster3:	linienfolger.mode = Linienfolger::Mode::RechtsAusweichen; break;
		}
	}
#endif

  // NUR ZUM TESTEN OHNE FERNBEDIENUNG
  //linienfolger.mode = Linienfolger::Mode::RechtsAusweichen;
	
	linienfolger.update();

#if ENABLE_DASHBOARD
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
#endif
}
