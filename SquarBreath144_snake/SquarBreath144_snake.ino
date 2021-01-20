#include <Adafruit_NeoPixel.h>
#define IRSensor    2
#define LED_PIN     7
#define LED_COUNT  144
#define BRIGHTNESS 255 // (max = 255)
#define PI 3.1415926535897932384626433832795
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);

// Parameters
int whiteLength         = 5;
float stripLength        =123;
float maxbrightness     =175;
float minbrightness = 75;
int timer =16; // seconds
float brightnessStep  =maxbrightness*(minbrightness/maxbrightness)*
  (stripLength/strip.numPixels())/timer*2; 

// variables for starting main loop
int counter=0;


void intro(){
int period=1000;
for (unsigned long elapsedMillis=millis(),  previousMillis = millis(),
  introbrightness,dampen=1;elapsedMillis-previousMillis <3*period;
  elapsedMillis=millis()){
  
  introbrightness=minbrightness+abs(minbrightness*sin(PI*(elapsedMillis-previousMillis)/(period)));
  strip.fill(strip.Color(strip.gamma8(introbrightness), 0, 0, strip.gamma8(introbrightness)));
  strip.show();
            }
}

void setgo(){
  for(int i=0; i <2;i++){
    strip.setPixelColor(1, strip.Color(strip.gamma8(maxbrightness), 0, 0, strip.gamma8(maxbrightness)));
    strip.setPixelColor(2, strip.Color(strip.gamma8(maxbrightness), 0, 0, strip.gamma8(maxbrightness)));
    strip.show();  
    delay(1000);
    strip.setPixelColor(1, strip.Color(0, 0, 0, 0));
    strip.setPixelColor(2, strip.Color(0, 0, 0, 0));
    strip.show(); 
    delay(1000); 
  }
}

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
  Serial.begin(9600);
}

void loop() {

   Serial.println(counter);
  int statusSensor = digitalRead (IRSensor);
  strip.fill(strip.Color(strip.gamma8(minbrightness), 0, 0, strip.gamma8(minbrightness)));
  strip.show();  

//Build threshold for starting
  if (statusSensor == 1){
    counter++;
    }
  else{
    (counter=counter-1);
    if(counter<0){counter=0;}
  }
  if (counter>5){
    intro();
    setgo();
    Square();
    intro();
  }
delay(1000);  
}
//Change idle color if used a certain amount during the day reducing it to nothing if not used within 24hrs
//Create contiuation if 
// Move starting position to left side
