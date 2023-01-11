#pragma once

#include <Arduino.h>
#include "config.h"

class LED {
private:
	class Light {
	private:
		friend class LED;

		uint8_t pin;
		bool enabled;
		bool inverted;
		bool scheduled;

		uint32_t startTime;
		uint32_t stopTime;
		

		Light(const uint8_t& pin);
		Light(const uint8_t& pin, const bool& enabled, const bool& inverted);
		
		void invert();
	};

	static Light lights[];

public:
	LED();
	void setup();
	void loop(const uint32_t& currentTime);

	void blink(const uint32_t& currentTime, const uint8_t& pin, const uint16_t& duration = DEFAULT_BLINK_DURATION, const uint16_t& delay = 0);
};
