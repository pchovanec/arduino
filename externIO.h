#ifndef _ixternIO_h
#define _ixternIO_h

#include "U8glib.h"
#include "app.h"
#include "menu.h"
#include "MCP23S17.h"

class externIO:public app{
  private:
     void mainScreen();
     long int timer;
     int selected=0;
     byte inputCache;
     byte outputCache;
  public:
     void render();
     void inputApp();
     void (externIO::*SCENE)(void) = &mainScreen;
};

#endif
