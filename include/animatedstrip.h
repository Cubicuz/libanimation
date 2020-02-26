#ifndef ANIMATED_STRIP_H
#define ANIMATED_STRIP_H
#include <Arduino.h>
#include "animations.h"
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
template <uint32_t ledCount> class AnimatedStrip {
public:
  AnimatedStrip(){
    staticRainbow.animate = [this]{
      Animations::Static::rainbow(state, ledCount);
    };
  }
  void animate() { staticRainbow.animate(); }
  void setAnimation(void(*fkt));
  void setAnimation(const char *name);
  void setAnimation(int index);

  char **getAvailableAnimations();

  uint32_t getLedCount();
  uint32_t getSpeed();
  void setSpeed(uint32_t speed);
  uint32_t getResolution();
  void setResolution(uint32_t);
  void setSetPixelColor(void (*setPixelColor)(uint32_t, uint8_t, uint8_t,
                                              uint8_t)) {
    this->setPixelColor = setPixelColor;
  }

private:
  uint32_t progress;
  void (*setPixelColor)(uint32_t, uint8_t, uint8_t, uint8_t);
  uint8_t state[ledCount * 3];
  uint32_t speed;
  uint32_t resolution;

  // some kind of this will be needed
  struct AnimationListEntry {
    const char *name;
    std::function<void()> animate;
    AnimationListEntry *next;
  };
  AnimationListEntry* head;
  AnimationListEntry staticRainbow = {"staticrainbow"};

};

#endif // ANIMATED_STRIP_H