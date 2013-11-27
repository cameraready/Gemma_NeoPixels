// Low power NeoPixel earrings example.  Makes a nice blinky display
// with just a few LEDs on at any time...uses MUCH less juice than
// rainbow display!

#include <Adafruit_NeoPixel.h>

#define PIN 1
#define NUMPIX 10

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIX, PIN);

uint8_t  mode   = 0, // Current animation effect
         offset = 0; // Position of spinny eyes
uint32_t color  = 0xFFAE00; // Start color
uint32_t prevTime;

void setup() {
  pixels.begin();
  pixels.setBrightness(64); // 1/4 brightness
  prevTime = millis();
}

void loop() {
  uint8_t  i;
  uint32_t t;
  uint8_t  numPixOn = 3;

  switch(mode) {

   case 0: // Random sparks - just one LED on at a time!
    i = random(NUMPIX);
    pixels.setPixelColor(i, color);
    pixels.show();
    delay(10);
    pixels.setPixelColor(i, 0);
    break;
 
   case 1: // Spinny wheels 
    for(i=0; i<NUMPIX; i++) {
      uint32_t c = 0;
      if(((offset + i) & 7) < numPixOn) c = color; // use variable to set the number of pixels on during cycle
      pixels.setPixelColor( i, c); 
    }
    pixels.show();
    offset++;
    delay(50);
    break;
  }

  t = millis();
  if((t - prevTime) > 8000) {      // Every 8 seconds...
    mode++;                        // Next mode
    if(mode > 1) {                 // End of modes?
      mode = 0;                    // Start modes over
      color >>= 8;                 // Next color R->G->B
      if(!color) color = 0xFFAE00; //0xFF0000; // Reset to color
    }
    for(i=0; i<NUMPIX; i++) pixels.setPixelColor(i, 0); // clear all pixels
    prevTime = t;
  }
}
