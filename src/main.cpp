/**
 * i2c_scanner
 *
 * This is the PlatformIO version of the I²C scanner (i2c_scanner.ino) which is provided in the Arduino IDE examples.
 *
 */

#include <Arduino.h>
#include <Wire.h>

/**
 *
 */
void configure_i2c()
{
    Wire.begin();
}

/**
 *
 */
void configure_serial()
{
    Serial.begin(BAUD_RATE);
    Serial.println(F("\n\n\n# I2C SCANNER\n"));
    Serial.print(F("FILE NAME:        "));
    Serial.println(__FILE__);
    Serial.print(F("PATH:             "));
    Serial.println(PATH);
    Serial.print(F("COMPILATION DATE: "));
    Serial.println(COMPILATION_DATE);
    Serial.print(F("COMPILATION TIME: "));
    Serial.println(COMPILATION_TIME);
    Serial.println("");
}

/**
 *
 */
void setup()
{
    configure_serial();
    configure_i2c();
}

/**
 *
 */
void print_address(uint8_t address)
{
    Serial.print("0x");
    if (address < 16)
    {
        Serial.print("0");
    }
    Serial.println(address, HEX);
}

/**
 *
 */
void loop()
{
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
    delay(5000);
}
