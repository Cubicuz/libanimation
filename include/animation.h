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
private:
  uint32_t progress;
  void (*setPixelColor)(uint32_t, uint8_t, uint8_t, uint8_t);
  uint8_t state [ledCount*3];
  uint32_t speed;
  uint32_t resolution;

public:

  void animate(){
    rainbow();
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
    for (uint32_t i = 0; i < ledCount; i++){
      setPixelColor(i, wheel(i, ledCount), wheel((i+ledCount/3)%ledCount, ledCount), wheel((i+ledCount*2/3)%ledCount, ledCount));
    }
  }



};

// some kind of this will be needed
class Animation{
  const char* name;
  void animate();
};