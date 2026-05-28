# Smart-Light-MQTT-NodeMCU
# Smart Light + MQTT Peer-to-Peer System

An IoT project using two ESP8266 NodeMCU modules to demonstrate ADC reading, threshold control, and MQTT Publish/Subscribe communication using a public HiveMQ broker.

## Project Architecture
- **Kit 1 (Publisher):** Reads ambient light via an LDR module. If the light drops below the threshold, it triggers a local LED and publishes an `ON` status to the MQTT broker.
- **Kit 2 (Subscriber):** Subscribes to the MQTT broker. It mirrors the state of Kit 1 by turning two remote LEDs on or off in real-time.

---

## Hardware Connections

### Kit 1: Publisher (Sensor Node)
| Component | NodeMCU Pin |
| :--- | :--- |
| **LDR Module VCC** | 3V3 |
| **LDR Module GND** | GND |
| **LDR Module AO** | A0 |
| **LED 1 Anode (+)**| D1 (via 220Ω Resistor) |
| **LED 1 Cathode (-)**| GND |

### Kit 2: Subscriber (Actuator Node)
| Component | NodeMCU Pin |
| :--- | :--- |
| **LED 2 Anode (+)**| D1 (via 220Ω Resistor) |
| **LED 2 Cathode (-)**| GND |
| **LED 3 Anode (+)**| D2 (via 220Ω Resistor) |
| **LED 3 Cathode (-)**| GND |

---

## Software Dependencies
Before uploading the code via the Arduino IDE, ensure you have installed:
1. **ESP8266 Board Core**
2. **PubSubClient Library** (by Nick O'Leary)

> ⚠️ **Setup Note:** Remember to change `YOUR_WIFI_SSID`, `YOUR_WIFI_PASSWORD`, and use a unique `mqtt_topic` in both `.ino` files before flashing your devices.
