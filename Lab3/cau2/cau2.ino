#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Wire.h>
#include <BH1750.h>

#define TRIGGER_PIN D5  // Chân Trigger của cảm biến khoảng cách
#define ECHO_PIN D6     // Chân Echo của cảm biến khoảng cách

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const char* serverUrl = "http://YOUR_SERVER_IP_ADDRESS:80/data"; // Thay đổi địa chỉ server

BH1750 lightMeter;

void setup() {
  Serial.begin(9600);
  Wire.begin(); // Khởi động I2C cho cảm biến ánh sáng
  lightMeter.begin(); // Khởi động cảm biến ánh sáng

  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
 // Kết nối với Wi-Fi
  WiFi.begin(ssid, password);
  
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
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

  sendSensorData(light_value , Distance_Value);

  delay(5000); // Gửi dữ liệu mỗi 5 giây
}

void sendSensorData(int lightValue, int distanceValue) {
  // Tạo JSON payload
  String jsonPayload = "{\"light\": " + String(lightValue) + ", \"distance\": " + String(distanceValue) + "}";

  // Kết nối tới server
  WiFiClient client;
  HTTPClient http;
  http.begin(client, serverUrl); // Sử dụng phương thức này để bắt đầu một kết nối HTTP

  // Gửi POST request đến server
  http.addHeader("Content-Type", "application/json");
  int httpResponseCode = http.POST(jsonPayload);

  if (httpResponseCode > 0) {
    Serial.printf("HTTP Response code: %d\n", httpResponseCode);
    String response = http.getString();
    Serial.println(response);
  } else {
    Serial.printf("Error sending POST request: %s\n", http.errorToString(httpResponseCode).c_str());
  }

  http.end();
}