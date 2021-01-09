#include <Adafruit_NeoPixel.h>
#define IRSensor    2
#define LED_PIN     7
#define LED_COUNT  144
#define BRIGHTNESS 50 // (max = 255)

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800); //defining strip.numPixels

void Square() {
  int whiteLength   = 36;
  int      delaytime = 0;
  int      loops         = 3;
  int      loopNum       = 0;
  int      x            = 0;
  for (;;) { // Repeat loops value
// i to strip.numPixels() = 144 
    for (int i = 0; i < strip.numPixels(); i++) { // For each pixel on strip
      for (int j = 0; j < 256; j = j + 50) { // Ramp up from 0 to 255,. where j white intensity

        strip.setPixelColor(i, strip.Color(0, 0, 0, strip.gamma8(j))); //set up color
        delay(delaytime);
        strip.show(); //show color
        delay(100);
      }

      for (int j = 255; j >= 0; j = j - 50) { // Ramp down

        strip.setPixelColor(x = i - whiteLength, strip.Color(0, 0, 0, strip.gamma8(j)));
        delay(100);
        strip.show();

        if ((loopNum >= 1) && (i <= 36)) {
          strip.setPixelColor(x = i - whiteLength + 144, strip.Color(0, 0, 0, strip.gamma8(j)));
          delay(delaytime);
          strip.show();
        }

      }
    }
    if (++loopNum >= loops) return;
  }
}
void setup()
{
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
    strip.show();
  }


}
