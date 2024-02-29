
#include "Stript.h"
#include "Arduino.h"

#include "Effect.h"






uint32_t Wheel(byte WheelPos, byte saturation) {
    WheelPos = 255 - WheelPos;
    byte r, g, b;
    if (WheelPos < 85) {
        r = 255 - WheelPos * 3;
        g = 0;
        b = WheelPos * 3;
    }
    else if (WheelPos < 170) {
        WheelPos -= 85;
        r = 0;
        g = WheelPos * 3;
        b = 255 - WheelPos * 3;
    }
    else {
        WheelPos -= 170;
        r = WheelPos * 3;
        g = 255 - WheelPos * 3;
        b = 0;
    }

    r = map(r, 0, 255, 255 - saturation, 255);
    g = map(g, 0, 255, 255 - saturation, 255);
    b = map(b, 0, 255, 255 - saturation, 255);

    return Stript::strip->Color(r, g, b);
}

void rainbowEffect(int wait, byte saturation) {
        uint16_t i, j;

    for(j=0; j<256; j++) { 
        for(i=0; i<Stript::strip->numPixels(); i++) {
            Stript::strip->setPixelColor(i, Wheel(((i * 256 / Stript::strip->numPixels()) + j) & 255, saturation));
        }
        delay(wait);
        Stript::strip->show();
    }
}


void wakeupEffect(int wait, uint32_t color) {
    static uint32_t lastMillis = 0;
    uint8_t i = 0;
    while (i<Stript::strip->numPixels())
    {
        if (millis() - lastMillis >= wait) {
        Stript::color_arr[i]=color;
        Stript::update();
        i++;
        lastMillis = millis();
        }
    }
    

    
}







void shutdownEffect(int wait) {
    static uint32_t lastMillis = 0;
    static int i = 0;
    while (i<Stript::strip->numPixels())
    {
        if (millis() - lastMillis >= wait) {
            Stript::color_arr[Stript::strip->numPixels() - i - 1]=0; 
            Stript::update(); 
            i++;
            lastMillis = millis();
        }
    }
}
