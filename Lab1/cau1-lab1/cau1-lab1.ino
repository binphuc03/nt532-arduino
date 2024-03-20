int LED[12] = {2,3,4,5,6,7,8,9,10,11,12,13};
int button = A0;
int state = 0;
int newstate = 0;
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
  newstate = digitalRead(button);
    if(newstate == 1 && newstate!=state) {
      if(a<11) 
        {
          a++;
          digitalWrite(LED[a],HIGH);
        }
      else 
        {
          a=0;
          for (int i=1;i<12;i++) digitalWrite(LED[i],LOW);
        }
      
    }
  state=newstate;
}
