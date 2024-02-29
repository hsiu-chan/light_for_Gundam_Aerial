class wakeupAnimation: public Effect
{
    
public:
    int wait;
    uint32_t color;
    wakeupAnimation(int wait,uint32_t color);
    void update();
};


wakeupAnimation::wakeupAnimation(int wait,uint32_t color){
    this->wait=wait;
    this->color=color;
    counter=Stript::strip->numPixels();
    last_millis=0;
};




void wakeupAnimation::update() {
    Serial.printf("counter:%d",counter);

    if (millis()-last_millis<wait){return;}
    //Stript::color_arr[Stript::strip->numPixels()-counter]=color;
    Stript::color_arr[0]=color;

    Serial.println(Stript::color_arr[0]);
    last_millis=millis();
    counter-=2;
}




wakeupAnimation animation= wakeupAnimation(200, Stript::strip->Color(255,0,0));
