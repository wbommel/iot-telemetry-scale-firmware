# IoT Telemetry Scale Firmware

🚀 Firmware for ESP8266/ESP32-based wireless telemetry scales, designed to read weight data from an HX711 sensor and publish it over MQTT.  
This project is part of the [IoT Telemetry Scale Project](https://github.com/wbommel/iot-telemetry-scale), a modular system for remote weight sensing and monitoring.

---

> ⚠️ **Disclaimer**
> 
> This project is the result of personal experimentation and learning. I am a hobbyist and not a certified electronics engineer, nor an expert in load cell calibration or metrology.
> 
> While the system works well in my own setup (and with budgies 🐦!), it may require adaptation, validation, and care before use in other environments—especially in critical or commercial applications.
> 
> Please review all schematics, firmware, and configuration settings carefully before use. I welcome contributions, feedback, and improvements from the community!

---

## ✨ Features

- 📦 Supports HX711 load cells
- 🌐 Publishes real-time weight data via MQTT
- ⚙️ Heartbeat and diagnostics topics for system health
- 📉 Configurable thresholds for event-based actions
- 📡 Remote commands via MQTT (tare, calibrate, etc.)
- 🧠 Designed for ESP8266 (ESP-12E/F); adaptable to ESP32
- 💾 Lightweight and easy to deploy

---

## 🧰 Getting Started

### ✅ Hardware Requirements

- ESP8266 or ESP32 microcontroller (NodeMCU, D1 mini, etc.)
- HX711 module
- Load cell (any standard strain gauge)
- Optional: Custom PCB ([iot-telemetry-scale-hardware](https://github.com/wbommel/iot-telemetry-scale-hardware))

### ⚙️ Software Setup

1. Clone the repo:

   ```bash
   git clone https://github.com/wbommel/iot-telemetry-scale-firmware.git
   cd iot-telemetry-scale-firmware

2. Open preferably in PlatformIO.

3. Install required libraries:
  * PubSubClient
  * HX711
  * ESP8266WiFi or WiFi (depending on board) (PlatformIO detects the board type by compiler conditions)

4. Create private_config.ini in the root folder (file is ignored via gitignore) (commented template file provided)

5. Flash the firmware to your microcontroller.

### ⚖️ Calibrating the scale

### 📡 MQTT Topics

Topic | Example Payload | Description
|--|--|--|
<configured client id>/weight | 23.5 | calculated weight (raw_reading/Calibration Value)
<configured client id>/raw_reading | 250873 | raw output of the hx711 to be able to manually calculate a calibration value
<configured client id>/heartbeat | online | Sent every 30 seconds
<configured client id>/tare | . | tare command (payload irrelevant)
<configured client id>/calibrate | . | calibrate command (payload irrelevant)

### 🧩 Related Repositories

iot-telemetry-scale – Meta project hub

iot-telemetry-scale-hardware – KiCad PCB design

iot-telemetry-scale-housing – FreeCAD STL models for enclosures

iot-telemetry-scale-streamer – MJPEG streaming & image capture

iot-telemetry-scale-ui – Web-based GUI (NiceGUI) for managing individuals & weights

### 🪪 License
This project is licensed under the MIT License.

---

> Designed with ❤️ to help animals and those who care for them — now open to all creative uses.
