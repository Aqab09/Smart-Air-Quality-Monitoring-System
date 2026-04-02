#include <WiFi.h>
#include <HTTPClient.h>

#define LM35_PIN 33
#define MQ135_PIN 34
#define MQ7_PIN 35
#define DUST_PIN 32
#define DUST_LED 4

const char* ssid = "AQAB";
const char* password = "aqab1234";

String serverName = "http://192.168.29.224:5000/predict";

void setup() {
  Serial.begin(115200);
  pinMode(DUST_LED, OUTPUT);

  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
}

void loop() {

  // -------- Temperature --------
  int lm35Value = analogRead(LM35_PIN);
  float voltage = lm35Value * (3.3 / 4095.0);
  float temperature = voltage * 100;

  // -------- MQ Sensors --------
  int mq135Value = analogRead(MQ135_PIN);
  int mq7Value = analogRead(MQ7_PIN);

  // -------- PM2.5 --------
  digitalWrite(DUST_LED, LOW);
  delayMicroseconds(280);

  int dustValue = analogRead(DUST_PIN);

  delayMicroseconds(40);
  digitalWrite(DUST_LED, HIGH);
  delayMicroseconds(9680);

  float dustVoltage = dustValue * (3.3 / 4095.0);
  float pm25 = (dustVoltage - 0.1) * 1000;

  if (pm25 < 0) pm25 = 0;

  // -------- Send Data --------
  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;
    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");

    String json = "{";
    json += "\"temperature\":" + String(temperature) + ",";
    json += "\"mq135\":" + String(mq135Value) + ",";
    json += "\"mq7\":" + String(mq7Value) + ",";
    json += "\"pm25\":" + String(pm25);
    json += "}";

    Serial.println("Sending JSON:");
    Serial.println(json);

    int response = http.POST(json);

    if (response > 0) {
      Serial.print("Response Code: ");
      Serial.println(response);

      String payload = http.getString();
      Serial.println("AQI Response: " + payload);
    } else {
      Serial.print("Error: ");
      Serial.println(http.errorToString(response));
    }

    http.end();
  }

  delay(30000);
}
