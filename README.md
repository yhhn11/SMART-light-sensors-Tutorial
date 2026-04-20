# SMART-light-sensors-Tutorial
### Low-Cost Digital Instrumentation for Chemical Analysis

This repository provides the software and technical documentation for implementing low-cost digital optical sensors in chemistry laboratory environments. By integrating advanced sensors with Arduino microcontrollers, this project aims to democratize high-precision analytical instrumentation for researchers and students.

## 1. Supported Sensors
The repository contains ready-to-use projects for the following sensors, organized by their optical capabilities:

* **Illuminance & Intensity (Luxmeters):** * `BH1750`: Standard light intensity.
    * `TSL2591`: High Dynamic Range (HDR) sensing.
    * `LTR303`: Light sensing with IR compensation.
* **Colorimetry (RGB):** * `TCS34725`: RGB sensing with integrated IR blocking filter.
* **Spectral Analysis (Low-Cost Spectrophotometry):**
    * `AS7262`: 6-channel visible spectrometer.
    * `AS7341`: 11-channel advanced spectral sensor.
    * `AS7343`: 14-channel multispectral sensor (Visible + NIR).

## 2. Hardware Setup
All sensors communicate via the **I2C Protocol**, requiring only four connections. To ensure hardware safety, please follow this wiring standard:

* **VCC/VIN (Red):** Connect to 5V or 3.3V (Check your sensor module voltage).
* **GND (Black):** Connect to Arduino Ground.
* **SDA (Blue/Green):** Connect to Arduino Pin **A4**.
* **SCL (Yellow/White):** Connect to Arduino Pin **A5**.



## 3. Software Installation
This project is built using **Visual Studio Code (VS Code)** and the **PlatformIO** extension.

1.  **Install VS Code:** Download from [code.visualstudio.com](https://code.visualstudio.com/).
2.  **Install PlatformIO:** Search for "PlatformIO IDE" in the VS Code Extensions Marketplace and install it.
3.  **Open a Project:** * Click the **PlatformIO Icon** (alien head) on the sidebar.
    * Select `PIO Home > Open > Open Project`.
    * Navigate to this repository and select the specific sensor folder you wish to use (e.g., `Sensor_AS7341`).

## 4. Operation: Build and Upload
Once a project is open and your Arduino is connected via USB:

1.  **Build (Checkmark Icon):** Click the checkmark in the bottom status bar to compile the code.
2.  **Upload (Right Arrow Icon):** Click the arrow to flash the firmware to the Arduino.
3.  **Serial Monitor (Plug Icon):** Click the plug icon to view the data in real-time. Set the baud rate to **115200** if prompted.


## 5. Interaction Modes (Switching Methods)
You can choose how the sensor collects data by editing the `void loop()` in the `main.cpp` file. Use the `//` slashes to activate or deactivate a mode:

### Mode A: Continuous Monitoring
The sensor sends data constantly. Ideal for tracking chemical kinetics or stability over time.

### Mode B: On-Demand Acquisition
In this mode, the sensor remains in standby until a manual command is received.

## NOTE: Every time you modify the code—such as switching between modes by adding or removing comments (//)—you must Upload the code again to the Arduino (right arrow icon) for the changes to take effect on the hardware.