/*
 * ==================================================================================
 * PROJECT: Low-Cost Photometric Setup - AS7341 11-Channel Spectral Sensor
 * DESCRIPTION: Advanced Spectral Analysis (F1-F8, NIR, Clear, and Extra)
 * ----------------------------------------------------------------------------------
 * SENSOR CONFIGURATION REFERENCE:
 * ----------------------------------------------------------------------------------
 * 1. ANALOG GAIN (Parameters for as7341.setGain(constant)):
 * Adjusts the sensitivity of the sensor.
 * - AS7341_GAIN_0_5X  | 0.5x Gain
 * - AS7341_GAIN_1X    | 1x Gain (Default)
 * - AS7341_GAIN_2X    | 2x Gain
 * - AS7341_GAIN_4X    | 4x Gain
 * - AS7341_GAIN_8X    | 8x Gain
 * - AS7341_GAIN_16X   | 16x Gain
 * - AS7341_GAIN_32X   | 32x Gain
 * - AS7341_GAIN_64X   | 64x Gain
 * - AS7341_GAIN_128X  | 128x Gain
 * - AS7341_GAIN_256X  | 256x Gain
 * - AS7341_GAIN_512X  | 512x Gain (Maximum sensitivity)
 *
 * 2. INTEGRATION TIME (Parameters for as7341.setATIME(val) and as7341.setASTEP(val)):
 * Total integration time = (ATIME + 1) * (ASTEP + 1) * 2.78 microseconds.
 * - ATIME: 0 to 255 (Integer)
 * - ASTEP: 0 to 65535 (Integer)
 * - Default: ATIME = 100, ASTEP = 999 (Approx. 280ms)
 *
 * 3. LED CURRENT (Parameters for as7341.setLEDCurrent(value)):
 * Controls the brightness of the built-in LED (4mA to 258mA).
 * - Accepted range: 4 to 258 (Integer)
 * - Higher values increase light intensity for reflectance experiments.
 * ==================================================================================
 */

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_AS7341.h>

// Instantiate the spectral sensor object
Adafruit_AS7341 as7341;

void setup() {
  // Initialize Serial Communication at 115200 Baud Rate
  Serial.begin(115200);

  // Initialize the AS7341 sensor
  if (as7341.begin()) {
      Serial.println(F("AS7341 Spectrometer Initialized Successfully."));
  } else {
      Serial.println(F("AS7341 not found. Check I2C wiring (A4/A5)."));
      while (1);
  }

  //SENSOR CALIBRATION: Adjust gain and integration time based on your sample's transmittance.
  as7341.setGain(AS7341_GAIN_16X);
  as7341.setATIME(100);
  as7341.setASTEP(999);


  //LED CONFIGURATION: Uncomment the two lines below by removing the '//' slashes to enable the internal LED for reflectance measurements.
  // as7341.setLEDCurrent(4); // Set LED current to 4mA (minimum)
  // as7341.enableLED(true);  // Turn ON the internal white LED
}

void loop() {
  // Read data from all channels simultaneously
  if (as7341.readAllChannels()) {
      
      // Output spectral data labeled by their respective center wavelengths
      Serial.print(F("F1(415nm): ")); Serial.print(as7341.getChannel(AS7341_CHANNEL_415nm_F1));
      Serial.print(F(" | F2(445nm): ")); Serial.print(as7341.getChannel(AS7341_CHANNEL_445nm_F2));
      Serial.print(F(" | F3(480nm): ")); Serial.print(as7341.getChannel(AS7341_CHANNEL_480nm_F3));
      Serial.print(F(" | F4(515nm): ")); Serial.print(as7341.getChannel(AS7341_CHANNEL_515nm_F4));
      Serial.print(F(" | F5(555nm): ")); Serial.print(as7341.getChannel(AS7341_CHANNEL_555nm_F5));
      Serial.print(F(" | F6(590nm): ")); Serial.print(as7341.getChannel(AS7341_CHANNEL_590nm_F6));
      Serial.print(F(" | F7(630nm): ")); Serial.print(as7341.getChannel(AS7341_CHANNEL_630nm_F7));
      Serial.print(F(" | F8(680nm): ")); Serial.print(as7341.getChannel(AS7341_CHANNEL_680nm_F8));
      Serial.print(F(" | NIR: "));       Serial.print(as7341.getChannel(AS7341_CHANNEL_NIR));
      Serial.print(F(" | Clear: "));     Serial.println(as7341.getChannel(AS7341_CHANNEL_CLEAR));
  }

  // Sampling interval
  delay(1000);
}