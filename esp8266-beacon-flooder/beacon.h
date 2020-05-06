#pragma once

#include <Arduino.h>

namespace beacon {
	void build_packet();

	extern uint8_t packet[128];
	extern uint8_t packet_size;
};
