#pragma once

// CORE
#define VERSION "2.0.1"
#define START_DELAY 5000

#define USE_SERIAL 1
#define USE_LED 1

// CONFIGURATION
#define RANDOMIZE_SSID_LENGTH 1
#define RANDOM_SSID_LENGTH_MIN 4	// must be greater than 0 and less than RANDOM_SSID_LENGTH_MAX; this value is incremented by 1 if USE_SORT_CHARACTER is enabled!
#define RANDOM_SSID_LENGTH_MAX 16	// must be less than 33 and greater than RANDOM_SSID_LENGTH_MIN

#define SET_SSID_LENGTH 8			// must be at least 1; ignored if RANDOMIZE_SSID_LENGTH is enabled
#define USE_SORT_CHARACTER 1		// SET_SSID_LENGTH must be at least 2 or RANDOMIZE_SSID_LENGTH must be enabled
#define SORT_CHARACTER ' '			// Use ' ' or '!' if you want to flood ascending lists

#define BROADCAST_AS_SECURE_AP 0
#define BROADCAST_EXTRA_SECURITY_INFORMATION 0
#define TAG_SLOWER_BROADCAST_INTERVAL 0

#define HOP_CHANNELS 0				// Hops channels every LOOP_TIME milliseconds
#define LOOP_TIME 1000

// ATTACK
#define START_CHANNEL 6
#define MIN_CHANNEL 1
#define MAX_CHANNEL 11				// US: 11; EU: 13; Japan: 14 (802.11b only)

#define MAC_ADDRESS_MIN 0
#define MAC_ADDRESS_MAX 255

// SERIAL
#define BAUD_RATE 115200

// LED
#define LED_STATE_ON 0x0
#define LED_STATE_OFF 0x1
#define DEFAULT_BLINK_DURATION 32

#define ESP_LED 2
#define MCU_LED 16
