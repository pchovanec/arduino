#ifndef _brightness_h
#define _brightness_h

#include "U8glib.h"
#include "app.h"
#include "menu.h"
#include "MHZ19.h"

class brightness:public app{
  private:
     void mainScreen();
     long int measureTimer;    
  public:
     void render();
     void inputApp();
     void (brightness::*SCENE)(void) = &mainScreen;
};

#endif
