#include <Arduino.h>

#include "LED.h"
#include "config.h"
#include "Controller.h"

LED::Light LED::lights[] = { LED::Light(ESP_LED), LED::Light(MCU_LED) };

LED::Light::Light(const uint8_t& pin) {
	this->pin = pin;
	this->enabled = false;
	this->inverted = false;
	this->scheduled = false;

	this->startTime = 0;
	this->stopTime = 0;
}

LED::Light::Light(const uint8_t& pin, const bool& enabled, const bool& inverted) {
	this->pin = pin;
	this->enabled = enabled;
	this->inverted = inverted;
	this->scheduled = false;

	this->startTime = 0;
	this->stopTime = 0;
}

void LED::Light::invert() {
	if (!USE_LED) return;

	this->inverted = !this->inverted;
	digitalWrite(this->pin, (this->enabled && !this->inverted) || (this->inverted && !this->enabled) ? LED_STATE_ON : LED_STATE_OFF);
}

LED::LED() { }

void LED::setup() {
	if (!USE_LED) return;

	for (Light& led : lights) {
		pinMode(led.pin, OUTPUT);
		digitalWrite(led.pin, (led.enabled && !led.inverted) || (led.inverted && !led.enabled) ? LED_STATE_ON : LED_STATE_OFF);
	}
}

void LED::loop(const uint32_t& currentTime) {
	if (!USE_LED) return;

	for (Light& led : lights) {
		if (led.scheduled && currentTime >= led.startTime) {
			led.scheduled = false;
			digitalWrite(led.pin, led.inverted ? LED_STATE_OFF : LED_STATE_ON);
			led.enabled = true;
		}

		if (led.enabled && currentTime >= led.stopTime) {
			digitalWrite(led.pin, led.inverted ? LED_STATE_ON : LED_STATE_OFF);
			led.enabled = false;
		}
	}
}

void LED::blink(const uint32_t& currentTime, const uint8_t& pin, const uint16_t& duration, const uint16_t& delay) {
	if (!USE_LED) return;

	for (Light& led : lights) {
		if (led.pin == pin) {
			led.startTime = currentTime + delay;
			led.stopTime = currentTime + delay + duration;
			led.scheduled = true;
			return;
		}
	}
}
