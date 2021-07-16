void CmdInterpreter()
{
  Serial.print("Fish ");
  Serial.print(FISH_ID);
  Serial.print(" Command: ");
  
  String Cmd = Subs[0];
  
  if(Cmd == "LED")
    {
      Serial.println("LED");
      ModeLed = _LED;
      _Red = Subs[2].toInt();
      _Green = Subs[3].toInt();
      _Blue = Subs[4].toInt();
    }
  else if(Cmd == "RAINBOW")
  {
     Serial.println("RAINBOW");
     ModeLed = _RAINBOW;
     wait=Subs[2].toInt();
  }
  else if(Cmd == "BLINK")
  {
     
     Serial.println("BLINK");
     ModeLed = _BLINK;
     _Red = Subs[2].toInt();
     _Green = Subs[3].toInt();
     _Blue = Subs[4].toInt();
     wait = Subs[5].toInt();
  }
  else Serial.println("unknown !?!");
}
