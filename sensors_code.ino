#include <WiFi.h>
#include <HTTPClient.h>

// -------- Pins --------
#define LM35_PIN 33
#define MQ135_PIN 34
#define MQ7_PIN 35
#define DUST_PIN 32
#define DUST_LED 4

// -------- WiFi --------
const char* ssid = "Wifi_name";  //name of the wifi you want to connect to (same wifi your device is connected to)
const char* password = "Wifi_pass"; //password of the wifi

// -------- Server --------
String serverName = "Your_IP/data";

void setup() {
  Serial.begin(115200);
  pinMode(DUST_LED, OUTPUT);

  WiFi.begin(ssid, password);
  Serial.print("Connecting...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n✅ Connected!");
}

void loop() {

  // -------- Temperature --------
  int lm35Value = analogRead(LM35_PIN);
  float voltage = lm35Value * (3.3 / 4095.0);
  float temperature = voltage * 100;

  // -------- MQ Sensors --------
  int mq135Value = analogRead(MQ135_PIN);
  int mq7Value = analogRead(MQ7_PIN);

  float nh3 = (mq135Value / 4095.0) * 15;
  float co = (mq7Value / 4095.0) * 10;
  float benzene = (mq135Value / 4095.0) * 0.3;

  // -------- PM2.5 (RAW REAL VALUE) --------
  digitalWrite(DUST_LED, LOW);
  delayMicroseconds(280);

  int dustValue = analogRead(DUST_PIN);

  delayMicroseconds(40);
  digitalWrite(DUST_LED, HIGH);
  delayMicroseconds(9680);

  float dustVoltage = dustValue * (3.3 / 4095.0);

  // 👉 REAL VALUE (no forcing)
const float NO_DUST_VOLTAGE = 0.35;

float pm25 = (dustVoltage - NO_DUST_VOLTAGE) * 170;

if (pm25 < 0) pm25 = 0;
  // -------- DEBUG --------
  Serial.println("\n===== REAL SENSOR DATA =====");
  Serial.print("RAW ADC: "); Serial.println(dustValue);
  Serial.print("Voltage: "); Serial.println(dustVoltage);
  Serial.print("PM2.5: "); Serial.println(pm25);

  // -------- JSON --------
  String json = "{";
  json += "\"temperature\":" + String(temperature) + ",";
  json += "\"pm25\":" + String(pm25) + ",";
  json += "\"co\":" + String(co) + ",";
  json += "\"nh3\":" + String(nh3) + ",";
  json += "\"benzene\":" + String(benzene);
  json += "}";

  Serial.println("📤 Sending:");
  Serial.println(json);

  // -------- HTTP --------
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");

    int response = http.POST(json);

    if (response > 0) {
      Serial.println("✅ Sent");
    } else {
      Serial.println("❌ Error");
    }

    http.end();
  }

  delay(5000);
}
