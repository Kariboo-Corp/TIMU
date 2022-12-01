#include <Arduino.h>
#include <common/mavlink.h>
#include <Streaming.h>
#include <SPI.h>
#include <SD.h>

#define VERSION "0.0.1"

#include "HighSpeedLogger.h"
#include "linker.h"
#include "autopilot_interface.h"

HighSpeedLogger logger(new SDClass(SD));
Linker linker(logger);
Autopilot_Interface pixhawk(&linker);

void setup() {
  Serial1.begin(921600);
  SerialUSB.begin(921600);

  delay(1000);

  linker.logger.begin(SDCARD_SS_PIN);

  SerialUSB << "TIMU - " << VERSION << endl;
}

Mavlink_Messages messages;
mavlink_attitude_t attitude;

void loop() {
  pixhawk.read_messages();
}