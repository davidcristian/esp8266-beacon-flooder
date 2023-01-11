#include <Arduino.h>

#include "Console.h"
#include "config.h"

Console::Console() { }

void Console::setup() {
	if (!USE_SERIAL) return;

	Serial.begin(BAUD_RATE);
	Serial.println("");

	for (uint8_t i = 0; i < 32; ++i) {
		Serial.print("-");
	}

	Serial.println("\r\nesp8266-beacon-flooder by davidcristian");
	Serial.print("VERSION ");
	Serial.print(VERSION);
	Serial.println("\r\n");
}

void Console::read() {
	if (!USE_SERIAL) return;

	// Empty for now
}

void Console::printStatus(const uint8_t& channel, const uint16_t& packets) {
	if (!USE_SERIAL) return;

	Serial.print("CH: ");
	Serial.print(channel);
	Serial.print(channel < 10 ? "  PPL: " : " PPL: ");
	Serial.println(packets);
}
