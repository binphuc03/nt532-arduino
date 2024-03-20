#define trigPin 13
#define echoPin 12
int LED = 2;
void setup()
{
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(LED,LOW);
}
void loop()
{
  long duration, distance, level;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if (distance >= 200 || distance <= 0)
  {
  Serial.println("Out of range");
  }
  else
  { if(distance <=40) {Serial.println("muc 1");blinkLED(100);}
  else if(distance <= 80) {Serial.println("muc 2");blinkLED(200);}
  else if(distance <= 120) {Serial.println("muc 3");blinkLED(300);}
  else if(distance <= 160) {Serial.println("muc 4");blinkLED(400);}
  else {Serial.println("muc 5");blinkLED(500);}
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(1000);
}
// Hàm kích hoạt đèn LED với tốc độ chớp cho trước (milliseconds)
void blinkLED(int interval) {
  static unsigned long previousMillis = 0;  // thời gian lần chuyển đổi cuối
  static boolean ledState = LOW;

  unsigned long currentMillis = millis(); //thời gian hiện tại

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    ledState = !ledState;
    digitalWrite(LED, ledState);
  }
}
