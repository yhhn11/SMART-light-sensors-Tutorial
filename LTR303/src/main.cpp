/*
 * ==================================================================================
 * PROJECT: Low-Cost Photometric Setup - LTR303 Sensor
 * DESCRIPTION: Ambient Light Sensing with Infrared Compensation for Lab Applications
 * ----------------------------------------------------------------------------------
 * SENSOR CONFIGURATION REFERENCE:
 * ----------------------------------------------------------------------------------
 * 1. ANALOG GAIN (Parameters for ltr.setGain()):
 * Adjusts the sensor's sensitivity. Higher gain is better for low light.
 * - LTR3XX_GAIN_1  | (Default) Standard lighting conditions
 * - LTR3XX_GAIN_2  |
 * - LTR3XX_GAIN_4  |
 * - LTR3XX_GAIN_8  |
 * - LTR3XX_GAIN_48 | High sensitivity for low light
 * - LTR3XX_GAIN_96 | Maximum sensitivity
 *
 * 2. INTEGRATION TIME (Parameters for ltr.setIntegrationTime()):
 * The time the sensor spends collecting light for a single reading.
 * - LTR3XX_INTEGTIME_50   | 50ms (Fastest)
 * - LTR3XX_INTEGTIME_100  | 100ms (Default)
 * - LTR3XX_INTEGTIME_150  | 150ms
 * - LTR3XX_INTEGTIME_200  | 200ms
 * - LTR3XX_INTEGTIME_250  | 250ms
 * - LTR3XX_INTEGTIME_300  | 300ms
 * - LTR3XX_INTEGTIME_350  | 350ms
 * - LTR3XX_INTEGTIME_400  | 400ms (Highest resolution)
 *
 * 3. MEASUREMENT RATE (Parameters for ltr.setMeasurementRate()):
 * Defines how often the sensor performs a measurement.
 * - LTR3XX_MEASRATE_50    | 50ms
 * - LTR3XX_MEASRATE_100   | 100ms (Default)
 * - LTR3XX_MEASRATE_200   | 200ms
 * - LTR3XX_MEASRATE_500   | 500ms
 * - LTR3XX_MEASRATE_1000  | 1000ms
 * - LTR3XX_MEASRATE_2000  | 2000ms
 * ==================================================================================
 */

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_LTR329_LTR303.h>

// Instantiate the sensor object
Adafruit_LTR303 ltr = Adafruit_LTR303();

void setup() {
    // Initialize Serial Communication at 115200 Baud Rate
    Serial.begin(115200);

    // Initialize the LTR303 sensor
    if (ltr.begin()) {
        Serial.println(F("LTR303 Initialized Successfully."));
    } else {
        Serial.println(F("Sensor not found. Check VCC, GND, SDA, and SCL."));
        while (1); // Halt execution
    }

    /*
     * SENSOR CALIBRATION
     * Adjust these parameters based on your experiment's light intensity.
    */
    ltr.setGain(LTR3XX_GAIN_1);
    ltr.setIntegrationTime(LTR3XX_INTEGTIME_100);
    ltr.setMeasurementRate(LTR3XX_MEASRATE_500);
}

void loop() {
    uint16_t visible_plus_ir, infrared;

    // Check if new data is available for reading
    if (ltr.newDataAvailable()) {
        // Read both channels (Channel 0: Visible+IR, Channel 1: IR only)
        if (ltr.readBothChannels(visible_plus_ir, infrared)) {
            
            // Calculate an estimate of Visible Light
            int visible_only = visible_plus_ir - infrared;

            // Output raw data to Serial Monitor
            Serial.print(F("CH0 (Vis+IR): ")); Serial.print(visible_plus_ir);
            Serial.print(F(" | CH1 (IR): "));    Serial.print(infrared);
            Serial.print(F(" | Est. Visible: ")); Serial.println(visible_only);
        }
    }

    // Sampling delay (matches or exceeds the measurement rate)
    delay(500);
}