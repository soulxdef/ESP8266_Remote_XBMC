#include <Arduino.h>
#include "sys/XBMC.h"
void setup() {
  Serial.begin(115200);
  delay(3000);
  LoadModules();
}

void loop() {
  Handle_http();
  Recive_code();
  handle_ts();
}