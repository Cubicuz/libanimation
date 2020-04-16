#include "stripwrapper.h"
#include <Adafruit_NeoPixel.h>
#include "animations.h"

void StripWrapper::setColor(uint8_t r, uint8_t g, uint8_t b){
    this->r = r;
    this->g = g;
    this->b = b;
    doAnimate = true;
}

void StripWrapper::setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t w){
    this->r = r;
    this->g = g;
    this->b = b;
    this->w = w;
    doAnimate = true;
}

void StripWrapper::setWhite(uint8_t w){
    this->w = w;
    doAnimate = true;
}

void StripWrapper::setBrightness(uint8_t brightness){
    this->brightness = brightness;
    doAnimate = true;
}

uint8_t StripWrapper::getBrightness(){
    return brightness;
}

void StripWrapper::animate(){
    if (!doAnimate){
        return;
    }
    auto lambda = [this] (uint32_t i, uint8_t r, uint8_t g, uint8_t b) {
                strip->setPixelColor(i, r, g, b);
                };
    if (activeAnimation != NULL){
        if (activeAnimation == SOLID){
            doAnimate = false;
            for (uint32_t i = 0; i<numPixel;i++){
                strip->setPixelColor(i, r, g, b);
            }
            strip->show();

        } else if (activeAnimation == RAINBOW){
            doAnimate = false;
            Animations::Static::rainbow([this] (uint32_t i, uint8_t r, uint8_t g, uint8_t b) {
                strip->setPixelColor(i, r, g, b);
                }, numPixel);
            strip->show();

        } else if (activeAnimation == RAINBOWMOVING){
            Animations::Dynamic::rainbow([this] (uint32_t i, uint8_t r, uint8_t g, uint8_t b) {
                strip->setPixelColor(i, r, g, b);
                }, numPixel, progress, 4);
            strip->show();

        } else if (activeAnimation == RAIN){
            Animations::Dynamic::rain(memory, numPixel);
            for (uint32_t i=0; i < numPixel, i++){
                strip->setPixelColor(i, 0, 0, memory[i]);
            }
            strip->show();

        } else {
            Serial.print("unsupported animation: ");
            Serial.println(activeAnimation);
        }
    } else {
        Serial.println("no animation selected");
    }
}

void StripWrapper::setAnimation(const char * const functionName){
    doAnimate = true;
    activeAnimation = functionName;
    if (functionName == SOLID){

    } else if (functionName == RAINBOW){

    } else if (functionName == RAINBOWMOVING){

    } else if (functionName == RAIN){
        for (uint32_t i=0;i<numPixel;i++){
            memory[i] = 0;
        }
    } else {
        this->activeAnimation = NULL;
        Serial.print("unsupported animation: ");
        Serial.println(functionName);
    }
    if (strip == NULL){
        Serial.println("wrong constructor");
    }
}

char const * const StripWrapper::getAnimation(){
    return activeAnimation;
}

StripWrapper::StripWrapper(uint32_t numPixel, uint8_t* memory){
    if (memory == NULL){
        memory = new uint8_t [numPixel * 4];
        memory_self_managed = true;
    } else {
        memory_self_managed = false;
    }
    doAnimate = true;
}

StripWrapper::StripWrapper(Adafruit_NeoPixel* strip, uint8_t* memory){
    Serial.println("create Stripwrapper with NeoPixel Ref");
    this->strip = strip;
    numPixel = strip->numPixels();
    if (memory == NULL){
        memory = new uint8_t [strip->numPixels() * 4];
        memory_self_managed = true;
    } else {
        memory_self_managed = false;
    }
    doAnimate = true;
}

StripWrapper::~StripWrapper(){
    if (memory_self_managed){
        delete[] memory;
    }
}
