#pragma once

#include <Arduino.h>

class Beacon {
private:
	uint8_t beaconHead[37] = {
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

	uint8_t beaconTail[12] = {
		/*  0 - 1  */ 0x01, 0x08,	// Tag: Supported Rates, Tag Length: 8
		/*    2    */ 0x82,		// 1(B)
		/*    3    */ 0x84,		// 2(B)
		/*    4    */ 0x8b,		// 5.5(B)
		/*    5    */ 0x96,		// 11(B)
		/*    6    */ 0x24,		// 18
		/*    7    */ 0x30,		// 24
		/*    8    */ 0x48,		// 36
		/*    9    */ 0x6c,		// 54

		/* 10 - 11 */ 0x03, 0x01	// Channel Set, Length
		// Channel
	};

	uint8_t beaconExtra[26] = {
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

	const String characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

	uint8_t* packet;
	uint8_t packetSize;

public:
	Beacon();
	void build(const uint8_t& channel);

	uint8_t* getPacket() const { return this->packet; };
	uint8_t getPacketSize() const { return this->packetSize; };

	~Beacon();
};
