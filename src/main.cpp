#include <Arduino.h>
#include <common/mavlink.h>
#include <Streaming.h>
#include <SPI.h>
#include <SD.h>

#include "linker.h"
#include "autopilot_interface.h"

Linker linker(921600);
Autopilot_Interface pixhawk(&linker);

void setup() {
  Serial1.begin(921600);
  SerialUSB.begin(921600);

  delay(1000);

  SerialUSB << "Hello, World" << endl;
}

Mavlink_Messages messages;
mavlink_attitude_t attitude;

void loop() {

  pixhawk.read_messages();

  messages = pixhawk.current_messages;
	attitude = messages.attitude;

	SerialUSB << ("    ap time:     ") << attitude.time_boot_ms << endl;
  SerialUSB << ("pitch : ") << _FLOAT(attitude.pitch, 32) << ", roll : " << _FLOAT(attitude.roll, 32) << ", yaw : " << _FLOAT(attitude.yaw, 32) << endl;

}