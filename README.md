# IoT Telemetry Scale Firmware

🚀 Firmware for ESP8266/ESP32-based wireless telemetry scales, designed to read weight data from an HX711 sensor and publish it over MQTT.  
This project is part of the [IoT Telemetry Scale Project](https://github.com/wbommel/iot-telemetry-scale), a modular system for remote weight sensing and monitoring.

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

4. Create private_config.ini in the root folder (file is ignored via gitignore) (template file provided)

5. Flash the firmware to your microcontroller.

### 📡 MQTT Topics

Topic | Example Payload | Description
|--|--|--|
iot-scale/weight | 23.5 | Published every second
iot-scale/heartbeat | online | Sent every 30 seconds
iot-scale/command | tare | Remote commands (tare, calibrate)
iot-scale/debug | JSON object | Optional verbose system info

### 💬 Remote Commands
Publish to the iot-scale/command topic to control the scale:

tare – Resets the current weight to zero

calibrate:<value> – Applies a calibration factor (e.g. calibrate:437)

Example:

```bash
  mosquitto_pub -h 192.168.1.100 -t "iot-scale/command" -m "tare"
```

### 📁 Project Structure

```bash
📁 src/
├── main.cpp            # Firmware main logic
├── config.h            # User-specific WiFi & MQTT settings
├── scale_logic.h       # HX711 handling and utilities
```

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
