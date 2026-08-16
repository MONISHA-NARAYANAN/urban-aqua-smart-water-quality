# Urban Aqua – Smart Residential Water Quality Detection System

## 📌 About the Project

Urban Aqua is an IoT-based smart residential water quality monitoring system designed to monitor water quality in real time.

The system uses an ESP32 microcontroller to collect water quality parameters such as pH, turbidity, and temperature. The collected data is displayed locally through an LCD and remotely monitored using the Blynk IoT platform.

A blockchain-inspired data integrity mechanism is also used to generate SHA-256 hashes and link sensor records to improve data integrity.

## 🎯 Objectives

- Monitor water quality parameters in real time
- Measure pH, turbidity, and temperature
- Display sensor readings on an LCD
- Enable remote monitoring through Blynk IoT
- Detect abnormal water quality conditions
- Improve sensor data integrity using hash-linked records

## 🛠️ Technologies Used

- ESP32
- Embedded C++
- Arduino IDE
- Python
- Blynk IoT
- SHA-256
- IoT Sensors
- I2C LCD

## 🔧 Hardware Components

- ESP32 Development Board
- pH Sensor
- Turbidity Sensor
- DS18B20 Temperature Sensor
- 16×2 I2C LCD
- Connecting Wires
- USB Cable
- Power Supply

## 💻 Software Components

### ESP32

The ESP32 collects sensor readings and processes the data before displaying it on the LCD and sending it to the Blynk IoT platform.

### Blynk IoT

Blynk is used for remote monitoring and real-time visualization of water quality parameters.

### Python Data Integrity Module

Python is used to implement the blockchain-inspired data integrity mechanism. Sensor readings are processed using SHA-256 hashing, with records linked using previous hash values.

## ⚙️ System Workflow

1. Sensors collect water quality data.
2. ESP32 receives the sensor readings.
3. The readings are processed by the ESP32.
4. Temperature, turbidity, and pH values are displayed on the LCD.
5. Data is transmitted through Wi-Fi to the Blynk IoT platform.
6. Sensor data can be monitored remotely.
7. Python generates SHA-256 hashes for data integrity.

## 📂 Repository Contents

```text
├── README.md
├── water_quality_monitor.ino
├── blockchain_data_integrity.py
└── hardware-prototype.png
