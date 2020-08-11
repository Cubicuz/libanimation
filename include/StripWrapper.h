#ifndef STRIPWRAPPER_HEADER_GUARD
#define STRIPWRAPPER_HEADER_GUARD
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

class StripWrapper
{
public:
    // Todo: auslagern

    //constexpr char WAVE = "wave";

    // Names of the available animations
    static const char *const KNIGHTRIDER;
    static const char *const SOLID;
    static const char *const RAIN;
    static const char *const RAINBOW;
    static const char *const RAINBOWMOVING;

    // Can be modified by you, if you wish to exclude some animations
    const char *const availableAnimations[5] = {SOLID, KNIGHTRIDER, RAINBOW, RAINBOWMOVING, RAIN};
    const uint8_t availableAnimationCount = sizeof(availableAnimations);


    void setColor(uint8_t r, uint8_t g, uint8_t b);
    void setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t w);
    void setWhite(uint8_t w);

    void setBrightness(uint8_t brightness);
    uint8_t getBrightness();

    // needs to be called periodically, produces the next animation step
    void animate();

    const char * sameAnimationNameButMyPointer(const char *const functionName);
    void setAnimation(const char *const functionName);
    const char *const getAnimation();

    StripWrapper(uint32_t numPixel, uint8_t *memory = NULL);

    StripWrapper(Adafruit_NeoPixel *strip, uint8_t *memory = NULL);

    ~StripWrapper();

private:
    uint8_t r, g, b, w;
    uint8_t brightness;

    uint32_t numPixel;
    uint8_t *memory;
    bool memory_self_managed;
    uint32_t progress;
    const char *activeAnimation;
    bool doAnimate; // static animations set this to false so they dont flicker

    Adafruit_NeoPixel *strip;

    // Todo: implement rgb only
    bool warmwhite;
};

#endif // STRIPWRAPPER_HEADER_GUARD