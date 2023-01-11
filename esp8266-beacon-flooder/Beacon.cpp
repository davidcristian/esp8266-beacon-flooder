#include <Arduino.h>

#include "config.h"
#include "Beacon.h"
#include "Controller.h"

Beacon::Beacon() {
	packetSize = 0;
	packet = new uint8_t[128];

	for (uint8_t i = 0; i < 128; ++i) {
		packet[i] = 0;
	}
}

void Beacon::build(const uint8_t& channel) {
	packetSize = 0;

	// COPY BEACON HEAD
	for (uint8_t fragment : beaconHead) {
		packet[packetSize++] = fragment;
	}

	// RANDOMIZE MAC
	for (uint8_t i = 0; i < 6; ++i) {
		packet[10 + i] = packet[16 + i] = random(MAC_ADDRESS_MIN, MAC_ADDRESS_MAX + 1);
	}

	// Interval: [0x64, 0x00] => 100ms, [0xe8, 0x03] => 1s
	if (TAG_SLOWER_BROADCAST_INTERVAL) {
		packet[32] = 0xe8;
		packet[33] = 0x03;
	}

	if (BROADCAST_AS_SECURE_AP) {
		packet[34] = 0x31;
	}

	// SET SSID LENGTH
	uint8_t name_length = SET_SSID_LENGTH;
	if (RANDOMIZE_SSID_LENGTH) name_length = random(USE_SORT_CHARACTER ? RANDOM_SSID_LENGTH_MIN + 1 : RANDOM_SSID_LENGTH_MIN, RANDOM_SSID_LENGTH_MAX + 1);
	packet[packetSize++] = name_length;

	// RANDOMIZE SSID
	if (USE_SORT_CHARACTER)
		packet[packetSize++] = SORT_CHARACTER;
	for (uint8_t i = 0; i < uint8_t(USE_SORT_CHARACTER ? name_length - 1 : name_length); ++i) {
		packet[packetSize++] = characters.charAt(random(0, characters.length()));
	}

	// COPY BEACON TAIL
	for (uint8_t fragment : beaconTail) {
		packet[packetSize++] = fragment;
	}

	// SET CHANNEL
	packet[packetSize++] = channel;

	// COPY BEACON EXTRA
	if (BROADCAST_EXTRA_SECURITY_INFORMATION) {
		for (uint8_t fragment : beaconExtra) {
			packet[packetSize++] = fragment;
		}
	}
}

Beacon::~Beacon() {
	delete[] packet;
}
