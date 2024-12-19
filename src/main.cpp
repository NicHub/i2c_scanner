/**
 * i2c_scanner
 *
 * This is the PlatformIO version of the I²C scanner (i2c_scanner.ino) which
 * is provided in the Arduino IDE examples.
 *
 * - On macOS the original file can be found here:
 *   $HOME/.platformio/packages/framework-arduino-avr/libraries/Wire/examples/i2c_scanner/i2c_scanner.ino
 *   $HOME/Library/Arduino15/packages/arduino/hardware/avr/1.8.6/libraries/Wire/examples/i2c_scanner/i2c_scanner.ino
 *
 */

#include <Arduino.h>
#ifdef NRF52840_XXAA
#pragma message("NRF52840_XXAA IS DEFINED")
#include "utilities.h"
#include <SPI.h>
#endif
#include <Wire.h>

void printAddress(
    const __FlashStringHelper *prefix,
    uint8_t address,
    const __FlashStringHelper *suffix)
{
    Serial.print(prefix);
    Serial.print("0x");
    if (address < 16)
        Serial.print("0");
    Serial.print(address, HEX);
    Serial.print(suffix);
}

void readWhoIAmRegister(uint8_t address)
{
    Wire.write(0x75);
    Wire.endTransmission(false);
    Wire.requestFrom(static_cast<int>(address), 1);
    if (!Wire.available())
        return;

    uint8_t whoAmI = Wire.read();
    printAddress(F("    Who am I register:           "), whoAmI, F("\n"));
}

void I2CScanner()
{
    static uint32_t cnt = 0;
    ++cnt;
    Serial.print(F("- - I²C scan count:              "));
    Serial.println(cnt);

    uint8_t device_count = 0;

    for (uint8_t address = 1; address < 127; ++address)
    {
        Wire.beginTransmission(address);
        uint8_t status = Wire.endTransmission();

        if (status == 0)
        {
            printAddress(F("  - I²C address:                 "), address, F("\n"));
                readWhoIAmRegister(address);
            ++device_count;
        }
        else if (status == 4)
        {
            printAddress(F("  - Unknown error at address:    "), address, F("\n"));
        }
    }
    Serial.print(F("  - Number of I²C devices found: "));
    Serial.print(device_count);
    Serial.println(F("\n"));
}

void setupI2C()
{
    Wire.begin();
}

void setupSerial()
{
    Serial.begin(BAUD_RATE);
    while (!Serial.available())
        yield();

    Serial.println(F("\n\n# ##"));
    Serial.println(F("# PROJECT NAME:     I²C SCANNER"));
    Serial.print(F("# FILE NAME:        "));
    Serial.println(__FILE__);
    Serial.print(F("# PROJECT PATH:     "));
    Serial.println(PROJECT_PATH);
    Serial.print(F("# COMPILATION DATE: "));
    Serial.println(COMPILATION_DATE);
    Serial.print(F("# COMPILATION TIME: "));
    Serial.println(COMPILATION_TIME);
    Serial.println(F("# #\n\n"));
}

void setup()
{
    setupSerial();
    setupI2C();
}

void loop()
{
    I2CScanner();
    delay(3000);
}
