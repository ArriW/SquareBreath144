#include <Adafruit_NeoPixel.h>
#define IRSensor    2
#define LED_PIN     7
#define LED_COUNT  144
#define BRIGHTNESS 255 // (max = 255)
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);

// Parameters
int whiteLength         = 5;
float stripLength        =123;

float maxbrightness     =175;
float minbrightness = 75;
int timer =16; // seconds
float brightnessStep  =maxbrightness*(minbrightness/maxbrightness)*
  (stripLength/strip.numPixels())/timer*2; 

//void markers(){
 //   strip.fill(strip.Color(minbrightness, 0, 0, strip.gamma8(125)));
 //   strip.show();
//}

void Square() {

int      loops           = 4;
int      loopNum        = 0;
int      x              = 0;
 
// Timers
  unsigned long loopstart =0; //timing loops durations
  unsigned long loopend=0; //timing loops durations
  
  //Initiate Serial communication.
  Serial.begin(9600);
  Serial.print("Brightness Step: ");
  Serial.println(brightnessStep); 

//Fill Strip for base
  strip.fill(strip.Color(strip.gamma8(minbrightness), 0, 0, strip.gamma8(minbrightness)));
  strip.show();
  
  for (;;) { // Repeat loops value
     loopstart=millis();

    for (int i = 0; i < stripLength; i++) { // For each pixel on strip

      for (int j = minbrightness; j < maxbrightness; j = j + brightnessStep) { 
            strip.setPixelColor(i, strip.Color(strip.gamma8(j), 0, 0, strip.gamma8(j)));
            strip.show();
        }
      for (int j = maxbrightness; j >= minbrightness; j = j - brightnessStep) { 
        if ((loopNum >= 1) && (i < whiteLength)) {
          strip.setPixelColor(x = i - whiteLength + stripLength, strip.Color(strip.gamma8(j), 0, 0, strip.gamma8(j)));
          strip.show();
        } else
        {
        strip.setPixelColor(x = i - whiteLength, strip.Color(strip.gamma8(j), 0, 0, strip.gamma8(j)));
        strip.show();
        }

      }
//      markers();
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
    strip.fill(strip.Color(strip.gamma8(minbrightness), 0, 0, strip.gamma8(minbrightness)));
    strip.show();

  }

  else
  { 
    //markers();
  }


}
