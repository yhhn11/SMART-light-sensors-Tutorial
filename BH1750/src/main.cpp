/*
 * ==================================================================================
 * PROJECT: Low-Cost Photometric Setup - BH1750 Sensor
 * DESCRIPTION: Digital Light Intensity Measurement for Laboratory Applications
 * ----------------------------------------------------------------------------------
 * SENSOR CONFIGURATION REFERENCE:
 * ----------------------------------------------------------------------------------
 * 1. MEASUREMENT MODES (Parameters for lightMeter.begin()):
 * These constants define the resolution and frequency of data acquisition.
 * - BH1750::CONTINUOUS_HIGH_RES_MODE   | 1.0 lx resolution | 120ms scan             (Default)
 * - BH1750::CONTINUOUS_HIGH_RES_MODE_2 | 0.5 lx resolution | 120ms scan
 * - BH1750::CONTINUOUS_LOW_RES_MODE    | 4.0 lx resolution | 16ms scan
 * - BH1750::ONE_TIME_HIGH_RES_MODE     | 1.0 lx res (powers down after measurement)
 * - BH1750::ONE_TIME_HIGH_RES_MODE_2   | 0.5 lx res (powers down after measurement)
 * - BH1750::ONE_TIME_LOW_RES_MODE      | 4.0 lx res (powers down after measurement)
 * 
 * 2. SENSITIVITY ADJUSTMENT (MTreg):
 * Use lightMeter.setMTreg(value) to calibrate for extreme lighting.
 * - Accepted Range: 31 to 254 (Integer)
 * - Default Value: 69
 * - Higher values (e.g., 200): Increase sensitivity for very low-light environments.
 * - Lower values (e.g., 32): Decrease sensitivity for high-intensity light sources.
 * ==================================================================================
 */

#include <Arduino.h>
#include <Wire.h>
#include <BH1750.h>

// Instantiate the sensor object
BH1750 lightMeter;

void setup() {
    // Initialize Serial Communication at 115200 Baud Rate
    Serial.begin(115200);

    // Initialize I2C Bus (A4 = SDA, A5 = SCL)
    Wire.begin();

    /*
     * SENSOR INITIALIZATION
     * Parameters: Select one mode from the table above.
     * Example: BH1750::CONTINUOUS_HIGH_RES_MODE
     */
    bool status = lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE);

    if (status) {
        Serial.println(F("BH1750 Initialized Successfully."));
    } else {
        Serial.println(F("Initialization Error. Check wiring (VCC, GND, SDA, SCL)."));
        while (1); // Halt execution if sensor is not found
    }

    /*
     * OPTIONAL: SENSITIVITY ADJUSTMENT
     * Change the value on the line below to change sensitivity (Value range: 31 - 254)
    */
    lightMeter.setMTreg(69); 
}

void loop() {
    // Acquire light intensity level in Lux (lx)
    float lux = lightMeter.readLightLevel();

    // Output data to Serial Monitor
    Serial.print(F("Illuminance: "));
    Serial.print(lux);
    Serial.println(F(" lx"));

    // Sampling interval: 1000 milliseconds (1 second)
    delay(1000);
}