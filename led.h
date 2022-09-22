#ifndef _led_h
#define _led_h

#include <arduino.h>

class led{
  private:
    bool light;
    int pin;
  public:
    long int timer;
    long int fadeInOut;
    led(int Pin);
    void config(int State,int Brightnes, int Frequency);
    void doLed(void);
    int state;
    int brightnes;
    int frequency;
    int minimal;
};

#endif
