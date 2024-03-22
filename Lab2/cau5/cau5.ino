int sensorState = 0;
int sensorPin = 7;
void setup()
{
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}
void loop()
{
  sensorState = digitalRead(sensorPin);
  Serial.print(sensorState);
  delay(200);
}