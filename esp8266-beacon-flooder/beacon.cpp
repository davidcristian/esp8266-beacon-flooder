#include "beacon.h"
#include "config.h"
#include "controller.h"

#include <Arduino.h>

namespace beacon {
	static char characters[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	static uint8_t character_count = sizeof characters / sizeof characters[0];

	static uint8_t beacon_head[] = {
		/*  0 - 3  */ 0x80, 0x00, 0x00, 0x00, // Type / Subtype: Management Beacon Frame
		/*  4 - 9  */ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, // Destination MAC
		/* 10 - 15 */ 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, // Source MAC
		/* 16 - 21 */ 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, // Source MAC
		/* 22 - 23 */ 0x00, 0x00, // Fragment & Sequence Number (handled by the SDK)
		/* 24 - 31 */ 0x83, 0x51, 0xf7, 0x8f, 0x0f, 0x00, 0x00, 0x00, // Timestamp
		/* 32 - 33 */ 0x64, 0x00, // Interval: [0x64, 0x00] => 100ms, [0xe8, 0x03] => 1s
		/* 34 - 35 */ 0x21, 0x00, // Capabilities Information 0x21 = OPEN, 0x31 = ENCRYPTED; // 0x01, 0x04 = ?
		/* 36 - -- */ 0x00
		/* -- - 37  , 0x04,             // SSID Length
					  0x20, 0x20, 0x20, 0x20  // SSID */
	};

	static uint8_t beacon_tail[] = {
		/*  0 - 1  */ 0x01, 0x08,	// Tag: Supported Rates, Tag Length: 8
		/*    2    */ 0x82,			  // 1(B)
		/*    3    */ 0x84,			  // 2(B)
		/*    4    */ 0x8b,			  // 5.5(B)
		/*    5    */ 0x96,			  // 11(B)
		/*    6    */ 0x24,			  // 18
		/*    7    */ 0x30,			  // 24
		/*    8    */ 0x48,			  // 36
		/*    9    */ 0x6c,			  // 54

		/* 10 - 11 */ 0x03, 0x01	// Channel Set, Length
		// Channel
	};

	static uint8_t beacon_extra[] = {
		// RSN information
		/*  0 - 1  */ 0x30, 0x18,
		/*  2 - 3  */ 0x01, 0x00,
		/*  4 - 7  */ 0x00, 0x0f, 0xac, 0x02,
		/*  8 - 9  */ 0x02, 0x00,
		/* 10 - 13 */ 0x00, 0x0f, 0xac, 0x04,
		/* 14 - 17 */ 0x00, 0x0f, 0xac, 0x02, // 0x00, 0x0f, 0xac, 0x04
		/* 18 - 19 */ 0x01, 0x00,
		/* 20 - 23 */ 0x00, 0x0f, 0xac, 0x02,
		/* 24 - 25 */ 0x00, 0x00
	};

	uint8_t packet[128] = { 0 };
	uint8_t packet_size = 0;
	
	void build_packet() {
		packet_size = 0;

		// COPY BEACON HEAD
		for (uint8_t fragment : beacon_head) {
			packet[packet_size++] = fragment;
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
		packet[packet_size++] = name_length;

		// RANDOMIZE SSID
		if (USE_SORT_CHARACTER)
			packet[packet_size++] = SORT_CHARACTER;
		for (uint8_t i = 0; i < uint8_t(USE_SORT_CHARACTER ? name_length - 1 : name_length); ++i) {
			packet[packet_size++] = characters[random(0, character_count)];
		}

		// COPY BEACON TAIL
		for (uint8_t fragment : beacon_tail) {
			packet[packet_size++] = fragment;
		}

		// SET CHANNEL
		packet[packet_size++] = controller::current_channel;

		// COPY BEACON EXTRA
		if (BROADCAST_EXTRA_SECURITY_INFORMATION) {
			for (uint8_t fragment : beacon_extra) {
				packet[packet_size++] = fragment;
			}
		}
	}
}
