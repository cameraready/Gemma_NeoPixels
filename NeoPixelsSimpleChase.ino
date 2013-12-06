// Low power NeoPixel earrings example.  Makes a nice blinky display
// with just a few LEDs on at any time...uses MUCH less juice than
// rainbow display!

#include <Adafruit_NeoPixel.h>

#define PIN 1
#define NUMPIX 10

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIX, PIN);

uint32_t offset = 0; // Position of spinny eyes
uint32_t color  = 0xFF0000; // Start color
uint32_t prevTime;
uint8_t  numPixOn = 2;

void setup() {
  pixels.begin();
  pixels.setBrightness(48); // brightness
}

void loop() {
  uint8_t  i;
  uint32_t t;
 
    for(i=0; i<NUMPIX; i++) {
      uint32_t c = 0;
      if((((offset + i)%NUMPIX) & 0xF) < numPixOn) c = color; // use variable to set the number of pixels on during cycle
      pixels.setPixelColor( i, c); 
    }
    pixels.show();
    offset++;
    delay(75);
    
  t = millis();
  if((t - prevTime) > 8000) {    // Every 8 seconds...
    color >>= 8;                 // Next color R->G->B
    if(!color) color = 0xFF0000; //0xFFAE00; Reset to color
    prevTime = t;
  }
}
