/*I2C driver for ZD24C128A 128kByte EEPROM
 */
#include <Arduino.h>
#include <Wire.h>
#include "ZEEPROM.h"

ZEEPROM::ZettaEEPROM()
{
}

void ZEEPROM::ZEEPROM(HardwareSlaveAddressBits address)
{
    if (address >= HardwareSlaveAddressBits::A000 && address <= HardwareSlaveAddressBits::A111)
        _address = static_cast<int>(address);
    else
        _address = static_cast<int>(HardwareSlaveAddressBits::A000);
    _setDeviceTypeIdentifier(DeviceTypeIdentifier::MEMORY_ARRAY);
}

void ZEEPROM::_setDeviceTypeIdentifier(DeviceTypeIdentifier deviceTypeIdentifier)
{
    if (deviceTypeIdentifier == DeviceTypeIdentifier::MEMORY_ARRAY || deviceTypeIdentifier == DeviceTypeIdentifier::IDENTIFICATION_PAGE)
        _deviceTypeIdentifier = static_cast<int>(deviceTypeIdentifier);
    else
        _deviceTypeIdentifier = static_cast<int>(DeviceTypeIdentifier::MEMORY_ARRAY);
}

uint8_t ZEEPROM::_getHeader(READ_WRITE readWrite)
{
    if (readWrite != READ_WRITE::READ && readWrite != READ_WRITE::WRITE)
        readWrite = READ_WRITE::READ;
    return (_deviceTypeIdentifier << 4) | (_address << 1) | static_cast<uint8_t>(readWrite);
}

uint16_t ZEEPROM::_getAddressBytes(uint16_t address)
{
    address &= 0b0011111111111111; // 0x3FFF or 16383
    return address;
}

bool ZEEPROM::writeByte(uint16_t address, uint8_t data)
{
    uint8_t status = 1;
    Wire.beginTransmission(_address);
    status = Wire.write(_getHeader(READ_WRITE::WRITE));
    if (status != 1)
        return false;
    status = Wire.write(_getAddressBytes(address));
    if (status != 1)
        return false;
    Wire.write(data);
    status = Wire.endTransmission();
    if (status != 1)
        return false;
    return true;
}

uint8_t ZEEPROM::readByte(uint16_t address)
{
    uint8_t status = 1;
    Wire.beginTransmission(_address);
    status = Wire.write(_getHeader(READ_WRITE::READ));
    if (status != 1)
        return false;
    status = Wire.write(_getAddressBytes(address));
    if (status != 1)
        return false;
    status = Wire.endTransmission();
    if (status != 1)
        return false;
    Wire.requestFrom(_address, 1);
    return true;
}
