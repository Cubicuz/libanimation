#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include <Arduino.h>

namespace Animations{

    void rainbow();

    namespace Helpers
    {
        uint8_t wheel(uint32_t x, uint32_t resolution);
    } // namespace Helpers
    
}

#endif //ANIMATIONS_H