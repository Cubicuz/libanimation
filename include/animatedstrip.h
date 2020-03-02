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
#define _DEBUG_
#ifdef _DEBUG_
  #define DEBUG_ERROR(message) Serial.print(message)
#else
  #define DEBUG_ERROR
#endif

template <uint32_t ledCount> class AnimatedStrip {
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
  AnimationListEntry* head = NULL; // rename this !!!
  AnimationListEntry staticRainbow = {"rainbow"};
  AnimationListEntry dynamicRainbow = {"rainbowmoving"};

public:
  AnimatedStrip(){
    staticRainbow.animate = [this]{
      Animations::Static::rainbow(state, ledCount);
    };
  };
  AnimatedStrip* addAnimation(AnimationListEntry* ale){
    if (ale->next){
      DEBUG_ERROR("dont add an animation twice");
      return this;
    }
    AnimationListEntry **iter = &head;
    while(*iter != NULL){
      iter = &(**iter.next);
    }
    *iter = ale;

    return this;
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


};

#endif // ANIMATED_STRIP_H