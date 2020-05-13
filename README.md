# Disclaimer
esp8266-beacon-flooder is provided "as is", without warranty of any kind. The author of the project takes no responsibility for the abuse of anything provided and presented in the repository. Illegal usage of esp8266-beacon-flooder is strictly prohibited.

# esp8266-beacon-flooder

A beacon frame flooder that that is making use of the cheap ESP8266 WiFi module.

## Getting Started

### Prerequisites

- The [Arduino IDE](https://www.arduino.cc/en/Main/Software) or any other software that allows you to upload sketches to your development board

### Usage

1. Open the Arduino IDE and navigate to `File > Preferences`, then add `http://arduino.esp8266.com/stable/package_esp8266com_index.json` to the `Additional Boards Manager URLs` section
2. Open `Tools > Board: "XYZ" > Boards Manager...` and search for `esp8266`
3. Install the `esp8266` package from the `ESP8266 Community`. The latest version (v2.7.1 as of writing this) is preferred
4. Clone the repository
5. Open the `esp8266-beacon-flooder.ino` file
6. (Optional) Tweak the settings found in the `config.h` file
7. Upload the sketch to your board

### Features

Everything mentioned here can be tweaked in the `config.h` file
- Change the loop time (the loop time is used to switch channels and output the Packets Per Loop stat in the SERIAL interface)
- Enable / Disable the LED interface and SERIAL interface
- Set the starting channel, the minimum channel, the maximum channel, and enable channel hopping
- Set the SSID length or randomize it within set minimum and maximum values
- Append a character at the start of the SSID (such as ' ' or '!') to flood ascending lists
- Broadcast secure access points along with extra RSN information

## License

This project is licensed under the GPLv3 License - see the [LICENSE](LICENSE) file for details

## Acknowledgments

* Spacehuhn for the API fix and the beacon packet format
