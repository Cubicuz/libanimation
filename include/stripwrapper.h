#ifndef STRIP_WRAPPER
#define STRIP_WRAPPER
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

class StripWrapper{
public:
    // Todo: auslagern

    // Names of the available animations
    const char * const RAINBOW = "rainbow";
    const char * const SOLID = "solid";
    const char * const RAINBOWMOVING = "rainbowmoving";
    const char * const RAIN = "rain";

    // Can be modified by you, if you wish to exclude some animations
    const char * const availableAnimations[4] = {SOLID, RAINBOW, RAINBOWMOVING, RAIN};

    void setColor(uint8_t r, uint8_t g, uint8_t b);
    void setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t w);
    void setWhite(uint8_t w);

    void setBrightness(uint8_t brightness);
    uint8_t getBrightness();

    // needs to be called periodically, produces the next animation step
    void animate();

    void setAnimation(const char * const functionName);
    const char* const getAnimation();

    StripWrapper(uint32_t numPixel, uint8_t* memory = NULL);

    StripWrapper(Adafruit_NeoPixel* strip, uint8_t* memory = NULL);

    ~StripWrapper();
    
private:
    uint8_t r, g, b, w;
    uint8_t brightness;

    uint32_t numPixel;
    uint8_t *memory;
    bool memory_self_managed;
    uint32_t progress;
    const char * activeAnimation;
    bool doAnimate; // static animations set this to false so they dont flicker

    Adafruit_NeoPixel* strip;

    // Todo: implement rgb only
    bool warmwhite;
};

#endif