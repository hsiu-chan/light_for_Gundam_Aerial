#ifndef STRIPT_H
#define STRIPT_H

#include <Adafruit_NeoPixel.h>

#include <Adafruit_NeoPixel.h>
#include <list>

#include "main.h"



class Effect {
    public:
        uint8_t counter;
        unsigned long last_millis;        
        virtual void update(){
            this->counter--;
            last_millis=millis();
        }
        Effect(): last_millis(0), counter(0){}
};

extern std::list<Effect*> effects; // 声明 effects，不要进行定义


class Stript {
private:
public:

    static Adafruit_NeoPixel* strip; // 声明为静态成员变量
    static uint32_t color_arr[LED_COUNT];
    static boolean power; 

    static void initStript();
    static void update();
    static void fill(uint32_t color);
    static void add_effect(Effect *effect);
    static void clear_effect();
};


#endif
