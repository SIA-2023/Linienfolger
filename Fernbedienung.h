#pragma once

#include "Arduino.h"
#include "rc5_decoder_fz3.h"


class Fernbedienung {
public:
	enum Command : uint8_t {
		TasterStern = 80, // *
		Taster1 = 81,
		Taster2 = 82,
		Taster3 = 83,
		Taster4 = 84,
	};

	void setup();
	bool has_received_new();
	Command get_current_command() const;

private:
	struct RC5 {
		uint8_t toggle, address, command;
	} maerklin_fst_current, maerklin_fst_previous;
};