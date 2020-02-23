#ifndef ANIMATED_STRIP_H
#define ANIMATED_STRIP_H
#include <Arduino.h>
#include <vector>
/*
 * wants: 
 *  mapping name -> functionpointer
 *  string array containing function names
 *  timerindependant
 *  ref to led memory
 *    bitcount
 *    ledcount
 *      since most animations dont utilize white chanel, ignore it at first
 *    LED-independant
 *  structoriented
 *  selectedFunction
 *  currentAnimationState
 *  JSON containing Animation names for autodiscovery
 */
template<uint32_t ledCount>
class AnimatedStrip{
public:

  
  void animate(){
    rain();
  }
  void setAnimation(void (*fkt));
  void setAnimation(const char* name);
  void setAnimation(int index);

  char ** getAvailableAnimations();

  uint32_t getLedCount();
  uint32_t getSpeed();
  void setSpeed(uint32_t speed);
  uint32_t getResolution();
  void setResolution(uint32_t);
  void setSetPixelColor(void (*setPixelColor)(uint32_t, uint8_t, uint8_t, uint8_t)){
    this->setPixelColor = setPixelColor;
  }

private:
  uint32_t progress;
  void (*setPixelColor)(uint32_t, uint8_t, uint8_t, uint8_t);
  uint8_t state [ledCount*3];
  uint32_t speed;
  uint32_t resolution;

  // some kind of this will be needed
  struct AnimationListEntry{
    const char* name;
    std::function<void()> animate;
    AnimationListEntry* next;
  };

// ----------------- Helper functions
  uint8_t wheel(uint32_t x, uint32_t resolution){
    // function looks like ／￣￣＼＿＿
    // is splittet in 4 parts (rising 0, high 1-2, falling 3, low 4-5)

    if (x*6 < resolution)           // x < 1/6 * resolution
    { // rising
      return 255*6*x/resolution;   // 255 * x / (resolution / 6)
    } else if (x*2 < 1*resolution)  // x < 3/6 * resolution
    { // high
      return 255;
    } else if (x*3 < 2*resolution)  // x < 4/6 * resolution
    { // falling
      return (4*255 - 6*x*255/resolution) ;
    } else 
    { // low
      return 0;
    }
  }

// ----------------- Animation functions
  void rain(){
    const uint8_t reduction = 1;  // reduce intensity per animate

    const uint32_t dropCountDivisor = 30;
    const uint8_t dropRadius = 2; // radius of a raindrop, 2 means drop is three leds width

    // evaporate
    for (uint32_t i = 0; i<ledCount*3;i++){
      if (state[i] > reduction){
        state[i] -= reduction;
      } else {
        state[i] = 0;
      }
    }

    // new drops
    uint32_t drops = random(0, max(1U, ledCount/dropCountDivisor)*33)>>5;
    for (uint32_t i=0;i<drops;i++){
      uint32_t position = random(dropRadius-1, ledCount-dropRadius+1);
      Serial.println(position);
      uint8_t increment = 255;
      state[position] = increment;
      for (uint8_t j=1;j<dropRadius;j++){
        increment /= 2;
        state[position+j] = min(255, state[position+j]+increment);
        state[position-j] = min(255, state[position-j]+increment);
      }
    }
    for (uint32_t i=0;i<ledCount;i++){
      setPixelColor(i, 0, 0, state[i]);
    }
  }

  void rainbow(){
    for (uint32_t i = 0; i < ledCount; i++){
      setPixelColor(i, wheel(i, ledCount), wheel((i+ledCount/3)%ledCount, ledCount), wheel((i+ledCount*2/3)%ledCount, ledCount));
    }
  }

  void rainbowMoving(){
    const uint32_t resolutionFactor = 32;
    const uint32_t resolution = ledCount * resolutionFactor;
    progress = (progress + 1) % resolution;
    for (uint32_t i = 0; i<ledCount; i++){
      uint32_t index = i*resolutionFactor+progress;
      uint32_t offset = resolution / 3;
      uint8_t r = wheel(index%resolution, resolution);
      uint8_t g = wheel((index+offset)%resolution, resolution);
      uint8_t b = wheel((index+2*offset)%resolution, resolution);
      setPixelColor(i, r, g, b);
 /*     if (1 == 0){
            Serial.print(index);
            Serial.print(" ");
            Serial.print(r);
            Serial.print(" ");
            Serial.print(g);
            Serial.print(" ");
            Serial.println(b);
      }
*/    }
  }



};

#endif // ANIMATED_STRIP_H