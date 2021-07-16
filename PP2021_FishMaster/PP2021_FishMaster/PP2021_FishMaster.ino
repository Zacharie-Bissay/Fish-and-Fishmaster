// set this to the hardware serial port you wish to use
#define HWSERIAL Serial1

int led = 13;
int en485 = 2;
#define DEBUT_TRAME '<'
#define FIN_TRAME '>'
String ReceivedString = "";
extern String Subs[];
char inByte;
String cmd="";

void setup() 
{
  Serial.begin(115200);
  HWSERIAL.begin(115200);
  pinMode(led, OUTPUT);
  pinMode(en485, OUTPUT);
  digitalWrite(led, LOW);
  digitalWrite(en485, LOW);
  delay(2000);
  Serial.println();
  Serial.println("***** Fish Master ****");
}
//*****************************************************
void FlushRx485()
{
  while (HWSERIAL.available())
    {
      inByte = HWSERIAL.read();
    }
}
//******************************************************
void WaitAnswer()
{
  bool Flag=false;
  Serial.println("Waiting for Answer ...");

while (!Flag)
  {
    while (!HWSERIAL.available()){};
    char Chr = HWSERIAL.read();
    if (Chr == DEBUT_TRAME) ReceivedString = "";
    else
    {
      if (Chr == FIN_TRAME)
      {
        Serial.print("recieved: ");
        Serial.println(ReceivedString);
        String_Split(',', ReceivedString);
        Flag=true;
      }
      else ReceivedString += Chr;
    }
  }
}
//******************************************************
void SendToFish( String Com, bool Answer)
{
  Serial.println();
  Serial.print("COM: ");
  Serial.println(Com);
  digitalWrite(led, HIGH);
  digitalWrite(en485, HIGH);
  delayMicroseconds(500);
 
  HWSERIAL.println(Com);
  
  HWSERIAL.flush();
  delayMicroseconds(500);
  digitalWrite(en485, LOW);
  digitalWrite(led, LOW);
  if(Answer) WaitAnswer();
  delay(1);
}
//*****************************************************
void loop() 
{
  SendToFish("<LED,0,255,0,0>", false);
  delay(1000);
  SendToFish("<LED,0,0,0,0>", false);
  delay(1000);
  SendToFish("<LED,1,0,255,0>", false);
  delay(1000);
  SendToFish("<LED,1,0,0,0>", false);
  delay(1000);
  SendToFish("<LED,2,0,0,255>", false);
  delay(1000);
  SendToFish("<LED,2,0,0,0>", false);
  delay(1000);
  SendToFish("<RAINBOW,2,10>", false);
  delay(3000);
  SendToFish("<BLINK,2,50,50,50,10>", false);
  delay(8000);
   SendToFish("<BLINK,2,50,0,50,100>", false);
  delay(8000);
  SendToFish("<LED,2,0,0,0>", false);
  delay(3000);
}
