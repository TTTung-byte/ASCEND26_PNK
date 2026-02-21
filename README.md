# ASCEND26_PNK
- ESP32 Multi-Sensor Environmental Monitoring with LoRa

This project uses an ESP32 to collect data from multiple sensors and transmit it wirelessly using LoRa. It is suitable for IoT learning, environmental monitoring, and smart city / smart agriculture projects.

- Features

- Measure temperature & humidity (DHT22)

- Detect air quality (MQ135)

- Get GPS location (latitude & longitude)

- Read acceleration data (MPU6050)

- Transmit all data via LoRa (433 MHz)

- Display real-time data on Serial Monitor

- Hardware Required

ESP32 Development Board

DHT22 Temperature & Humidity Sensor

MQ135 Air Quality Sensor

MPU6050 Accelerometer/Gyroscope

GPS Module (UART)

LoRa SX1278 / SX1276 Module (433 MHz)

Antenna for LoRa

Jumper wires

- Pin Connections
DHT22
Sensor	ESP32
DATA	GPIO 4
MQ135
Sensor	ESP32
AO	GPIO 34
GPS (UART2)
GPS	ESP32
TX	GPIO 16
RX	GPIO 17
MPU6050 (I2C)
MPU6050	ESP32
SDA	GPIO 21
SCL	GPIO 22
LoRa Module
LoRa	ESP32
NSS (SS)	GPIO 18
RST	GPIO 14
DIO0	GPIO 26
SCK	GPIO 5
MISO	GPIO 19
MOSI	GPIO 27
- Required Libraries

Install these libraries from Arduino Library Manager:

DHT sensor library

Adafruit Unified Sensor

MPU6050

TinyGPSPlus

LoRa

SPI

Wire

- How It Works

ESP32 reads data from all sensors every 3 seconds

GPS data is validated before use

Sensor values are printed to Serial Monitor

All data is packed into a single string

Data is transmitted via LoRa

- Example LoRa Data Packet
T=28.5,H=70.2,MQ=412,LAT=10.762622,LNG=106.660172,AX=120,AY=-32,AZ=16384
Serial Monitor Output
=== DATA ===
Nhiet do: 28.5 °C
Do am: 70.2 %
MQ135: 412
GPS: 10.762622, 106.660172
Accel X/Y/Z: 120 / -32 / 16384
Da gui LoRa 📡
- Applications

Environmental monitoring

Smart agriculture

Disaster warning systems

IoT & embedded systems education

Science fair / STEM projects

- Notes

Ensure the LoRa frequency (433 MHz) matches your module and local regulations

GPS may need clear sky to get valid coordinates

MQ135 values are raw ADC values, not ppm (calibration required)

- License

This project is open-source and free to use for educational and non-commercial purposes.
