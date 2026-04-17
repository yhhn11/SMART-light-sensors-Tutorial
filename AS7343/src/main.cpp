/*
 * ==================================================================================
 * PROJECT: Low-Cost Photometric Setup - AS7343 14-Channel Spectral Sensor
 * DESCRIPTION: High-Resolution Multi-Spectral Analysis for Laboratory Applications
 * ----------------------------------------------------------------------------------
 * SENSOR CONFIGURATION REFERENCE:
 * ----------------------------------------------------------------------------------
 * 1. GAIN (Parameters for as7343.setGain(constant)):
 * Adjusts sensitivity. Higher gain is ideal for low-light or high-absorbance samples.
 * - AS7343_GAIN_0_5X   | 0.5x gain
 * - AS7343_GAIN_1X     | 1x gain
 * - AS7343_GAIN_2X     | 2x gain
 * - AS7343_GAIN_4X     | 4x gain
 * - AS7343_GAIN_8X     | 8x gain
 * - AS7343_GAIN_16X    | 16x gain
 * - AS7343_GAIN_32X    | 32x gain
 * - AS7343_GAIN_64X    | 64x gain
 * - AS7343_GAIN_128X   | 128x gain
 * - AS7343_GAIN_256X   | 256x gain (Default)
 * - AS7343_GAIN_512X   | 512x gain
 * - AS7343_GAIN_1024X  | 1024x gain
 * - AS7343_GAIN_2048X  | 2048x gain (Maximum sensitivity)
 *
 * 2. INTEGRATION TIME (ATIME/ASTEP):
 * Total Integration Time = (ATIME + 1) * (ASTEP + 1) * 2.78 microseconds.
 * - ATIME: 0 to 255 (Integer)
 * - ASTEP: 0 to 65535 (Integer)
 * - Default setup: ATIME = 100, ASTEP = 999 (Approx. 280ms)
 *
 * 3. LED CURRENT (Parameters for as7343.setLEDCurrent(value)):
 * Controls the current (and thus brightness) of the built-in LED.
 * - Accepted range: 4 to 258 (Integer representing mA)
 * ==================================================================================
 */

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_AS7343.h>

// Instantiate the spectral sensor object
Adafruit_AS7343 as7343;

// Buffer to store the 14 spectral channel readings
uint16_t readings[14];

void setup() {
    // Initialize Serial Communication at 115200 Baud Rate
    Serial.begin(115200);

    // Initialize the AS7343 sensor
    if (as7343.begin()) {
        Serial.println(F("AS7343 Spectrometer Initialized Successfully."));
    } else {
        Serial.println(F("AS7343 not found. Check I2C wiring (A4/A5)."));
        while (1);
    }

    //SENSOR CALIBRATION: Adjust gain and integration time based on your experimental requirements. 
    as7343.setGain(AS7343_GAIN_128X);
    as7343.setATIME(100);
    as7343.setASTEP(999);

    //LED CONFIGURATION: Uncomment the two lines below by removing the '//' slashes to enable the internal LED for reflectance measurements.
    // as7343.setLEDCurrent(4); // Set LED current to 4mA
    // as7343.enableLED(true);  // Turn ON the internal white LED

}

void loop() {
    // Attempt to read data from all channels into the buffer
    if (as7343.readAllChannels(readings)) {
        
        Serial.println(F("\n--- Spectral Readings ---"));

        // Printing channels in wavelength order as per library documentation
        Serial.print(F("F1 (405nm violet):     ")); Serial.println(readings[AS7343_CHANNEL_F1]);
        Serial.print(F("F2 (425nm violet-blue):")); Serial.println(readings[AS7343_CHANNEL_F2]);
        Serial.print(F("FZ (450nm blue):       ")); Serial.println(readings[AS7343_CHANNEL_FZ]);
        Serial.print(F("F3 (475nm blue-cyan):  ")); Serial.println(readings[AS7343_CHANNEL_F3]);
        Serial.print(F("F4 (515nm green):      ")); Serial.println(readings[AS7343_CHANNEL_F4]);
        Serial.print(F("F5 (550nm green-yel):  ")); Serial.println(readings[AS7343_CHANNEL_F5]);
        Serial.print(F("FY (555nm yellow-grn): ")); Serial.println(readings[AS7343_CHANNEL_FY]);
        Serial.print(F("FXL(600nm orange):     ")); Serial.println(readings[AS7343_CHANNEL_FXL]);
        Serial.print(F("F6 (640nm red):        ")); Serial.println(readings[AS7343_CHANNEL_F6]);
        Serial.print(F("F7 (690nm deep red):   ")); Serial.println(readings[AS7343_CHANNEL_F7]);
        Serial.print(F("F8 (745nm near-IR):    ")); Serial.println(readings[AS7343_CHANNEL_F8]);
        Serial.print(F("NIR(855nm near-IR):    ")); Serial.println(readings[AS7343_CHANNEL_NIR]);
        Serial.print(F("VIS (clear):           ")); Serial.println(readings[AS7343_CHANNEL_VIS_TL_0]);
    }

    // Standard 1-second sampling delay
    delay(1000);
}