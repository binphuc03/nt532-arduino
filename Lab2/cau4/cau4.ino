#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11
#define LED1 3
#define LED2 4
#define LED3 5

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() 
{
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
  int tempLevel = map(temperature, 0, 40, 0, 3);
  int humLevel = map(humidity, 20, 80, 0, 3);
  int ledLevel = 0;

  // Check tem & hum
  Serial.println("Temp", temperature, " - level: ", tempLevel);
  Serial.println("Hum", humidity, " - level: ", humLevel);
/*
Tem = 3 => level 3
Hum = 3, tem != 3 => level 0
Tem = 1 => level 1
Tem = 2 => level 2
Tem = 0 => level 0

*/

  // Calculate led level
  if (temLevel == 3) ledLevel = 3;
  else if (humLevel == 3) ledLevel = 0;
  else ledLevel = temLevel;


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

  delay(2000); // Read data every 2 seconds
}
