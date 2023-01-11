#pragma once

#include <Arduino.h>

class Console {
private:
	// Nothing for now

public:
	Console();
	void setup();
	void read();

	void printStatus(const uint8_t& channel, const uint16_t& packets);
};
