#pragma once

#include "Linienfolger.h"

class Dashboard {
public:
  static void setup();
  static void daten_empfangen(Linienfolger& linienfolger);
  static void daten_senden(const Linienfolger& linienfolger);
};
