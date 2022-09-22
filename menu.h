#ifndef _menu_h
#define _menu_h

#define USING_PROGMEM
#include <avr/pgmspace.h>
#include "app.h"
#include "led.h"
#include "U8glib.h"
#include "inputs.h"
#include "constants.h"


typedef void (*itemFunction)();

typedef struct values {
  int* variable;
  int increment;
  int minimum;
  int maximum;
};

typedef struct Mswitch {
  int* variable;
  char text[5][4];
  int sizeS;
};

typedef struct menuItem {
  char text[14];
  int type;
  void *target;
  itemFunction function;
};

typedef struct menuList{
  menuItem item[8];
  int size;
};

class Menu: public app {
  private:
    bool cursorVisible=true;
    long int cursorTimer;
    int increment;
    int minimum;
    int maximum;
    int* activeValue;
    bool active;
    int currentList;
    int selected;
    int cursorPos;
    int listSize;
    int index;
    values *VALUEPOINER;
    Mswitch *SWITCHPOINTER;
    int getValue(int id);
    void getSelection(char **text, int id);
  public:
    Menu(int List);
    itemFunction theFunc;
    void nextItem(bool increment);
    void returnFun(void);
    void setList(int listId);
    void inputApp(void);
    void render(void);
    void getItemText(char **text, int id);
    int getIndex(void);
    void* getLink(void);
    int getItemSetting(void);
    int getSetting(int i);
    int getCursorPosition();
    void showCursor(void);

    protected:
    int renderTime=120; 
};

#endif
