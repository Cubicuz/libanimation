
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

struct Animation{
  const uint16_t ledCount;
  uint8_t progress;
  void (*setPixelColor)(uint16_t, uint8_t, uint8_t, uint8_t);
  uint8_t *state; // maybe a define can help here
};

//#define ANIMATION(numLeds, fkt) { (numLeds), 0, (fkt), (int[numLeds * 3])}

struct NameAndFunction {
  const char* name;
  void *fkt(Animation);
} availableAnimations[5];

void animate(Animation anim);

void setFunction(Animation anim, int index);

void setFunction(Animation anim, const char* name);

void setFunction(Animation anim, void (*fkt));

void initAnimation(Animation anim);
