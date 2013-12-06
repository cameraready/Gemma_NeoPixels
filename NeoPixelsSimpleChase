// Low power NeoPixel earrings example.  Makes a nice blinky display
// with just a few LEDs on at any time...uses MUCH less juice than
// rainbow display!

#include <Adafruit_NeoPixel.h>

#define PIN 1
#define NUMPIX 10

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIX, PIN);

uint8_t  offset = 0; // Position of spinny eyes
uint32_t color  = 0xFFAE00; // Start color
uint32_t prevTime;

void setup() {
  pixels.begin();
  pixels.setBrightness(48); // brightness
}

void loop() {
  uint8_t  i;
  uint32_t t;
  uint8_t  numPixOn = 2;
 
    for(i=0; i<NUMPIX; i++) {
      uint32_t c = 0;
      if(((offset + i) & 0xF) < numPixOn) c = color; // use variable to set the number of pixels on during cycle
      pixels.setPixelColor( i, c); 
    }
    pixels.show();
    offset++;
    delay(50);
    
  t = millis();
  if((t - prevTime) > 8000) {      // Every 8 seconds...
    color >>= 8;                 // Next color R->G->B
    if(!color) color = 0xFFAE00; //0xFF0000; // Reset to color
    for(i=0; i<NUMPIX; i++) pixels.setPixelColor(i, 0); // clear all pixels
    prevTime = t;
  }
}
