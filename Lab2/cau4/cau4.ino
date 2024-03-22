#include <DHT.h>

#define DHTPIN 5
#define DHTTYPE DHT11
#define LED1 2
#define LED2 3
#define LED3 4

DHT dht(DHTPIN, DHTTYPE);

void setup() 
{
  Serial.begin(9600);
  dht.begin();
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
}

void loop() 
{
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Map temperature and humidity to LED brightness levels
  int tempLevel;
  int humLevel;
  if(temperature <= 26) tempLevel = 1;
  else if(temperature <= 27) tempLevel =2;
  else tempLevel = 3;
  if (humidity <= 60) humLevel=1;
  else if (humidity <= 70) humLevel=2;
  else humLevel = 3;
  int ledLevel = 0;

  // Calculate led level
  if (tempLevel == 3) ledLevel = 3;
  else if (humLevel == 3) ledLevel = 0;
  else ledLevel = tempLevel;


  // Control LEDs based on temperature and humidity levels
  switch (ledLevel) 
  {
    case 0:
      // Turn off all LEDs
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      break;
    case 1:
      // Turn on LED 1
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      break;
    case 2:
      // Turn on LED 1 and 2
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, LOW);
      break;
    case 3:
      // Turn on all LEDs
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);
      break;
  }

  delay(1000); // Read data every 1 seconds
}