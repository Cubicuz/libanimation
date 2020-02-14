#include <Arduino.h>
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
template<uint ledCount>
class AnimatedStrip{
private:
  const uint16_t ledCount;
  uint8_t progress;
  void (*setPixelColor)(uint16_t, uint8_t, uint8_t, uint8_t);
  uint8_t state [ledCount];
  uint32_t speed;
  uint32_t resolution;
public:
  void animate();
  setAnimation(void (*fkt));
  setAnimation(const char* name);
  setAnimation(int index);
};

// some kind of this will be needed
class Animation{
  const char* name;
  void animate();
};