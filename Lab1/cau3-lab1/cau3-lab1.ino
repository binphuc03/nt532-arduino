int LED[6] = {2,8,4,5,6,7};
int button = 11;
int state = 0;
void setup()
{
  Serial.begin(115200);
  for (int i=0;i<6;i++)
  pinMode(LED[i], OUTPUT);
  for (int i=0;i<6;i++) {digitalWrite(LED[i],HIGH);delay(500);}  
  for (int i=0;i<6;i++) {digitalWrite(LED[i],LOW);}           //Sáng lần lượt 6 đèn biểu thị bắt đầu
  pinMode(button, INPUT);
}
void loop()
{ 
  state = digitalRead(button);
  if (state == 1)
  {  
    int a = random(1,7);         //Ngẫu nhiên từ 1 đến 6
    for(int i=0;i<a;i++) 
    {
      digitalWrite(LED[i], HIGH);           //sáng đèn biểu thị xúc sắc
    }
    delay(1000); // Wait for 1000 millisecond(s)
    for(int j=1;j<=6;j++) 
    {
      for(int i=0;i<a;i++) 
      {
        digitalWrite(LED[i], LOW);
      }
      delay(200);
      for(int i=0;i<a;i++) 
      {
        digitalWrite(LED[i], HIGH);
      }
      delay(200);
    }                                        //Chớp tắt 6 lần  
  for(int i=0;i<a;i++) 
      {
        digitalWrite(LED[i], LOW);
      }
  }
}
