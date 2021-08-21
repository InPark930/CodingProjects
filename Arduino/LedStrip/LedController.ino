//We always have to include the library
#include <Adafruit_NeoPixel.h>

#define LED_PIN 6
#define LED_COUNT 60
#define Sw 2
#define Rx A0
#define Ry A1

int speed = 10;

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

enum LedState {
  SingRot,
  AllRot,
  Fixed
};

int brightness = 250;

//LedState currStat = AllRot;
//static LedState currStat = Fixed;
static LedState currStat = Fixed;

/* we always wait a bit between updates of the display */
unsigned long delaytime=250;

void setup() {
  Serial.begin(9600); 

  pinMode(Rx, INPUT);
  pinMode(Ry, INPUT);
  pinMode(Sw, INPUT); 

  strip.begin(); //always needed
  strip.show(); // 0 data => off.
  strip.setBrightness(100); // ~20% (max = 255)
}

void loop() {

  bool SW_state = digitalRead(Sw);
  Brightness();
  TypeControl();

  switch(currStat){
    case (SingRot):
    SingleRotateLED();
    break;

    case (AllRot):
    AllRotateLED();
    break;

    case(Fixed):
    FixedLED();        
    break;

    default:
    break;
  }
  delay(100);
  Serial.println("Test : ");
  
}

void SingleRotateLED(){
  int n = strip.numPixels();
 // fph = FirstPixelHue
 for (long fph = 0; fph < 5 * 65536; fph += 256)
  {
    for (int i = 0; i < n; i++)
        { 
          int pixelHue = fph + (i * 65536L / n);
          strip.setPixelColor(i,strip.gamma32(strip.ColorHSV(pixelHue)));
        }
  strip.show();
  }
}

void AllRotateLED(){
  int n = strip.numPixels();
 // fph = FirstPixelHue
 for (long fph = 0; fph < 5 * 65536; fph += 256)
  {
    for (int i = 0; i < n; i++)
        { 
          int pixelHue = fph + 65536L / n;
          strip.setPixelColor(i,strip.gamma32(strip.ColorHSV(pixelHue)));
        }
  strip.show();
  }
}

void FixedLED(){
   int n = strip.numPixels();
 // fph = FirstPixelHue
    for (int i = 0; i < n; i++)
        { 
          strip.setPixelColor(i,200,200,200);
        }
  strip.show();
}

void Brightness(){
  int sens = 200;  
  int xPos = analogRead(Rx);
  int increment = 20;

  if ((xPos-sens) > 500)
    brightness = brightness - increment;
  else if ((xPos+sens) < 500)
    brightness = brightness + increment;
  
  if (brightness > 250){
    brightness = 250;
  }
  if (brightness <= increment){
    brightness = increment;
  }

    Serial.print("Input : ");
  Serial.print(xPos);
  
  Serial.print(" brightness : ");
  Serial.println(brightness);
  strip.setBrightness(brightness);
}

void TypeControl(){  
  int yPos = analogRead(Ry);
  int sens = 200;  

  if ((yPos-sens) > 500){
    switch(currStat){
      case(SingRot):
      currStat = AllRot;
      break;

      case(AllRot):
      currStat = Fixed;
      break;

      case(Fixed):
      currStat = SingRot;
      break;
    }
  }
  else if ((yPos+sens) < 500){
    switch(currStat){
      case(SingRot):
      currStat = Fixed;
      break;

      case(AllRot):
      currStat = SingRot;
      break;

      case(Fixed):
      currStat = AllRot;
      break;
    }
  }  
}
