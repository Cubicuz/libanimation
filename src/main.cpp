#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "test.h"
#include "animation.h"

#define NUM_LEDS 30
#define DATA_PIN 0 

Adafruit_NeoPixel strip(NUM_LEDS, DATA_PIN, NEO_GRBW + NEO_KHZ800);


AnimatedStrip<29> animStrip;

void mySetPixelColor(uint32_t i, uint8_t r, uint8_t g, uint8_t b){
  strip.setPixelColor(i, r, g, b, 0);
  Serial.print(r);
  Serial.print(" ");
  Serial.print(g);
  Serial.print(" ");
  Serial.println(b);
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(19200);
  Serial.println("Start");
  strip.begin();
  animStrip.setSetPixelColor(&mySetPixelColor);
  animStrip.animate();
  strip.show();


}

void loop()
{
}

