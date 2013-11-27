// Adapted from the 'Firewalker' LED sneakers sketch for Adafruit NeoPixels by Phillip Burgess
// Designed for a string of 8 neopixels to continuously rotate based on the firewalker color blends.
 
#include <Adafruit_NeoPixel.h>
 
uint8_t gamma[] PROGMEM = { // Gamma correction table for LED brightness
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
    2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
    5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
   10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
   17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
   25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
   37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
   51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
   69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
   90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
  115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
  144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
  177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
  215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255 };
 
// Removed references to shoes and related code
#define N_LEDS        10 // TOTAL number of LEDs in strip
#define LED_PIN        1 // NeoPixel strip is connected here
 
Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);
 
int mag[N_LEDS]; // Brightness buffer
uint8_t  offset; // Position of wave
 
 
void setup() {
  offset = 0;
  strip.begin();
  strip.setBrightness(64); // 1/4 brightness 
}
 
void loop() {
  uint8_t i;

  mag[0] = 50;
  mag[1] = 100;
  mag[2] = 250;
  mag[3] = 400;
  mag[4] = 600;
  mag[5] = 800;
  mag[6] = 500;
  mag[7] = 300;
  mag[8] = 150;
  mag[9] = 50;
 
  // Now the grayscale magnitude buffer is remapped to color for the LEDs.
  // The code below uses a blackbody palette, which fades from white to yellow
  // to red to black.  The goal here was specifically a "walking on fire"
  // aesthetic, so the usual ostentatious rainbow of hues seen in most LED
  // projects is purposefully skipped in favor of a more plain effect.
  uint8_t r, g, b;
  int     level;
  for(i=0; i<N_LEDS; i++) { // For each LED...
    level = mag[((offset + i) % N_LEDS)];                // Pixel magnitude (brightness)
    if(level < 255) {              // 0-254 = black to red-1
      r = pgm_read_byte(&gamma[level]);
      g = b = 0;
    } else if(level < 510) {       // 255-509 = red to yellow-1
      r = 255;
      g = pgm_read_byte(&gamma[level - 255]);
      b = 0;
    } else if(level < 765) {       // 510-764 = yellow to white-1
      r = g = 255;
      b = pgm_read_byte(&gamma[level - 510]);
    } else {                       // 765+ = white
      r = g = b = 255;
    }
    // Set R/G/B color along outside of shoe
    strip.setPixelColor(i, r, g, b);
  }
 
  offset++;
  strip.show();
  delay(75);
}
