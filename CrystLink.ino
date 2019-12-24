// This #include statement was automatically added by the Particle IDE.
#include <neopixel.h>

/**
 * This is a minimal example, see extra-examples.cpp for a version
 * with more explantory documentation, example routines, how to
 * hook up your pixels and all of the pixel types that are supported.
 *
 * On Photon, Electron, P1, Core and Duo, any pin can be used for Neopixel.
 *
 * On the Argon, Boron and Xenon, only these pins can be used for Neopixel:
 * - D2, D3, A4, A5
 * - D4, D6, D7, D8
 * - A0, A1, A2, A3
 *
 * In addition on the Argon/Boron/Xenon, only one pin per group can be used at a time.
 * So it's OK to have one Adafruit_NeoPixel instance on pin D2 and another one on pin
 * A2, but it's not possible to have one on pin A0 and another one on pin A1.
 */

#include "Particle.h"
#include "neopixel.h"

SYSTEM_MODE(AUTOMATIC);

// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIXEL_PIN D7
#define PIXEL_COUNT 64
#define PIXEL_TYPE WS2812B

String mode = "off";
int r = 255;
int g = 0;
int b = 0;
int a = 50;

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

// Prototypes for local build, ok to leave in for Build IDE
void rainbow(uint8_t wait);
uint32_t Wheel(byte WheelPos);

void setup()
{
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Particle.variable("mode", &mode, STRING);
  Particle.variable("r", &r, INT);
  Particle.variable("g", &g, INT);
  Particle.variable("b", &b, INT);
  Particle.variable("a", &a, INT);
//   Particle.function("setMode", setMode);
  Particle.function("setColorR", setColorR);
  Particle.function("setColorG", setColorG);
  Particle.function("setColorB", setColorB);
  Particle.function("setColorA", setColorA);
//   Particle.function("setColor", setColor);
}

void loop()
{
  if (mode == "solid") {
    colorAll(strip.Color(r, g, b), a);
  } else if (mode == "rainbow") {
    strip.clear();
    rainbow(20);
  } else {
    strip.clear();
    strip.show();
  }
  
}

// int setColor(String r, String g, String b, String a) {
//     return 1;
// }

int setColorR(String color) {
    r = color.toInt();
    return 1;
}

int setColorG(String color) {
    g = color.toInt();
    return 1;
}

int setColorB(String color) {
    b = color.toInt();
    return 1;
}

int setColorA(String color) {
    a = color.toInt();
    return 1;
}

int setMode(String givenMode) {
    mode = givenMode;
    return 1;
}

// Set all pixels in the strip to a solid color, then wait (ms)
void colorAll(uint32_t c, uint8_t wait) {
  uint16_t i;

  for(i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
  }
  strip.show();
  delay(wait);
}


// Rainbow
void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    if (mode == "rainbow") {
        for(i=0; i<strip.numPixels(); i++) {
          strip.setPixelColor(i, Wheel((i+j) & 255));
        }
    strip.show();
    delay(wait);
    }
  }
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

