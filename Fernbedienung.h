#pragma once

#include "rc5_decoder_fz3.h"

struct RC5 {
  uint8_t toggle, address, command;
} maerklin_fst_current, maerklin_fst_previous;

enum FernbedienungCommand : uint8_t {
  TasterStern = 80, // *
  Taster1 = 81,
  Taster2 = 82,
  Taster3 = 83,
  Taster4 = 84,
};

void fernbedienung_setup() {
  rc5_init_fz3();
}

bool fernbedienung_recieved_new() {
  maerklin_fst_current.command = 0;
  rc5_read_fz3(&maerklin_fst_current.toggle, &maerklin_fst_current.address, &maerklin_fst_current.command);
  return maerklin_fst_previous.toggle != maerklin_fst_current.toggle && maerklin_fst_current.address == 24;
}

FernbedienungCommand fernbedienung_get_current_command() {
  return FernbedienungCommand(maerklin_fst_current.command);
}