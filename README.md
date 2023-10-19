# ZEEPROM Library

![GitHub](https://img.shields.io/github/license/bin2ai/zeeprom)
![GitHub release (latest by date)](https://img.shields.io/github/v/release/bin2ai/zeeprom)
![GitHub issues](https://img.shields.io/github/issues/bin2ai/zeeprom)

The ZettaEEPROM library is a versatile tool for managing the Zetta EEPROM IC (ZD24C128A) non-volatile memory storage for Arduino-compatible devices. It simplifies the process of reading and writing data to the EEPROM, making it easy to store and retrieve configuration settings, calibration data, and more.

## Table of Contents

- [ZEEPROM Library](#zeeprom-library)
  - [Table of Contents](#table-of-contents)
  - [Installation](#installation)
  - [Usage](#usage)

## Installation

1. **Download:** Download the latest release of the ZEEPROM library from the [releases page](https://github.com/bin2ai/zeeprom/releases).

2. **Arduino IDE:**
   - Open the Arduino IDE.
   - Click "Sketch" -> "Include Library" -> "Add .ZIP Library..."
   - Select the downloaded ZIP file.

3. **Manual Installation:** If you prefer to install it manually, copy the contents of the ZIP file to your Arduino libraries folder.

## Usage

Here's a simple example of how to use the ZEEPROM library to store and retrieve data:

```cpp
#include "ZEEPROM.h"
#include <Wire.h>
#include <Arduino.h>

void setup()
{
    Wire.begin();
    Wire.setClock(400000);

    /*
    The Zetta ZD24C128A support 3 speed modes;
        - Standard Mode: up to 100KHz
        - Fast Mode: up to 400KHz
        - Fast Mode Plus: up to 1MHz
    */

    Serial.begin(9600);

    Zeeprom.setAddress(HardwareSlaveAddressBits::A000);

    Zeeprom.writeByte(0, 0x00);
    Serial.println(Zeeprom.readByte(0), HEX); // should be 0x00

    Zeeprom.writeByte(0, 0xFF);
    Serial.println(Zeeprom.readByte(0), HEX); // should be 0xFF

    // up to 2^14-1 = byte #16383 or 128 Kbits total
    Zeeprom.writeByte(16383, 0x00);
    Serial.println(Zeeprom.readByte(16383), HEX); // should be 0x00

    Zeeprom.writeByte(16383, 0xFF);
    Serial.println(Zeeprom.readByte(16383), HEX); // should be 0xFF
}

void loop()
{
}
```
