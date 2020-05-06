#pragma once

#include "config.h"
#include <Arduino.h>

namespace led {
	struct light {
		explicit light(uint8_t pin, bool enabled = false, bool inverted = false);
		void invert();
		
		uint8_t pin;
		bool enabled;
		bool inverted;
		bool scheduled;

		uint32_t start_time;
		uint32_t stop_time;
	};

	void setup();
	void loop();

	void blink_led(uint8_t pin, uint16_t duration = DEFAULT_BLINK_DURATION, uint16_t delay = 0);
}
