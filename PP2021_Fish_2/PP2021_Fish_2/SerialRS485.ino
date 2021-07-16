//**********************************
void ReadCmd()
{
bool Flag=false;
bool Started=false;
char Chr;
Serial.println();
Serial.print(HWSERIAL.available());
Serial.print(": ");

Started=false;
Flag=false;
digitalWrite(led, HIGH);

while(HWSERIAL.available()) // recherche debut trame
{
  Chr = HWSERIAL.read();
  Serial.print(Chr);
  if (Chr == DEBUT_TRAME)
  {
    Started=true;
    break;
  }
}
if(Started)
{
  ReceivedString = "";
  while(!Flag){
  while (!HWSERIAL.available()){};
  Chr = HWSERIAL.read();
  Serial.print(Chr);
  if (Chr == FIN_TRAME)
      {
        Serial.println();
        //Serial.print("recieved: ");
        //Serial.println(ReceivedString);
        String_Split(',', ReceivedString);
        Flag=true;
        digitalWrite(led, LOW);
        if(Subs[1].toInt()==FISH_ID)
        {
          //Serial.println("=> For my ID !");
          CmdInterpreter();
        }
        ReceivedString = "";
      }
      else ReceivedString += Chr;
  }
}
digitalWrite(led, LOW);
//Serial.println("back to rainbow");
}
