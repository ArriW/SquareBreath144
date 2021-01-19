#include <Adafruit_NeoPixel.h>
#define IRSensor    2
#define LED_PIN     7
#define LED_COUNT  144
#define BRIGHTNESS 50 // (max = 255)

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);

void markers(){
    strip.fill(strip.Color(0, 0, 0, 125));
    strip.show();
}

void Square() {
// Parameters
  int whiteLength         = 3;
  float stripLength        =123;
  int      loops           = 4;
  int      loopNum        = 0;
  int      x              = 0;
  float maxbrightness     =255;
  float minbrightness = 125;
  int timer =16; // seconds
  float brightnessStep    =maxbrightness*(minbrightness/maxbrightness)*(stripLength/strip.numPixels())/timer*2; 

  
// Timers
  unsigned long loopstart =0; //timing loops durations
  unsigned long loopend=0; //timing loops durations
  unsigned long dimtwoloopstart =0; //timing loops durations
  unsigned long dimtwoloopend=0; //timing loops durations
  
 //Initiate Serial communication.
  Serial.begin(9600);
  Serial.print("Brightness Step: ");
  Serial.println(brightnessStep); 

  
  for (;;) { // Repeat loops value
     loopstart=millis();

    for (int i = 0; i < stripLength; i++) { // For each pixel on strip

      for (int j = minbrightness; j > 0; j = j - brightnessStep) { 
            strip.setPixelColor(i, strip.Color(0, 0, 0, strip.gamma8(j)));
            strip.show();
        }
      for (int j = 0; j <= minbrightness; j = j + brightnessStep) { 
        if ((loopNum >= 1) && (i < whiteLength)) {
          strip.setPixelColor(x = i - whiteLength + stripLength, strip.Color(0, 0, 0, strip.gamma8(j)));
          strip.show();
        } else
        {
        strip.setPixelColor(x = i - whiteLength, strip.Color(0, 0, 0, strip.gamma8(j)));
        strip.show();
        }
//dimtwoloopstart=millis();
//dimtwoloopend=millis();
//Serial.println((dimtwoloopend-dimtwoloopstart));
      }
      markers();
    }

           loopend=millis();
    if (++loopNum >= loops) return;
    
     Serial.print("Loop: ");
     Serial.println(loopNum);
     Serial.print("Loop Duration: ");
     Serial.println((loopend-loopstart)); //unsure why this is not providing the right time
  }
}
void setup(){
  strip.begin();
  strip.show();
  strip.setBrightness(BRIGHTNESS);

  pinMode (IRSensor, INPUT); // sensor pin INPUT
}

void loop() {

  int statusSensor = digitalRead (IRSensor);
  if (statusSensor == 1)
  {

    Square();
    strip.fill(strip.Color(0, 0, 0, 0));
    strip.show();

  }

  else
  { 
    markers();
  }


}
