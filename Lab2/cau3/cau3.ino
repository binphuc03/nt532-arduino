#include "MQ135.h"  //Thêm thư viện
#define PIN_MQ135 A2    //Khai báo pin nối với chân A2
int LED = 3;
MQ135 mq135_sensor = MQ135(PIN_MQ135);   //Khai báo đối tượng thư viện
 
void setup() {
  Serial.begin(9600);   //Khởi tạo cổng Serial  
  pinMode(LED,OUTPUT);
  digitalWrite(LED,LOW);
}
 
void loop() {
  float ppm = mq135_sensor.getPPM();  //Đọc giá trị ppm
  Serial.print("PPM: ");
  Serial.print(ppm);
  Serial.println("ppm");
  if (ppm > 700) {
    // Kích hoạt đèn LED với tốc độ chớp nhanh
    blinkLED(100);
  } else if (ppm > 400) {
    // Kích hoạt đèn LED với tốc độ chớp trung bình
    blinkLED(500);
  } else {
    // Kích hoạt đèn LED với tốc độ chớp chậm
    blinkLED(1000);
  }
    // Chờ 1 giây trước khi đọc lại giá trị từ cảm biến
  //delay(1000);
}

// Hàm kích hoạt đèn LED với tốc độ chớp cho trước (milliseconds)
void blinkLED(int interval) {
  static unsigned long previousMillis = 0;
  static boolean ledState = LOW;

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    ledState = !ledState;
    digitalWrite(LED, ledState);
  }
}