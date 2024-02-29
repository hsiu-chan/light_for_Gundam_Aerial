#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
#include <HomeSpan.h>         // HomeSpan sketches always begin by including the HomeSpan library
#include <list>

#include "main.h"
#include "Stript.h"
#include "Effect.h"
#include "ColorConverter.h"


const char pairing_code[] = "20030707";
const char* ssid = "WI-FI_2.4G";
const char* password = "hsiu112358";
uint32_t MAIN_COLOR;
uint32_t LAST_COLOR;




// 槍與背包的燈
struct LEDBlub : Service::LightBulb {      // Addressable single-wire RGB LED Strand (e.g. NeoPixel)
  Characteristic::On power{0,true};
  Characteristic::Brightness L{100,true};

  LEDBlub():Service::LightBulb()
  {
    L.setRange(0,255,1);// sets the range of the Brightness to be from a min of 5%, to a max of 100%, in steps of 1%
    update(); 
    
  }

  boolean update() override 
  {
    if (power.getNewVal()==0){
      analogWrite(GUN_LED_PIN, 255);
      return (true);
    }
    int l=L.getNewVal<float>();
    Serial.printf("光束槍: %d\n",l);
    analogWrite(GUN_LED_PIN, 255-l);
    return(true); 
  }


};

// RGB 燈帶
struct RGB_LED : Service::LightBulb {      // Addressable single-wire RGB LED Strand (e.g. NeoPixel)
  Characteristic::On power{0,true};
  Characteristic::Hue H{0,true};
  Characteristic::Saturation S{0,true};
  Characteristic::Brightness L{100,true};

  RGB_LED():Service::LightBulb()
  {
    L.setRange(0,100,1);// sets the range of the Brightness to be from a min of 5%, to a max of 100%, in steps of 1%
    update(); 
    
  }

  boolean update() override 
  {
    if (power.getNewVal()==0){
      //shutdownEffect(300);
      Shutdown *shutdownEffect = new Shutdown(50);
      Stript::add_effect(shutdownEffect);

      return (true);
    }
    float h=H.getNewVal<float>();       
    float s=S.getNewVal<float>()/100;       
    float l=L.getNewVal<float>()/200;
    MAIN_COLOR = hsl2RGB(h,s,l);

    
    Wakeup *wakeupEffect = new Wakeup(50, MAIN_COLOR);
    Stript::add_effect(wakeupEffect);

    Serial.printf("刻痕: %d\n",MAIN_COLOR);
    Serial.printf("[%d,%d]\n",Stript::color_arr[0],Stript::color_arr[1]);


    return(true);  
  }

};









void setup() {
  Serial.begin(115200);

   // 配置引脚为输出模式
  pinMode(GUN_LED_PIN, OUTPUT); // 槍、腿後、背

  Stript::initStript();
  Stript::strip->fill(0);
  Stript::strip->show();

  //a=Wakeup(200, Stript::strip->Color(255,0,0));
  //addeffect(&a);
  // homespan 初始化
  homeSpan.begin(Category::Lighting,"風靈");
  homeSpan.setWifiCredentials(ssid, password);
  homeSpan.setPairingCode(pairing_code);


  SPAN_ACCESSORY(); // create Bridge 
  SPAN_ACCESSORY("光束槍");
    new LEDBlub();
  SPAN_ACCESSORY("刻痕");
    new RGB_LED();

  //Serial.printf("add counter:%d\n", animation.counter);
}

void loop() {
  homeSpan.poll();
  //animation.update();
  //update_effect();

  Stript::update();
  delay(10);
  


  
  //Effect::rainbowEffect(10, 200);

  //Effect::shutdownEffect(500);

}
