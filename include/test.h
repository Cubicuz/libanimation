#include <Arduino.h>

template <int ledcount>
class containingFixedsizeArray {
    public:
        int stuff [ledcount];

};

containingFixedsizeArray<16> a;