/*
 * ==================================================================================
 * PROJECT: Low-Cost Photometric Setup - AS7262 Visible Spectrometer
 * DESCRIPTION: 6-Channel Spectral Analysis (450nm to 650nm) for Lab Applications
 * ----------------------------------------------------------------------------------
 * SENSOR CONFIGURATION REFERENCE:
 * ----------------------------------------------------------------------------------
 * 1. ANALOG GAIN (Parameters for as726x.setGain()):
 * Amplifies the signal from the photodiodes.
 * - GAIN_1X   | (Default) No amplification
 * - GAIN_3.7X | 3.7x amplification
 * - GAIN_16X  | 16x amplification
 * - GAIN_64X  | 64x amplification (Maximum sensitivity for dark samples)
 *
 * 2. INTEGRATION TIME (Parameters for as726x.setIntegrationTime()):
 * Defines the exposure time. Integration time = <value> * 2.8ms.
 * - Value: 0 to 255 (Integer)
 * - Example: 50 * 2.8ms = 140ms exposure.
 * - Higher values increase resolution but slow down the measurement.
 *
 * 3. MEASUREMENT MODE (Parameters for as726x.setMeasurementMode()):
 * Defines which channels are read and how often.
 * - MODE_0 | Continuous reading of Violet, Blue, Green, Yellow channels
 * - MODE_1 | Continuous reading of Green, Yellow, Orange, Red channels
 * - MODE_2 | (Default) Continuous reading of all 6 channels
 * - ONE_SHOT | One-shot reading of all 6 channels (energy saving)
 * 
 * 4. LED CURRENT LIMIT (Parameters for as726x.setDrvCurrent()):
 * Defines the current for the built-in LED.
 * - LIMIT_12MA5 | 12.5 mA (Default)
 * - LIMIT_25MA  | 25 mA
 * - LIMIT_50MA  | 50 mA
 * - LIMIT_100MA | 100 mA
 * ==================================================================================
 */

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_AS726x.h>

// Instantiate the spectral sensor object
Adafruit_AS726x as726x;

// Buffer to store spectral data (6 channels)
float sensorValues[AS726x_NUM_CHANNELS];

void setup() {
  // Initialize Serial Communication at 115200 Baud Rate
  Serial.begin(115200);

  // Initialize the AS7262 sensor
  if (as726x.begin()) {
      Serial.println(F("AS7262 Spectrometer Initialized Successfully."));
  } else {
      Serial.println(F("AS7262 not found. Check I2C wiring (SDA/SCL)."));
      while (1);
  }

  /*
    * SENSOR CALIBRATION
    * Set gain, integration time, and measurement mode.
  */
  as726x.setGain(GAIN_16X);          // High gain for precision
  as726x.setIntegrationTime(50);           // ~140ms exposure
  as726x.setConversionType(MODE_2); // Read all 6 channels continuously

  // Optional: Turn ON the internal white LED for reflectance measurements (uncomment the two lines below by removing the '//' slashes to enable)
  // as726x.setDrvCurrent(LIMIT_12MA5); 
  // as726x.drvOn();
}

void loop() {
  // Check if the sensor has finished a measurement cycle
  if (as726x.dataReady()) {
      
      // Read calibrated values for all 6 visible channels
      as726x.readCalibratedValues(sensorValues);

      // Print spectral data labeled by color/wavelength
      Serial.print(F("V(450nm): ")); Serial.print(sensorValues[AS726x_VIOLET]);
      Serial.print(F(" | B(500nm): ")); Serial.print(sensorValues[AS726x_BLUE]);
      Serial.print(F(" | G(550nm): ")); Serial.print(sensorValues[AS726x_GREEN]);
      Serial.print(F(" | Y(570nm): ")); Serial.print(sensorValues[AS726x_YELLOW]);
      Serial.print(F(" | O(600nm): ")); Serial.print(sensorValues[AS726x_ORANGE]);
      Serial.print(F(" | R(650nm): ")); Serial.println(sensorValues[AS726x_RED]);
  }

  // Sampling interval
  delay(1000);
}