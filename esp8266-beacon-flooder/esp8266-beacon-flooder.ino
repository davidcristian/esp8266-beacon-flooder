#include "controller.h"
#include "serial.h"
#include "led.h"

void setup() {
    led::setup();
    serial::setup();
    controller::setup();
}

void loop() {
    controller::loop();
    serial::loop();
    led::loop();
}
