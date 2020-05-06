#include "controller.h"
#include "beacon.h"
#include "serial.h"
#include "led.h"
#include "config.h"

#include <Arduino.h>
#include <ESP8266WiFi.h>

extern "C" {
  #include "user_interface.h"

	typedef void (*freedom_outside_cb_t)(uint8 status);
	int wifi_register_send_pkt_freedom_cb(freedom_outside_cb_t cb);
	void wifi_unregister_send_pkt_freedom_cb(void);
	int wifi_send_pkt_freedom(uint8* buf, int len, bool sys_seq);
}

namespace controller {
	uint32_t current_time = 0;
	uint8_t current_channel = START_CHANNEL;

	uint32_t next_loop = 0;
	uint16_t packets_per_loop = 0;

	void setup() {
		// SYSTEM INITIALIZATION
		randomSeed(os_random());

		WiFi.mode(WIFI_OFF);
		wifi_set_opmode(STATION_MODE);
		wifi_set_channel(current_channel);

		current_time = millis();
		next_loop = current_time + LOOP_TIME;

		led::blink_led(MCU_LED, 1000);
	}

	void loop() {
		current_time = millis();

		// CONFIGURED LOOP ACTIONS
		if (current_time > next_loop) {
			next_loop = current_time + LOOP_TIME;

			// PPL stands for Packets Per Loop
			serial::print_loop(current_channel, packets_per_loop);
			packets_per_loop = 0;

			if (HOP_CHANNELS) {
				current_channel = current_channel < MAX_CHANNEL ? current_channel + 1 : MIN_CHANNEL;
				wifi_set_channel(current_channel);
			}

			led::blink_led(ESP_LED);
		}

		// BUILD PACKET
		beacon::build_packet();

		// SEND PACKET
		packets_per_loop += wifi_send_pkt_freedom(beacon::packet, beacon::packet_size, false) == 0;

		// Setting a delay of 1 millisecond drastically reduces the amount of lost packets
		// by as much as 50.000 but also reduces the amount of sent packets by as much as 500
		// Setting a delay may help with prolonged usage due to putting less strain on the CPU
		// Add "delay(1);" if desired.
	}
}
