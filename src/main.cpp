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

void configure_i2c()
{
    Wire.begin();
}

void configure_serial()
{
    Serial.begin(BAUD_RATE);
    // while (!Serial.available())
    //     yield();

    Serial.println("\n\n##########################");
    Serial.println(F("PROJECT NAME:     I2C SCANNER"));
    Serial.print(F("FILE NAME:        "));
    Serial.println(__FILE__);
    Serial.print(F("PROJECT PATH:     "));
    Serial.println(PROJECT_PATH);
    Serial.print(F("COMPILATION DATE: "));
    Serial.println(COMPILATION_DATE);
    Serial.print(F("COMPILATION TIME: "));
    Serial.println(COMPILATION_TIME);
    Serial.print(F("PYTHON VERSION:   "));
    Serial.println(PYTHON_VERSION);
    Serial.print(F("PYTHON PATH:      "));
    Serial.println(PYTHON_PATH);
    Serial.println("##########################\n\n");
}

void print_address(uint8_t address)
{
    Serial.print("0x");
    if (address < 16)
    {
        Serial.print("0");
    }
    Serial.println(address, HEX);
}

void i2c_scanner()
{
    static uint32_t cnt = 0;
    ++cnt;
    Serial.print(F("# "));
    Serial.println(cnt);

    uint8_t device_count = 0;

    Serial.println("Scanning I2C bus...");

    for (uint8_t address = 1; address < 127; ++address)
    {
        Wire.beginTransmission(address);
        uint8_t status = Wire.endTransmission();

        if (status == 0)
        {
            print_address(address);
            ++device_count;
        }
        else if (status == 4)
        {
            Serial.print("Unknown error at address ");
            print_address(address);
        }
    }
    Serial.print("Number of I2C devices found: ");
    Serial.print(device_count);
    Serial.println("\n");
}

void setup()
{
    configure_serial();
    configure_i2c();
}

void loop()
{
    i2c_scanner();
    delay(1000);
}
