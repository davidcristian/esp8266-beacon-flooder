#pragma once

#include <Arduino.h>

namespace serial {
	void setup();
	void loop();

	void print_loop(uint8_t channel, uint16_t packets);
}
