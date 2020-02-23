#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include <Arduino.h>

// having the animation functions inside the template class AnimatedStrip 
// may lead the compiler to generate a seperate function for every instantiated ledCount
// but i have to test this
// and it results in a large, meh readable file, witch i dont like

namespace Animations{

    void rainbow();

    namespace Helpers
    {
        uint8_t wheel(uint32_t x, uint32_t resolution);
    } // namespace Helpers
    
}

#endif //ANIMATIONS_H