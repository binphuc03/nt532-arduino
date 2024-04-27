#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

char ssid[] = "UiTiOt-E3.1";
char password[] = "UiTiOtAP";

ESP8266WebServer server(80);

const int numLeds = 5;
const int ledPins[] = {D3, D4, D5, D6, D7};
bool ledStates[numLeds] = {false};

int randomLedCount;
int randomLedPositions[numLeds];
int userScore = 0;
bool gameActive = false;
unsigned long gameStartTime = 0;

void handleRoot() {
  String html = "<html><body>";
  html += "<h1>LED Game</h1>";
  html += "<p>Score: <span id='score'>" + String(userScore) + "</span></p>";
  html += "<p>Game Status: <span id='gameStatus'>" + String(gameActive ? "Active" : "Inactive") + "</span></p>";
  html += "<button onclick=\"startGame()\">Start Game</button>";
  html += "<button onclick=\"resetGame()\">Reset Game</button>";
  html += "<br><br>";
  html += "<button onclick=\"buttonPress(0)\">0</button>";
  html += "<button onclick=\"buttonPress(1)\">1</button>";
  html += "<button onclick=\"buttonPress(2)\">2</button>";
  html += "<script>";
  html += "function startGame() {";
  html += "  fetch('/start')";
  html += "    .then(response => response.text())";
  html += "    .then(data => {";
  html += "      document.getElementById('gameStatus').innerText = 'Active';";
  html += "    });";
  html += "}";
  html += "function resetGame() {";
  html += "  fetch('/reset')";
  html += "    .then(response => response.text())";
  html += "    .then(data => {";
  html += "      document.getElementById('gameStatus').innerText = 'Inactive';";
  html += "      document.getElementById('score').innerText = '0';";
  html += "    });";
  html += "}";
  html += "function buttonPress(buttonIndex) {";
  html += "  fetch('/press?button=' + buttonIndex)";
  html += "    .then(response => response.text())";
  html += "    .then(data => {";
  html += "      document.getElementById('score').innerText = data;";
  html += "      if (parseInt(data) <= 0) {";
  html += "        alert('Game Over! Your score is 0 or negative.');";
  html += "        document.getElementById('gameStatus').innerText = 'Inactive';";
  html += "      }";
  html += "    });";
  html += "}";
  html += "</script>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleStartGame() {
  if (gameActive) {
    server.send(400, "text/plain", "Game already active");
    return;
  }
  Serial.println("game started");
  gameActive = true;
  userScore = 0;
  randomLedCount = random(1, numLeds + 1);

  for (int i = 0; i < randomLedCount; i++) {
    randomLedPositions[i] = random(0, numLeds);
    while(digitalRead(ledPins[randomLedPositions[i]])==HIGH) randomLedPositions[i] = random(0, numLeds);
    digitalWrite(ledPins[randomLedPositions[i]], HIGH);
  }

  delay(2000);
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], LOW);
  }

  gameStartTime = millis();
  server.send(200, "text/plain", "Game started");
}

void handleResetGame() {
  if (gameActive) {
    server.send(400, "text/plain", "Cannot reset game while it is active");
    return;
  }
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], LOW);
  }

  server.send(200, "text/plain", "Game reset");
}

void handleButtonPress() {
  if (!gameActive) {
    server.send(400, "text/plain", "Game not active");
    return;
  }

  int buttonIndex = server.arg("button").toInt(); // Lấy tham số từ query string
  if (buttonIndex < 0 || buttonIndex >= numLeds) {
    server.send(400, "text/plain", "Invalid button index");
    return;
  }

  if (buttonIndex == randomLedCount % 3 && millis() - gameStartTime < 2000) {
    userScore++;
    server.send(200, "text/plain", String(userScore)); // Trả về điểm số mới

    // Tiếp tục trò chơi và hiển thị các nút mới
    randomLedCount = random(1, numLeds + 1);

    for (int i = 0; i < randomLedCount; i++) {
      randomLedPositions[i] = random(0, numLeds);
      while(digitalRead(ledPins[randomLedPositions[i]])==HIGH) randomLedPositions[i] = random(0, numLeds);
      digitalWrite(ledPins[randomLedPositions[i]], HIGH);
    }

    delay(2000);
    for (int i = 0; i < numLeds; i++) {
      digitalWrite(ledPins[i], LOW);
    }

    gameStartTime = millis(); // Đặt lại thời gian bắt đầu của trò chơi
  } 
  else {
    userScore--;
    if (userScore <= 0) {
      gameActive = false; // Kết thúc trò chơi nếu điểm số nhỏ hơn hoặc bằng 0
      userScore = 0;
    }
    else {
      // Tiếp tục trò chơi và hiển thị các nút mới
      randomLedCount = random(1, numLeds + 1);

      for (int i = 0; i < randomLedCount; i++) {
        randomLedPositions[i] = random(0, numLeds);
        while(digitalRead(ledPins[randomLedPositions[i]])==HIGH) randomLedPositions[i] = random(0, numLeds);
        digitalWrite(ledPins[randomLedPositions[i]], HIGH);
      }

      delay(2000);
      for (int i = 0; i < numLeds; i++) {
        digitalWrite(ledPins[i], LOW);
      }

      gameStartTime = millis(); // Đặt lại thời gian bắt đầu của trò chơi
    }
    server.send(200, "text/plain", String(userScore)); // Trả về điểm số mới
  }
}

void setup() {
  Serial.begin(115200);

  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }

  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], HIGH);
    delay(500);
    digitalWrite(ledPins[i], LOW);
  }

  for (int i = numLeds - 1; i >= 0; i--) {
    digitalWrite(ledPins[i], HIGH);
    delay(500);
    digitalWrite(ledPins[i], LOW);
  }

  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
  Serial.println("IP Address: " + WiFi.localIP().toString());

  server.on("/", handleRoot);
  server.on("/start", handleStartGame);
  server.on("/reset", handleResetGame);
  server.on("/press", handleButtonPress);

  server.begin();
  Serial.println("Server started");
}

void loop() {
  server.handleClient();
}
