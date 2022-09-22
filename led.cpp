#include "led.h"

led::led(int Pin){
  pin = Pin;
}

void led::doLed(){
  if(state == 0){
    analogWrite(pin,0);
  }
   else if(state == 1){
    analogWrite(pin,brightnes);
  }
  else if(state == 2 && millis() - timer > frequency){
    if(light)analogWrite(pin,0);
    else analogWrite(pin,brightnes);
    light = !light;
    timer = millis();
  }
    else if(state == 3 && millis() - timer > fadeInOut){
    fadeInOut = brightnes - minimal / 100;
    if(light)analogWrite(pin,0);
    else analogWrite(pin,brightnes);
    light = !light;
    timer = millis();
  }

    else if(state == 4 && millis() - timer > frequency){
    if(light)analogWrite(pin,0);
    else analogWrite(pin,brightnes);
    light = !light;
    timer = millis();
  }
}

void led::config(int State,int Brightnes, int Frequency){
  state = State;
  brightnes = Brightnes;
  frequency = Frequency;
}
