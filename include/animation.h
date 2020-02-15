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
  void animate();
  void setAnimation(void (*fkt));
  void setAnimation(const char* name);
  void setAnimation(int index);


  uint32_t getLedCount();
  uint32_t getSpeed();
  void setSpeed(uint32_t speed);
  uint32_t getResolution();
  void setResolution(uint32_t);
};

// some kind of this will be needed
class Animation{
  const char* name;
  void animate();
};