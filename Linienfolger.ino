#include "Linienfolger.h"
#include "Fernbedienung.h"

// Fernbedienung wurde noch nicht getestet!
Fernbedienung fernbedienung;
Linienfolger linienfolger;

void setup() {
	fernbedienung.setup();
	linienfolger.setup();
	linienfolger.mode = Linienfolger::Mode::FolgeLinie;
}

void loop() {
	/* Wurde noch nicht getested!
	if (fernbedienung.has_received_new()) {
		switch (fernbedienung.get_current_command()) {
		case Fernbedienung::Command::Taster1:	linienfolger.mode = Linienfolger::Mode::FolgeLinie; break;
		case Fernbedienung::Command::Taster2:	linienfolger.mode = Linienfolger::Mode::LinksAusweichen; break;
		case Fernbedienung::Command::Taster3:	linienfolger.mode = Linienfolger::Mode::RechtsAusweichen; break;
		}
	}
	*/

	linienfolger.update();
}