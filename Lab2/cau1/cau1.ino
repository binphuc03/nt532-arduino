#define trigPin 13
#define echoPin 12
int LED = 2;
void setup()
{
Serial.begin (9600);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(LED, OUTPUT);
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
  { if(distance <=40) {Serial.println("muc 1");level=1;}
  else if(distance <= 80) {Serial.println("muc 2");level=2;}
  else if(distance <= 120) {Serial.println("muc 3");level=3;}
  else if(distance <= 160) {Serial.println("muc 4");level=4;}
  else {Serial.println("muc 5");level=5;}
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(level*200);
}
