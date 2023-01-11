#include "config.h"
#include "Controller.h"
#include "Console.h"
#include "LED.h"

Console console{};
LED led{};

Beacon beacon{};
Controller ctrl{console, led, beacon};

void setup() {
	delay(START_DELAY);

	console.setup();
	delay(100);

	led.setup();
	delay(100);

	ctrl.setup();
	delay(100);
}

void loop() {
	ctrl.loop();
	led.loop(ctrl.getCurrentTime());
	console.read();
}
