#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "Controller.h"
#include "config.h"
#include "Beacon.h"
#include "Console.h"
#include "LED.h"

extern "C" {
	#include "user_interface.h"

	typedef void (*freedom_outside_cb_t)(uint8 status);
	int wifi_register_send_pkt_freedom_cb(freedom_outside_cb_t cb);
	void wifi_unregister_send_pkt_freedom_cb(void);
	int wifi_send_pkt_freedom(uint8* buf, int len, bool sys_seq);
}

Controller::Controller(Console& console, LED& led, Beacon& beacon) : console{ console }, led{ led }, beacon{ beacon } {
	currentTime = 0;
	currentChannel = START_CHANNEL;

	nextLoop = 0;
	packetsPerLoop = 0;
}

void Controller::setup() {
	// SYSTEM INITIALIZATION
	randomSeed(os_random());

	WiFi.mode(WIFI_OFF);
	wifi_set_opmode(STATION_MODE);
	wifi_set_channel(currentChannel);

	currentTime = millis();
	nextLoop = currentTime + LOOP_TIME;

	led.blink(currentTime, MCU_LED, 1000);
}

void Controller::loop() {
	currentTime = millis();

	// CONFIGURED LOOP ACTIONS
	if (currentTime > nextLoop) {
		nextLoop = currentTime + LOOP_TIME;

		// PPL stands for Packets Per Loop
		console.printStatus(currentChannel, packetsPerLoop);
		packetsPerLoop = 0;

		if (HOP_CHANNELS) {
			currentChannel = currentChannel < MAX_CHANNEL ? currentChannel + 1 : MIN_CHANNEL;
			wifi_set_channel(currentChannel);
		}

		led.blink(currentTime, ESP_LED);
	}

	// BUILD PACKET
	beacon.build(this->currentChannel);

	// SEND PACKET
	packetsPerLoop += wifi_send_pkt_freedom(beacon.getPacket(), beacon.getPacketSize(), false) == 0;

	// Setting a delay of 1 millisecond drastically reduces the amount of lost packets
	// by as much as 50.000 but also reduces the amount of sent packets by as much as 500
	// Setting a delay may help with prolonged usage due to putting less strain on the CPU
	// Add "delay(1);" if desired.
}
