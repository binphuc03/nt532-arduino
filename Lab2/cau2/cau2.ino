#include "SevSeg.h"
#define trigPin 13
#define echoPin 12
SevSeg sevseg;
void setup()
{
    Serial.begin (9600);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    //Set to 1 for single digit display
    byte numDigits = 1;

    //defines common pins while using multi-digit display. Left empty as we have a single digit display
    byte digitPins[] = {};

    //Defines arduino pin connections in order: A, B, C, D, E, F, G, DP
    byte segmentPins[] = {2, 3, 4, 5, 6, 7, 8, 9};
    bool resistorsOnSegments = true;

    //Initialize sevseg object. Uncomment second line if you use common cathode 7 segment
    sevseg.begin(COMMON_ANODE, numDigits, digitPins, segmentPins, resistorsOnSegments);
    //sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins, resistorsOnSegments);

    sevseg.setBrightness(90);
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
  if (distance >= 180 || distance <= 0)
  {
  Serial.println("Out of range");
  level=0;
  }
  else
  { if(distance<80)
      {
        level=distance/10;
        level=round(level)+1;
      }
    else level=9;
    Serial.println(level);
  }
  sevseg.setNumber(level);
  sevseg.refreshDisplay(); 
  delay(1000);
}