/*
 * ==================================================================================
 * PROJECT: Low-Cost Photometric Setup - TSL2591 Sensor
 * DESCRIPTION: High Dynamic Range Digital Light Sensing for Laboratory Applications
 * ----------------------------------------------------------------------------------
 * SENSOR CONFIGURATION REFERENCE:
 * ----------------------------------------------------------------------------------
 * 1. ANALOG GAIN (Parameters for tsl.setGain()):
 * Adjusts the sensitivity of the internal photodiodes.
 * - TSL2591_GAIN_LOW  | 1x Gain  | For very bright light (prevents saturation)
 * - TSL2591_GAIN_MED  | 25x Gain | (Default) Standard laboratory lighting
 * - TSL2591_GAIN_HIGH | 428x Gain| For low light conditions
 * - TSL2591_GAIN_MAX  | 9876x Gain| For near-darkness or weak luminescence
 * 
 * 2. INTEGRATION TIME (Parameters for tsl.setTiming()):
 * Defines the exposure time for each reading. Longer times increase precision 
 * and sensitivity but slow down the sampling rate.
 * - TSL2591_INTEGRATIONTIME_100MS | (Default) Fastest sampling
 * - TSL2591_INTEGRATIONTIME_200MS |
 * - TSL2591_INTEGRATIONTIME_300MS |
 * - TSL2591_INTEGRATIONTIME_400MS |
 * - TSL2591_INTEGRATIONTIME_500MS |
 * - TSL2591_INTEGRATIONTIME_600MS | Slowest sampling, highest sensitivity
 * ==================================================================================
 */

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2591.h>

// Instantiate the sensor object
Adafruit_TSL2591 tsl = Adafruit_TSL2591(2591); // Pass ID 2591 for reference

void setup() {
    // Initialize Serial Communication at 115200 Baud Rate
    Serial.begin(115200);

    // Initialize the TSL2591 sensor
    if (tsl.begin()) {
        Serial.println(F("TSL2591 Initialized Successfully."));
    } else {
        Serial.println(F("Sensor not found. Check VCC, GND, SDA, and SCL."));
        while (1);
    }

    /*
     * SENSOR CALIBRATION
     * Based on your light source intensity, select the appropriate Gain and Timing.
    */
    tsl.setGain(TSL2591_GAIN_MED);
    tsl.setTiming(TSL2591_INTEGRATIONTIME_100MS);

    Serial.println(F("Configured: Gain = Medium (25x), Time = 100ms"));
}

void loop() {
    // Simple reading: returns 32-bit combined value (Full Spectrum | Infrared)
    uint32_t lum = tsl.getFullLuminosity();
    uint16_t ir = lum >> 16;      // Extract Infrared
    uint16_t full = lum & 0xFFFF; // Extract Full Spectrum (Visible + IR)
    
    // Calculate visible light by subtracting IR from Full Spectrum
    uint16_t visible = full - ir;

    // Calculate Lux (Standardized Illuminance)
    float lux = tsl.calculateLux(full, ir);

    // Output data to Serial Monitor
    Serial.print(F("Full: "));    Serial.print(full);
    Serial.print(F(" | IR: "));   Serial.print(ir);
    Serial.print(F(" | Visible: ")); Serial.print(visible);
    Serial.print(F(" | LUX: "));  Serial.println(lux);

    // Sampling interval (must be >= selected Integration Time)
    delay(1000);
}