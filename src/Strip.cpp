#include <list>

#include "Effect.h"
#include "Stript.h"
#include "main.h"

Adafruit_NeoPixel* Stript::strip = nullptr; // 初始化为 nullptr

boolean Stript::power=true;

uint32_t Stript::color_arr[LED_COUNT] = {0};
std::list<Effect*> effects;



void Stript::initStript() {
    // 创建 NeoPixel 对象
    strip = new Adafruit_NeoPixel(LED_COUNT, RGB_LED_PIN, NEO_GRB + NEO_KHZ800);
    fill(0);
    clear_effect();
    strip->begin();
}


void Stript::update() {
    //開關
    if (!power){
        strip->fill(0);
        return;
    }
    
    // 畫 effects
    auto it = effects.begin();
    while (it != effects.end()) {
        Effect* currentEffect = *it;
        if (currentEffect->counter == 0) {
        //delete currentEffect; // 删除指针所指向的对象
        it = effects.erase(it); // 删除元素并更新迭代器
        } else {
        currentEffect->update();
        ++it;
        }
    }
    
    // 畫 stript
    for (uint16_t i = 0; i < LED_COUNT; i++) {
        if (color_arr[i]==-1){continue;}
        strip->setPixelColor(i,color_arr[i]);
    }
    strip->show();
}


void Stript::fill(uint32_t color) {
    for (uint8_t i=0; i<LED_COUNT; i++){
        color_arr[i]=color;
    }
}


void Stript::add_effect(Effect *effect){
    effects.push_back(effect);
}

void Stript::clear_effect(){
    effects.clear();
}
