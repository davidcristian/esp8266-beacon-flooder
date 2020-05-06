#include "led.h"
#include "config.h"
#include "controller.h"

#include <Arduino.h>

namespace led {
	light lights[] = { light(ESP_LED), light(MCU_LED) };
	
	light::light(const uint8_t pin, const bool enabled, const bool inverted) {
		this->pin = pin;
		this->enabled = enabled;
		this->inverted = inverted;
		this->scheduled = false;

		this->start_time = 0;
		this->stop_time = 0;
	}

	void light::invert() {
		if (!USE_LED) return;
		
		this->inverted = !this->inverted;
		digitalWrite(this->pin, (this->enabled && !this->inverted) || (this->inverted && !this->enabled) ? LED_STATE_ON : LED_STATE_OFF);
	}

	void setup() {
		if (!USE_LED) return;
		
		for (light& led : lights) {
			pinMode(led.pin, OUTPUT);
			digitalWrite(led.pin, (led.enabled && !led.inverted) || (led.inverted && !led.enabled) ? LED_STATE_ON : LED_STATE_OFF);
		}
	}
	
	void loop() {
		if (!USE_LED) return;
		
		for (light& led : lights) {
			if (led.scheduled && controller::current_time >= led.start_time) {
				led.scheduled = false;
				digitalWrite(led.pin, led.inverted ? LED_STATE_OFF : LED_STATE_ON);
				led.enabled = true;
			}

			if (led.enabled && controller::current_time >= led.stop_time) {
				digitalWrite(led.pin, led.inverted ? LED_STATE_ON : LED_STATE_OFF);
				led.enabled = false;
			}
		}
	}

	void blink_led(const uint8_t pin, const uint16_t duration, const uint16_t delay) {
		for (light& led : lights) {
			if (led.pin == pin) {
				led.start_time = controller::current_time + delay;
				led.stop_time = controller::current_time + delay + duration;
				led.scheduled = true;
				return;
			}
		}
	}
}
