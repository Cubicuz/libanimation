#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define NUM_LEDS 30
#define DATA_PIN 5 // this is D1 because of reasons

Adafruit_NeoPixel strip(NUM_LEDS, DATA_PIN, NEO_GRBW + NEO_KHZ800);

uint8_t wheel(uint16_t x, uint16_t resolution);


void setup()
{

  // put your setup code here, to run once:
  Serial.begin(19200);
  Serial.println("Start");
  strip.begin();
  strip.show();
  strip.setPixelColor(1, 255, 0, 0, 0);
  strip.setPixelColor(2, 0, 255, 0, 0);
  strip.setPixelColor(3, 0, 0, 255, 0);
  strip.setPixelColor(4, 0, 0, 0, 255);
  strip.show();
  for (uint16_t i=0;i<NUM_LEDS;i++){
    uint8_t red = wheel(i, NUM_LEDS);
    strip.setPixelColor(i, red, wheel((i+10)%NUM_LEDS, NUM_LEDS), wheel((i+20)%NUM_LEDS, NUM_LEDS), 0);
    Serial.print(i);
    Serial.print(" : ");
    Serial.println(red);
  }
  strip.show();

}

void loop()
{
}

uint8_t wheel(uint16_t x, uint16_t resolution){
  
  // function looks like ／￣￣＼＿＿
  // is splittet in 4 parts (rising 0, high 1-2, falling 3, low 4-5)

  if (x*6 < resolution)           // x < 1/6 * resolution
  { // rising
    return 255*6*x/resolution/2;   // 255 * x / (resolution / 6)
  } else if (x*2 < 1*resolution)  // x < 3/6 * resolution
  { // high
    return 255;
  } else if (x*3 < 2*resolution)  // x < 4/6 * resolution
  { // falling
    return (4*255 - 6*x*255/resolution)/2 ;
  } else 
  { // low
    return 0;
  }
  
}

void rainbow(){

}
