#ifndef ZEEPROM_H
#define ZEEPROM_H

#include <Arduino.h>

// Enumerations
enum class DeviceTypeIdentifier : uint8_t
{
    MEMORY_ARRAY = 0b1010,
    IDENTIFICATION_PAGE = 0b1011
};

enum class HardwareSlaveAddressBits : uint8_t
{
    // A2 A1 A0
    A000 = 0b000,
    A001 = 0b001,
    A010 = 0b010,
    A011 = 0b011,
    A100 = 0b100,
    A101 = 0b101,
    A110 = 0b110,
    A111 = 0b111
};

enum class READ_WRITE : uint8_t
{
    READ = 0b1,
    WRITE = 0b0
};

class ZEEPROM
{
public:
    ZEEPROM(); // hardware address bits A0, A1, A2
    void setAddress(HardwareSlaveAddressBits address);
    bool writeByte(uint16_t address, uint8_t data); // address 0-16383, data 0-255
    uint8_t readByte(uint16_t address);             // address 0-16383

private:
    uint8_t _address;
    uint8_t _deviceTypeIdentifier;
    void _setDeviceTypeIdentifier(DeviceTypeIdentifier deviceTypeIdentifier);
    uint8_t _getHeader(READ_WRITE readWrite);
    uint16_t _getAddressBytes(uint16_t address);
};

extern ZEEPROM Zeeprom;

#endif
