#pragma once

#include <Arduino.h>
#include "Console.h"
#include "LED.h"
#include "Beacon.h"

class Controller {
private:
	Console console;
	LED led;
	Beacon beacon;

	uint32_t currentTime;
	uint8_t currentChannel;

	uint32_t nextLoop;
	uint16_t packetsPerLoop;

public:
	Controller(Console& console, LED& led, Beacon& beacon);
	void setup();
	void loop();

	uint32_t getCurrentTime() const { return this->currentTime; };
};
