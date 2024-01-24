# ESP32 MQTT Servo Control

## Project Overview

This project enables communication between an ESP32, a client dashboard, and a servo motor for controlling a volet roulant (rolling shutter). Real-time data is sent to an MQTT broker via Wi-Fi, and the data is displayed in real-time on the dashboard.
![Dashboard](https://github.com/alaeddineth/SmartHome-ESP32-Servo-MQTT/assets/50785652/4f135025-056f-4ffd-b2ed-5d2fcac2332d)

## Table of Contents

- [Dependencies](#dependencies)
- [Setup and Installation](#setup-and-installation)
- [Usage](#usage)
- [MQTT Broker Configuration](#mqtt-broker-configuration)
- [Contributing](#contributing)
- [License](#license)

## Dependencies

- [Arduino IDE](https://www.arduino.cc/en/software)
- [Library Name and Version](Link to the library documentation)

## Setup and Installation

1. Clone this repository:

   ```bash
   git clone https://github.com/your-username/esp32-mqtt-servo-control.git

2. Open the Arduino IDE and load the sketch located in the src folder.

3.Install the required libraries using the Arduino Library Manager.
4. Upload the sketch to your ESP32.
## Usage

1. Connect the ESP32 to your Wi-Fi network.

2. Configure the MQTT broker settings in the sketch.

    ```cpp
    // MQTT Broker Configuration
    #define MQTT_BROKER "your_mqtt_broker_address"
    #define MQTT_PORT 1883
    #define MQTT_USER "your_mqtt_username"
    #define MQTT_PASSWORD "your_mqtt_password"
    ```

3. Power on the servo motor.

4. Install and run Mosquitto (MQTT broker):

   - Follow the installation instructions for your operating system from the [Mosquitto website](https://mosquitto.org/download/).
   - Start the Mosquitto broker.

     ```bash
         mosquitto_sub -t "topic" -h "mqtt_broker_host"

     ```

5. Install Node.js for real-time communication with Socket.IO:

   - Follow the installation instructions for your operating system from the [Node.js website](https://nodejs.org/).
   - Verify the installation:

     ```bash
     node -v
     npm -v
     ```

6. Install project dependencies:

   ```bash
   cd path/to/your/project
   npm install

7.node server.js
8.Open a web browser and navigate to http://localhost:3000.

The dashboard should be accessible at this address, provided that the server is running and configured correctly.
