#include <Adafruit_NeoPixel.h>
#define IRSensor    2
#define LED_PIN     7
#define LED_COUNT  144
#define BRIGHTNESS 50 // (max = 255)

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);

void markers(){
    strip.setPixelColor(0, strip.Color(0, 0, 0, 125));
    strip.setPixelColor(36, strip.Color(0, 0, 125, 0));
    strip.setPixelColor(72, strip.Color(0, 125, 0, 0));
    strip.setPixelColor(108, strip.Color(125, 0, 0, 0));
    strip.show();
}

void Square() {
// Parameters
  int whiteLength         = 2;
  int stripLength        =144;
  int      loops           = 4;
  int      loopNum        = 0;
  int      x              = 0;
  int maxbrightness     =255; //255
  int timer =40; // seconds
  int brightnessStep    =maxbrightness/timer*2; 
  //unsigned long period = 3;
  
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

    for (int i = 0; i < strip.numPixels(); i++) { // For each pixel on strip
      //if(loopNum<1){
      //  for (unsigned long elapsedMillis=millis(),  previousMillis = millis();
       //       (elapsedMillis-previousMillis) <period;
      //      elapsedMillis=millis()){}
       //   }
      for (int j = 0; j < maxbrightness; j = j + brightnessStep) { // Ramp up from 0 to 255
            strip.setPixelColor(i, strip.Color(0, 0, 0, strip.gamma8(j)));
            strip.show();
        }
      for (int j = maxbrightness; j >= 0; j = j - brightnessStep) { // Ramp down
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
     Serial.println((loopend-loopstart));
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
