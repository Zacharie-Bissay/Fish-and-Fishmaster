// set this to the hardware serial port you wish to use
#define HWSERIAL Serial1

#define FISH_ID 2

#include <Adafruit_NeoPixel.h>
// Which pin on the Arduino is connected to the NeoPixels?
#define PIN  17 
// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 60 // Popular NeoPixel ring size
/* 
WARNING: il faut commenter le blocage des interruptions dans Adafruit_Neopixel.cpp:
Normalement, la fonction pixels.show() bloque les ITs pour garantir son timing très précis
 #if !( defined(NRF52) || defined(NRF52_SERIES) )
  //noInterrupts(); // Need 100% focus on instruction timing
 #endif
Sans cela, la communication Serial est corrompue 
En contrepartie il y a un léger scintillement du ruban de Leds ...
*/

#define DEBUT_TRAME '<'
#define FIN_TRAME '>'
String ReceivedString = "";
extern String Subs[];
char inByte;
int led = 13;
int en485 = 2;
enum Modes { _STBY, _LED, _RAINBOW, _BLINK };
int ModeLed = _STBY;
int wait=0;
int _Red, _Green, _Blue;

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


void setup() 
{
  Serial.begin(115200);
  /*
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Native USB only
  }*/
  HWSERIAL.begin(115200);
  pinMode(led, OUTPUT);
  pinMode(en485, OUTPUT);
  digitalWrite(led, LOW);
  digitalWrite(en485, LOW);
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.clear();
  pixels.show();
  delay(2000);
  Serial.print("fishID=");
  Serial.println(FISH_ID);
  Serial.flush();
}

//*****************************************
void LedStripColor(int red, int green, int blue)
{
  for(int i=0; i< NUMPIXELS; i++)
      {
        pixels.setPixelColor(i, pixels.Color(red, green, blue));
      }
}

//*****************************************************
void FlushRx485()
{
  while (HWSERIAL.available()>0)
    {
      inByte = HWSERIAL.read();
    }
}
//**********************************************
void loop() 
{
   switch(ModeLed)
   {
    case _STBY:
      LedStripColor(5,5,5);
      wait=100;
      PixUpdate();
    break;
    case _LED:
      LedStripColor(_Red,_Green,_Blue);
      wait=100;
      PixUpdate();
    break;
    case _RAINBOW:
      Rainbow();
    break;
    case _BLINK:
      Blink();
    break;
   }
}
//********************************
void Blink()
{
  LedStripColor(_Red,_Green,_Blue);
  for(int Time=0; Time<10; Time++)
  {
    PixUpdate();
    if(ModeLed != _BLINK) break;
  }
  LedStripColor(0,0,0);
  for(int Time=0; Time<10; Time++)
  {
    PixUpdate();
    if(ModeLed != _BLINK) break;
  }
}
//********************************
// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void Rainbow() 
{
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) 
  {
    for(int i=0; i<pixels.numPixels(); i++) 
    { // For each pixel in strip...
      int pixelHue = firstPixelHue + (i * 65536L / pixels.numPixels());
      pixels.setPixelColor(i, pixels.gamma32(pixels.ColorHSV(pixelHue)));
    }
   PixUpdate();
   if(ModeLed != _RAINBOW) break;
  }
}
//**********************************
void PixUpdate()
{
    pixels.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
    if (HWSERIAL.available()>4) ReadCmd();
}
