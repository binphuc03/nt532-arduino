//#include <BH1750.h>
int LED[10] = {2,3,4,5,6,7,8,9,10,11} ;
int button = A0;
//BH1750 lightMeter;
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
 // lightMeter.begin();
  pinMode(button, INPUT);
  
}

void loop()
{
  float lux = lightMeter.readLightLevel();
  bool currentState = digitalRead(button); // Đọc trạng thái của nút bấm
   // Kiểm tra debounce để tránh nhiễu từ nút bấm
  if (currentState != buttonState) 
  {
    if (currentState == HIGH) 
    {
      if (millis() - pressTime > 50 && millis() - pressTime < 1000) 
      {
        buttonPressCount++; // Tăng số lần nhấn nút
      }
      pressTime = millis(); // Ghi lại thời điểm bắt đầu nhấn nút
    }
  }
 //   if(currentState==HIGH) buttonPressCount=count(0);



  // Kiểm tra số lần nhấn nút và thực hiện chức năng tương ứng
  switch (buttonPressCount) {
    case 1:
      turnOnLEDs(5);
      delay(1000);
      break;
    case 2:
      turnOnLEDs(10); 
      break;
    default:
     // turnOffLEDs();
      break;
  }x
  Serial.println(buttonPressCount);
  delay(500);
  turnOffLEDs();
  // Đặt lại số lần nhấn nút sau khi thực hiện chức năng
  buttonPressCount = 0;
  buttonState=currentState;

  // Tùy chỉnh điều khiển đèn LED tùy thuộc vào cường độ ánh sáng
  int a = lux / 10;

}
void turnOnLEDs(int a) {
  for (int i = 0; i < 10-a; i++) {
    digitalWrite(LED[i], HIGH);
  }
}

void turnOffLEDs() {
  for (int i = 0; i < 10; i++) {
    digitalWrite(LED[i], LOW);
  }
}
int count(int a) {
  static unsigned long previousMillis = 0;
  unsigned long currentMillis = millis();

  while (millis() - previousMillis >= 10) {
    previousMillis = millis();
    a++;
  }
  return a;
}