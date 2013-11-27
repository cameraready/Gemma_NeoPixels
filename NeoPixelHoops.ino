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
uint32_t arrows; // Define 3 steps for arrow animation

void setup() {
  pixels.begin();
  pixels.setBrightness(48); // brightness
  prevTime = millis();
}

void loop() {
  uint8_t  i;
  uint32_t t;
  uint8_t  numPixOn = 2;

  switch(mode) {

   case 0: // Random sparks - just one LED on at a time!
    i = random(NUMPIX*2); // 1/2 of pixels on?
    pixels.setPixelColor(i, color);
    pixels.show();
    delay(10);
    pixels.setPixelColor(i, 0);
    break;
 
   case 1: // Spinny wheels 
    for(i=0; i<NUMPIX; i++) {
      uint32_t c = 0;
      if(((offset + i) & 15) < numPixOn) c = color; // use variable to set the number of pixels on during cycle
      pixels.setPixelColor( i, c); 
    }
    pixels.show();
    offset++;
    delay(50);
    break;
    
    case 2: // Arrows animation
      arrows = 0b010101000100100010101000100100;
      uint32_t c = 0;
      for(i=0; i<3; i++) {
        for(uint8_t j=0; j<NUMPIX; j++) {
          if (arrows&1)
            c = 0x00FF00;
          else
            c = 0;
          pixels.setPixelColor( j, c);  // Solid green color
          arrows >>= 1;
        }
      pixels.show();
      delay(150);
      }
  }

  t = millis();
  if((t - prevTime) > 8000) {      // Every 8 seconds...
    mode++;                        // Next mode
    if(mode > 2) {                 // End of modes?
      mode = 0;                    // Start modes over
      color >>= 8;                 // Next color R->G->B
      if(!color) color = 0xFFAE00; //0xFF0000; // Reset to color
    }
    for(i=0; i<NUMPIX; i++) pixels.setPixelColor(i, 0); // clear all pixels
    prevTime = t;
  }
}
