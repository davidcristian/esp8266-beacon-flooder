#pragma once

#include <Arduino.h>

namespace controller {
	void setup();
	void loop();

	extern uint32_t current_time;
	extern uint8_t current_channel;
}
