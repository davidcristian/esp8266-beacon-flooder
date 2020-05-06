#include "serial.h"
#include "config.h"

#include <Arduino.h>

namespace serial {
	void print_loop(const uint8_t channel, const uint16_t packets) {
		Serial.print("CH: ");
		Serial.print(channel);
		Serial.print(channel < 10 ? "  PPL: " : " PPL: ");
		Serial.println(packets);
	}

	void setup() {
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

	void loop() {
		if (!USE_SERIAL) return;

		// Empty for now
	}
}
