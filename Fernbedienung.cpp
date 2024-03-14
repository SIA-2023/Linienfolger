#include "Fernbedienung.h"

void Fernbedienung::setup() {
	rc5_init_fz3();
}

bool Fernbedienung::has_received_new() {
	maerklin_fst_current.command = 0;
	rc5_read_fz3(&maerklin_fst_current.toggle, &maerklin_fst_current.address, &maerklin_fst_current.command);
	return maerklin_fst_previous.toggle != maerklin_fst_current.toggle && maerklin_fst_current.address == 24;
}

Fernbedienung::Command Fernbedienung::get_current_command() const {
	return Command(maerklin_fst_current.command);
}