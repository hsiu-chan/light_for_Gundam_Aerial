#ifndef EFFECT_H
#define EFFECT_H

#include "Stript.h"
#include "Arduino.h"


void rainbowEffect(int wait, byte saturation);
void wakeupEffect(int wait, uint32_t color);
void shutdownEffect(int wait);





class Wakeup :public Effect {
  public:
  int wait;
  uint32_t color;
  Wakeup(){}
  Wakeup(int wait, uint32_t color){
    this->wait=wait;
    this->color=color;
    last_millis=0;
    counter=LED_COUNT;
  }
  void update() override{
    unsigned long currentMillis = millis();

    if (currentMillis-last_millis<wait){return;}
    if (counter>0){

      Serial.print(counter);
      Stript::color_arr[LED_COUNT-counter]=color;
      

      counter-=1;
      last_millis=currentMillis;
    }


  }

};




class Shutdown :public Effect {
    private:
    int wait;


    public:
    Shutdown(){}
    Shutdown(int wait){
        this->wait=wait;
        last_millis=0;
        counter=LED_COUNT;
    }
    void update() override{
        unsigned long currentMillis = millis();

        if (currentMillis-last_millis<wait){return;}
        if (counter>0){

        Serial.print(counter);
        Stript::color_arr[counter-1]=0;
        

        counter-=1;
        last_millis=currentMillis;
        }


    }

};







#endif
