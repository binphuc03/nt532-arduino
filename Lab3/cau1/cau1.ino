#include <ESP8266WiFi.h>
#include <WiFiClient.h>
//ESP Web Server Library to host a web page
#include <ESP8266WebServer.h>
//---------------------------------------------------------------

// Định nghĩa chân GPIO cho các đèn LED
const int ledPins[] = {D1, D2, D3, D4, D5};
const int numLeds = sizeof(ledPins) / sizeof(ledPins[0]);

char ssid[] = "UiTiOt-E3.1";
char password[] = "UiTiOtAP";

ESP8266WebServer server(80); // Khởi tạo server HTTP trên cổng 80

void handleRoot() {
  String content = "<html><head><title>LED Game</title></head><body>";
  content += "<h1>LED Game</h1>";
  content += "<p>Score: <span id='score'>0</span></p>";
  content += "<p>Status: <span id='status'>Ready</span></p>";
  content += "<button onclick='sendData(1)'>1</button>";
  content += "<button onclick='sendData(2)'>2</button>";
  content += "<button onclick='sendData(3)'>3</button>";
  content += "</body></html>";
  server.send(200, "text/html", content);
}

void handleNotFound() {
  server.send(404, "text/plain", "Not found");
}

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW); 
  }
  for (int i = 0; i < 5; i++)
  {     
    if(i==0) digitalWrite(ledPins[i], HIGH); 
      else 
        { 
          digitalWrite(ledPins[i], HIGH); 
          digitalWrite(ledPins[i-1], LOW); 
        }
        delay(200);
  }
  for (int i = 3; i >= 0; i++)
  {
    digitalWrite(ledPins[i], HIGH); 
    digitalWrite(ledPins[i+1], LOW); 
    delay(200);
  }
  digitalWrite(ledPins[0], LOW);
    // Kết nối với Wi-Fi
  WiFi.begin(ssid, password);
  
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }

  Serial.println("\nWiFi connected");
  Serial.println("IP Address: " + WiFi.localIP().toString());

  server.on("/", HTTP_GET, handleRoot);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  // Điều khiển trò chơi ở đây
}
