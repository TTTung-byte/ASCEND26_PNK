#include <DHT.h>
#include <Wire.h>
#include <MPU6050.h>
#include <TinyGPSPlus.h>
#include <HardwareSerial.h>
#include <SPI.h>
#include <LoRa.h>

/* -------- DHT22 -------- */
#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

/* -------- MQ135 -------- */
#define MQ135_PIN 34

/* -------- GPS -------- */
TinyGPSPlus gps;
HardwareSerial gpsSerial(2);   // UART2
#define GPS_RX 16
#define GPS_TX 17

/* -------- MPU6050 -------- */
MPU6050 mpu;

/* -------- LoRa -------- */
#define LORA_SS   18
#define LORA_RST  14
#define LORA_DIO0 26
#define LORA_FREQ 433E6

void setup() {
  Serial.begin(115200);

  /* DHT */
  dht.begin();

  /* MQ135 */
  pinMode(MQ135_PIN, INPUT);

  /* GPS */
  gpsSerial.begin(9600, SERIAL_8N1, GPS_RX, GPS_TX);

  /* MPU6050 */
  Wire.begin(21, 22);
  mpu.initialize();

  /* LoRa */
  SPI.begin(5, 19, 27, LORA_SS);
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);

  if (!LoRa.begin(LORA_FREQ)) {
    Serial.println("LoRa loi!");
    while (1);
  }

  Serial.println("ESP32 da san sang 🚀");
}

void loop() {
  /* -------- DHT22 -------- */
  float temp = dht.readTemperature();
  float hum  = dht.readHumidity();

  /* -------- MQ135 -------- */
  int mq135 = analogRead(MQ135_PIN);

  /* -------- GPS -------- */
  while (gpsSerial.available()) {
    gps.encode(gpsSerial.read());
  }

  float lat = gps.location.isValid() ? gps.location.lat() : 0.0;
  float lng = gps.location.isValid() ? gps.location.lng() : 0.0;

  /* -------- MPU6050 -------- */
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);

  /* -------- Serial Monitor -------- */
  Serial.println("=== DATA ===");
  Serial.print("Nhiet do: "); Serial.print(temp); Serial.println(" °C");
  Serial.print("Do am: "); Serial.print(hum); Serial.println(" %");
  Serial.print("MQ135: "); Serial.println(mq135);
  Serial.print("GPS: "); Serial.print(lat, 6); Serial.print(", "); Serial.println(lng, 6);
  Serial.print("Accel X/Y/Z: ");
  Serial.print(ax); Serial.print(" / ");
  Serial.print(ay); Serial.print(" / ");
  Serial.println(az);

  /* -------- Gui LoRa -------- */
  LoRa.beginPacket();
  LoRa.print("T=");   LoRa.print(temp);
  LoRa.print(",H=");  LoRa.print(hum);
  LoRa.print(",MQ="); LoRa.print(mq135);
  LoRa.print(",LAT=");LoRa.print(lat, 6);
  LoRa.print(",LNG=");LoRa.print(lng, 6);
  LoRa.print(",AX="); LoRa.print(ax);
  LoRa.print(",AY="); LoRa.print(ay);
  LoRa.print(",AZ="); LoRa.print(az);
  LoRa.endPacket();

  Serial.println("Da gui LoRa 📡\n");

  delay(3000);
}