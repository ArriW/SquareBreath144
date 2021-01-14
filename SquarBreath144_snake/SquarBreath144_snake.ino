#include <Adafruit_NeoPixel.h>
#define IRSensor    2
#define LED_PIN     7
#define LED_COUNT  144
#define BRIGHTNESS 50 // (max = 255)

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);

void Square() {
  int whiteLength   = 36;
  int      delaytime = 0;
  int      loops         = 5;
  int      loopNum       = 0;
  int      x            = 0;
  unsigned long myTime;
  int loopstart =0; //timing loops durations
  int loopend=0; //timing loops durations
  

  unsigned long period = 3;

 //Initiate Serial communication.
 Serial.begin(9600);
     
  for (;;) { // Repeat loops value
     loopstart=millis();

    for (int i = 0; i < strip.numPixels(); i++) { // For each pixel on strip
      if(loopNum<1){
          for (unsigned long elapsedMillis=millis(),  previousMillis = millis();
            (elapsedMillis-previousMillis) <period;
            elapsedMillis=millis()){}
          }
      for (int j = 0; j < 106; j = j + 50) { // Ramp up from 0 to 255
            strip.setPixelColor(i, strip.Color(0, 0, 0, strip.gamma8(j)));
            strip.show();
        }
      for (int j = 106; j >= 0; j = j - 50) { // Ramp down

        strip.setPixelColor(x = i - whiteLength, strip.Color(0, 0, 0, strip.gamma8(j)));
        strip.show();

        if ((loopNum >= 1) && (i <= 36)) {
          strip.setPixelColor(x = i - whiteLength + 144, strip.Color(0, 0, 0, strip.gamma8(j)));
          strip.show();
        }

      }
    }
    if (++loopNum >= loops) return;
    
       loopend=millis();
       
     Serial.print("Loop: ");
     Serial.println(loopNum);
     
     Serial.print("Loop Duration: ");
     Serial.println(loopend-loopstart);
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
    strip.fill(strip.Color(0, 0, 0, 0));
    Square();
    strip.fill(strip.Color(0, 0, 0, 0));
    strip.show();
  }

  else
  {
    strip.show();
  }


}
