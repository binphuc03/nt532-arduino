#include <BH1750.h>
#include <Wire.h>
BH1750 lightMeter;
int LED[10] = {2,3,4,5,6,7,8,9,10,11} ;
int button = A0;
bool buttonState = false; // Trạng thái nút bấm: false - không được nhấn, true - được nhấn
unsigned long pressTime = 0; // Thời điểm bắt đầu nhấn nút
int buttonPressCount = 0; // Số lần nhấn nút
void setup() 
{
  Serial.begin(9600);
   for (int i = 0; i < 10; i++) {
    pinMode(LED[i], OUTPUT);
    digitalWrite(LED[i], LOW);
  }
  lightMeter.begin();
  pinMode(button, INPUT);
}

void loop()
{
  int a;                                  //cuong do sang hien tai
  float lux = lightMeter.readLightLevel();
  bool currentState = digitalRead(button); // Đọc trạng thái của nút bấm
  // Kiểm tra debounce để tránh nhiễu từ nút bấm
  if (currentState != buttonState) {
    if (currentState == HIGH) {
      buttonPressCount++; // Tăng số lần nhấn nút
      if (millis() - pressTime > 1500 && buttonPressCount == 2) {
        buttonPressCount--;
      }
      if (buttonPressCount > 3) {
        buttonPressCount == 0;
      }
    }
    pressTime = millis(); // Ghi lại thời điểm bắt đầu nhấn nút
    Serial.println(buttonPressCount);
    Serial.print("Press time: ");
    Serial.println(millis() - pressTime);
  }
  buttonState = currentState;


  // Kiểm tra số lần nhấn nút và thực hiện chức năng tương ứng
  
  switch (buttonPressCount) {
    case 1:
      a = lux / 20;
      if (a < 5)
        turnFiveLEDs(a);
      else
        turnOffLEDs();
      break;
    default:
      a = lux / 10;              
      if (a < 10)
        turnOnLEDs(a);
      else
        turnOffLEDs();
      break;
    delay(100);
  }
  // Đặt lại số lần nhấn nút sau khi thực hiện chức năng
  if (buttonPressCount == 2) buttonPressCount = 0;
  delay(100);
}

void turnOnLEDs(int a) {
  turnOffLEDs();
  for (int i = 0; i < 10-a; i++) {
    digitalWrite(LED[i], HIGH);
  }
}

void turnFiveLEDs(int a) {
  turnOffLEDs();
  for (int i = 0; i < 5-a; i++) {
    digitalWrite(LED[i], HIGH);
  }
}

void turnOffLEDs() {
  for (int i = 0; i < 10; i++) {
    digitalWrite(LED[i], LOW);
  }
}
