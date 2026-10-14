# 🌱 AgriShield: IoT Smart Agriculture & Security Hub

AgriShield is an automated, dual-core smart agriculture and crop protection system powered by an **ESP32-WROOM** micro-controller hub and an **AI-Thinker ESP32-CAM** security module. It combines automated crop irrigation, real-time tank level monitoring, and intelligent motion-triggered intrusion detection into a compact, low-cost hardware solution.

---

## 🚀 Key Features

* **Automated Irrigation System:** Continuously monitors soil moisture and weather conditions (via a rain sensor) to toggle an automated water pump relay.
* **Smart Water Tank Monitoring:** Uses an HC-SR04 ultrasonic distance sensor to calculate and display water reservoir levels in real time.
* **Intrusion Detection & Visual Capture:** Integrates a PIR motion sensor to detect trespassers, sounding an audible/visual alarm while simultaneously triggering the ESP32-CAM over UART to snap a photographic capture.
* **Local LCD Feedback Hub:** Features a 16x2 I2C Liquid Crystal Display providing instant system status, moisture levels, and warning notifications without needing constant serial monitor access.

---

## 🛠️ Hardware Components

* **Main Microcontroller:** ESP32-WROOM (HW-463 breakout board with CP2102 USB-to-UART bridge)
* **Camera Module:** AI-Thinker ESP32-CAM (OV2640 lens) + FTDI Programmer for initial flashing
* **Sensors:**
  * Capacitive Soil Moisture Sensor (Analog)
  * Rain Sensor Module (Digital)
  * HC-SR04 Ultrasonic Sensor
  * PIR Motion Sensor
* **Actuators & Output:**
  * 5V 1-Channel Relay Module (Water pump interface)
  * 16x2 I2C LCD Display
  * Active Buzzer & Status LEDs (Red/Green)
* **Power:** Laptop-powered via USB (5V VIN & 3.3V rails)

---

## 📐 Pin Mapping Architecture

### Main ESP32 Hub Connections
| Component | Component Pin | ESP32 Pin (`D` Label) |
| :--- | :--- | :--- |
| **Soil Moisture Sensor** | AO | `D34` |
| **Rain Sensor** | DO | `D33` |
| **Ultrasonic (HC-SR04)** | Trig / Echo | `D26` (Trig) / `D27` (Echo) |
| **PIR Motion Sensor** | OUT | `D25` |
| **ESP32-CAM Link** | TX / RX | `D16` (RX2) / `D17` (TX2) |
| **I2C LCD Display** | SDA / SCL | `D21` (SDA) / `D22` (SCL) |
| **Alarm Buzzer** | Positive (+) | `D23` (via 220Ω resistor) |
| **Red LED (Intrusion)** | Anode (+) | `D13` (via 220Ω resistor) |
| **Green LED (Status)** | Anode (+) | `D4` (via 220Ω resistor) |
| **Relay Module** | IN (Signal) | `D32` |

---

## 📂 Codebase Structure

The project code is divided into two firmware sketches:
1. **`main_hub.ino`**: Uploaded to the primary ESP32-WROOM board; handles sensor polling, LCD updates, irrigation logic, and serial command dispatching.
2. **`esp32_cam.ino`**: Flashed once via an FTDI adapter to the ESP32-CAM module; listens for UART trigger signals to capture frame buffers.

---

## ⚙️ Getting Started & Installation

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/your-username/AgriShield.git
   ```
2. **Install Dependencies:**
   * Open Arduino IDE and install the **ESP32 Board Manager** via Preferences.
   * Install the **`LiquidCrystal_I2C`** library by Frank de Brabander via the Library Manager.
3. **Flash the Firmware:**
   * Connect your ESP32-WROOM via USB, select **ESP32 Dev Module**, choose your assigned COM port (Silicon Labs CP210x driver required), and upload `main_hub.ino`.
   * Flash `esp32_cam.ino` to your ESP32-CAM using a 5V FTDI programmer with GPIO 0 jumpered to GND.
4. **Wire the Circuit:** Reference the pin mapping table above to assemble your breadboard prototype.

---

## 📄 License
This project is open-source and available under the [MIT License](LICENSE).
