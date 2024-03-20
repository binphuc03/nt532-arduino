#include "SevSeg.h"
SevSeg sevseg;
int LED[6]={A0,A1,A2,A3,A4,A5};   // A0,A1,A2 lần lượt là đèn đỏ,vàng,xanh của giao lộ A; A3,A4,A5 lần lượt là đèn đỏ,vàng,xanh của giao lộ B
void setup()
{
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
    for(int i=0;i<6;i++) pinMode(LED[i], OUTPUT);
}

void loop()
{ 
   //Display numbers one by one with 2 seconds delay
   int a = 1;
   while (a!=0)
   {
    if(a==1) {    
      digitalWrite(LED[0],HIGH);
      digitalWrite(LED[5],HIGH);                   //ban đầu đèn đỏ ở giao lộ A sáng thì đèn xanh ở giao lộ B sẽ sáng tương ứng
      for(int i = 9; i >= 0; i--)
    { 
      if(i==3)
      {
        digitalWrite(LED[5],LOW);
        digitalWrite(LED[4],HIGH);               //hết 6 giây thì đèn xanh ở giao lộ B chuyển sang đèn vàng
      }
      sevseg.setNumber(i);
      sevseg.refreshDisplay(); 
      delay(1000);
    }
    a+=2;analogWrite(LED[4],LOW);analogWrite(LED[0],LOW);                 //đèn vàng ở giao lộ B và đèn đỏ ở giao lộ A tắt để chuyển sang giai đoạn tiếp theo
    }
    if(a==3) {    
      digitalWrite(LED[2],HIGH);
      digitalWrite(LED[3],HIGH);                    //ban đầu đèn đỏ ở giao lộ B sáng thì đèn xanh ở giao lộ A sẽ sáng tương ứng
      for(int i = 6; i >= 0; i--)
    { 
      sevseg.setNumber(i);
      sevseg.refreshDisplay(); 
      delay(1000);
    } 
      digitalWrite(LED[2],LOW);
      digitalWrite(LED[1],HIGH);                  //hết 6 giây thì đèn xanh ở giao lộ A chuyển sang đèn vàng
      for(int i = 3; i >= 0; i--)
    { 
      sevseg.setNumber(i);
      sevseg.refreshDisplay(); 
      delay(1000);
    } 
    a-=2; 
    digitalWrite(LED[1],LOW);digitalWrite(LED[3],LOW);        //đèn vàng ở giao lộ A và đèn đỏ ở giao lộ B tắt để chuyển sang giai đoạn tiếp theo
   }
}
}
