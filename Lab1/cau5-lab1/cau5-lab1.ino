int LED[10] = {2,3,4,5,6,7,8,9,10,11};
int Button[3] = {12,13,14};
int State[3] = 0;
int a=0;
void setup()
{
Serial.begin(115200);
  for (int i=0;i<12;i++) pinMode(LED[i], OUTPUT);
    pinMode(button, INPUT);
  digitalWrite(LED[0],HIGH);
}
void loop()
{ 
  state = digitalRead(button);
    if(state==1) {
      if(a<12) 
        {
          a++;
          digitalWrite(LED[a],HIGH);
        }
      else 
        {
          a=0;
          for (int i=1;i<12;i++) digitalWrite(LED[0],LOW);
        }
    }
}
