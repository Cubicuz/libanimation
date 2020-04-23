#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include <Arduino.h>

// having the animation functions inside the template class AnimatedStrip
// may lead the compiler to generate a seperate function for every instantiated
// ledCount but i have to test this and it results in a large, meh readable
// file, witch i dont like

namespace Animations {

namespace Static {
void rainbow(
    std::function<void(uint32_t, uint8_t, uint8_t, uint8_t)> setPixelColor,
    uint32_t ledCount);

/**
 * memory musst be at least 3*ledCount in size, colormode rgb
 * */
void rainbow(uint8_t *memory, uint32_t ledCount);

} // namespace Static

namespace Dynamic {
void rainbow(
    std::function<void(uint32_t, uint8_t, uint8_t, uint8_t)> setPixelColor,
    uint32_t ledCount, uint32_t &progress, uint32_t resolutionFactor);

/**
 * memory musst be at least 3*ledCount in size, colormode rgb
 * */
void rainbow(uint8_t *memory, uint32_t ledCount, uint32_t progress,
             uint32_t resolutionFactor = 32);

/**
 * memory: musst be at least ledCount in size, is meant for blue only
 * dropRadius: radius of a raindrop, 2 means drop is three leds width
 * dropCountDivisor: larger means less drops
 * reduction: reduce intensity per animate
 * */
void rain(uint8_t *memory, uint32_t ledCount, uint8_t dropRadius = 2,
          uint32_t dropCountDivisor = 30, uint8_t reduction = 1);

void sort(uint8_t *memory, uint32_t ledCount);
} // namespace Dynamic

namespace Helper {
uint8_t wheel(uint32_t x, uint32_t resolution);
} // namespace Helper

} // namespace Animations

#endif // ANIMATIONS_H