#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// Định nghĩa chân GPIO cho các đèn LED
const int ledPins[] = {D1, D2, D3, D4, D5};
const int numLeds = 5;

char ssid[] = "UiTiOt-E3.1";
char password[] = "UiTiOtAP";

ESP8266WebServer server(80); // Khởi tạo server HTTP trên cổng 80

int score = 0;            //điểm số
int targetLED = 0;        // số đèn hiện tại
bool gameRunning = false; //trạng thái trò chơi

void handleRoot() {
  String statusMessage = gameRunning ? "Running" : "Ready";
  String content = "<html><head><title>LED Game</title></head><body>";
  content += "<h1>LED Game</h1>";
  content += "<p>Score: <span id='score'>" + String(score) + "</span></p>";
  content += "<p>Status: <span id='status'>" + statusMessage + "</span></p>";
  content += "<button onclick='sendData(1)' " + String(gameRunning ? "" : "disabled") + ">1</button>";
  content += "<button onclick='sendData(2)' " + String(gameRunning ? "" : "disabled") + ">2</button>";
  content += "<button onclick='sendData(3)' " + String(gameRunning ? "" : "disabled") + ">3</button>";
  content += "</body></html>";
  server.send(200, "text/html", content);
}

void handleNotFound() {
  server.send(404, "text/plain", "Not found");         //nếu server gặp lỗi
}

void setup() {
  Serial.begin(9600);
  //khởi động ban đầu
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
  for (int i = 3; i >= 0; i--)
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

  // Bắt đầu trò chơi
  startGame();
}

void loop() {
    // Điều khiển trò chơi 
  server.handleClient();
}

void startGame() {                //Trạng thái bắt đầu
  score = 0;
  gameRunning = true;
  updateLED();
}

void updateLED() {                    //Cập nhập trạng thái hiện tại
   targetLED = random(1, numLeds + 1); // Chọn ngẫu nhiên số lượng đèn target
  int selectedLED[targetLED]; // Mảng lưu trữ các chỉ số của đèn LED được chọn
  for (int i = 0; i < targetLED; i++) {
    selectedLED[i] = random(0, numLeds); // Chọn ngẫu nhiên một đèn LED
    digitalWrite(ledPins[selectedLED[i]], HIGH); // Bật đèn LED được chọn
  }
  for (int i = 0; i < numLeds; i++) {
    if (!isInArray(selectedLED, targetLED, i)) {
      digitalWrite(ledPins[i], LOW); // Tắt các đèn LED không được chọn
    }
  }
  delay(2000); // Đợi 2 giây
  if (gameRunning) {
    sendData(-1); // Gửi dữ liệu để yêu cầu người chơi chọn
  }
}

bool isInArray(int arr[], int size, int element) {
  for (int i = 0; i < size; i++) {
    if (arr[i] == element) {
      return true;
    }
  }
  return false;
}

void sendData(int choice) {
  if (choice != -1 && !gameRunning) {
    return; // Không xử lý dữ liệu nếu trò chơi không hoạt động
  }

  if (choice == targetLED % 3) {
    score++; // Tăng điểm nếu chọn đúng
    server.send(200, "text/plain", "Correct");
  } else {
    score--; // Giảm điểm nếu chọn sai
    server.send(200, "text/plain", "Incorrect");
  }

  if (score < 0) {
    endGame();
  } else {
    updateLED(); // Chuyển qua vòng tiếp theo
  }
}

void endGame() {
  gameRunning = false;
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], LOW); // Tắt tất cả đèn LED
  }
  targetLED = 0;
  server.send(200, "text/plain", "Game Over");
}