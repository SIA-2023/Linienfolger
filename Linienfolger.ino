#define ENABLE_DASHBOARD 0
#define ENABLE_FERNBEDIENUNG 0

#if ENABLE_DASHBOARD
#include "Dashboard.h"
#endif

#if ENABLE_FERNBEDIENUNG
#include "Fernbedienung.h"
Fernbedienung fernbedienung;
#endif

#include "Linienfolger.h"
Linienfolger linienfolger;

void setup() {
#if ENABLE_FERNBEDIENUNG
	fernbedienung.setup();
#endif

	linienfolger.setup();
	linienfolger.mode = Linienfolger::Mode::FolgeLinie;
 
#if ENABLE_DASHBOARD
  Dashboard::setup();
#endif
}

void loop() {
#if ENABLE_FERNBEDIENUNG
	if (fernbedienung.has_received_new()) {
		switch (fernbedienung.get_current_command()) {
		case Fernbedienung::Command::Taster1:	linienfolger.mode = Linienfolger::Mode::FolgeLinie; break;
		case Fernbedienung::Command::Taster2:	linienfolger.mode = Linienfolger::Mode::LinksAusweichen; break;
		case Fernbedienung::Command::Taster3:	linienfolger.mode = Linienfolger::Mode::RechtsAusweichen; break;
		}
	}
#endif

#if ENABLE_DASHBOARD
  Dashboard::daten_empfangen(linienfolger);
#endif

	linienfolger.update();

#if ENABLE_DASHBOARD
  Dashboard::daten_senden(linienfolger);
#endif
}
