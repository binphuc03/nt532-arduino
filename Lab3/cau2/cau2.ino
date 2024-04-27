#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Wire.h>
#include <BH1750.h>
#include <ArduinoJson.h>

#define TRIGGER_PIN D6  // Chân Trigger của cảm biến khoảng cách
#define ECHO_PIN D7     // Chân Echo của cảm biến khoảng cách

char ssid[] = "UiTiOt-E3.1";
char password[] = "UiTiOtAP";
const char* serverUrl = "http://192.168.31.230:3000/sensor-data"; // Thay đổi địa chỉ server thành địa chỉ ip của máy

BH1750 lightMeter;
int ledPins[3] = {D3, D4, D5};

void setup() {
  Serial.begin(115200);
  Wire.begin(); // Khởi động I2C cho cảm biến ánh sáng
  lightMeter.begin(); // Khởi động cảm biến ánh sáng

  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  for (int i = 0; i < 3; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }
 // Kết nối với Wi-Fi
  WiFi.begin(ssid, password);
  
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
  Serial.println("IP Address: " + WiFi.localIP().toString());

}

void loop() {
  float light_value = lightMeter.readLightLevel();
  long Duration, Distance_Value;
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  Duration = pulseIn(ECHO_PIN, HIGH);
  Distance_Value = (Duration/2) / 29.1;

 // Tạo payload JSON
  DynamicJsonDocument json(128);
  json["light"] = light_value;
  json["distance"] = Distance_Value;

  // Gửi yêu cầu POST đến server
  WiFiClient client;
  HTTPClient http;

  if (http.begin(client, serverUrl)) {
    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.POST(json.as<String>());
    if (httpResponseCode == 200) {
      String response = http.getString();
      Serial.println(response);

      DynamicJsonDocument jsonResponse(256);
      deserializeJson(jsonResponse, response);

      int lightIntensity = jsonResponse["data"]["light_intensity"];
      // Control your LED lights based on lightIntensity value here
      for (int i = 0; i < 3; i++)     digitalWrite(ledPins[i], LOW);
      for (int i = 0; i < lightIntensity; i++) {
    digitalWrite(ledPins[i], HIGH);
      }
    } else {
      Serial.print("Error: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("Unable to connect to server.");
  }

  delay(5000); // Đợi 5 giây trước khi gửi yêu cầu tiếp theo
}