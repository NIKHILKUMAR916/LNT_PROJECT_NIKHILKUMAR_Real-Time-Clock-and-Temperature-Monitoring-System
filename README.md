# Real-Time Clock and Temperature Monitoring System

## Overview
This project monitors temperature using a DS18B20 sensor while displaying the current date and time from a DS1307 RTC module on an SSD1306 OLED display. A warning is generated when the temperature exceeds a predefined threshold.

## Features
- Real-time clock display
- Temperature monitoring
- OLED display
- High-temperature alert
- Wokwi simulation
- ESP32 based implementation

## Components
- ESP32 DevKit V1
- DS1307 RTC
- DS18B20 Temperature Sensor
- SSD1306 OLED Display
- 4.7kΩ Pull-up Resistor

## Software
- Arduino IDE
- Wokwi Simulator

## Connections

OLED
- SDA → GPIO21
- SCL → GPIO22

RTC
- SDA → GPIO21
- SCL → GPIO22

DS18B20
- DQ → GPIO4
- 4.7kΩ pull-up resistor to 3.3V

## Future Improvements
- Wi-Fi monitoring
- Blynk integration
- ThingSpeak cloud logging
- Buzzer alert
