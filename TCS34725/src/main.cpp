/*
 * ==================================================================================
 * PROJECT: Low-Cost Photometric Setup - TCS34725 Sensor
 * DESCRIPTION: RGB Color Sensing with Integrated IR Filter for Chemical Analysis
 * ----------------------------------------------------------------------------------
 * SENSOR CONFIGURATION REFERENCE:
 * ----------------------------------------------------------------------------------
 * 1. INTEGRATION TIME (Parameters for tcs.setIntegrationTime()):
 * Defines the exposure duration. Longer times increase resolution but may lead 
 * to sensor saturation under bright light.
 * - TCS34725_INTEGRATIONTIME_2_4MS  | 2.4ms  | Max Count: 1024
 * - TCS34725_INTEGRATIONTIME_24MS   | 24ms   | Max Count: 10240
 * - TCS34725_INTEGRATIONTIME_50MS   | 50ms   | Max Count: 20480
 * - TCS34725_INTEGRATIONTIME_101MS  | 101ms  | Max Count: 43008
 * - TCS34725_INTEGRATIONTIME_154MS  | 154ms  | Max Count: 65535
 * - TCS34725_INTEGRATIONTIME_700MS  | 700ms  | Max Count: 65535 (Highest Resolution)
 *
 * 2. ANALOG GAIN (Parameters for tcs.setGain()):
 * Amplifies the signal. Useful for dark solutions or low-light reactions.
 * - TCS34725_GAIN_1X  | No amplification (Standard)
 * - TCS34725_GAIN_4X  | 4x Gain
 * - TCS34725_GAIN_16X | 16x Gain
 * - TCS34725_GAIN_60X | 60x Gain (Maximum sensitivity)
 * ==================================================================================
 */

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_TCS34725.h>

// Instantiate the sensor object
Adafruit_TCS34725 tcs = Adafruit_TCS34725();

void setup() {
    // Initialize Serial Communication at 115200 Baud Rate
    Serial.begin(115200);

    // Initialize the TCS34725 sensor
    if (tcs.begin()) {
        Serial.println(F("TCS34725 Initialized Successfully."));
    } else {
        Serial.println(F("No TCS34725 found. Check wiring and I2C address."));
        while (1); // Stop execution
    }

    /*
     * SENSOR CALIBRATION
     * Adjust these based on the transmittance/reflectance of your sample.
    */
    tcs.setIntegrationTime(TCS34725_INTEGRATIONTIME_154MS);
    tcs.setGain(TCS34725_GAIN_4X);

    Serial.println(F("Configured: Gain = 4X, Integration Time = 154ms"));
}

void loop() {
    uint16_t r, g, b, c, colorTemp, lux;

    // Read the raw values from the sensor (Red, Green, Blue, Clear)
    tcs.getRawData(&r, &g, &b, &c);

    // Calculate standardized values using Adafruit's internal algorithms
    colorTemp = tcs.calculateColorTemperature(r, g, b);
    lux = tcs.calculateLux(r, g, b);

    // Output data to Serial Monitor in a format easy to copy to Excel/CSV
    Serial.print(F("R: ")); Serial.print(r);
    Serial.print(F(" G: ")); Serial.print(g);
    Serial.print(F(" B: ")); Serial.print(b);
    Serial.print(F(" C: ")); Serial.print(c);
    Serial.print(F(" | Temp: ")); Serial.print(colorTemp); Serial.print(F("K"));
    Serial.print(F(" | Lux: ")); Serial.println(lux);

    // Wait 1 second between readings
    delay(1000);
}