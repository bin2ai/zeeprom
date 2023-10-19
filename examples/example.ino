#include "ZettaEEPROM.h"
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