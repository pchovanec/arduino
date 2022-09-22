#ifndef _itemList_h
#define _itemList_h

#define LINK 1
#define VALUE 2
#define SWITCH 3
#define FUNCTION 4

#include <avr/pgmspace.h>
#include "menu.h"
#include "led.h"
#include "flappyBird.h"

extern void initFlappy(void);
extern void initStarBreaker(void);
extern void initStarWars(void);
extern void initExternInputs(void);
extern void initExternOutputs(void);
extern void ioBoardInit(void);
extern void nextPosition(void);
extern void balancerInit(void);

extern void initBrightness(void);
extern int lastList;
extern flappyBird flappy;
extern led redLed;
extern led greenLed;
extern led blueLed;
extern int externIO_ID;

const PROGMEM values redBrightnes{&redLed.brightnes, 5, 0, 250};
const PROGMEM values greenBrightnes{&greenLed.brightnes, 5, 0, 250};
const PROGMEM values blueBrightnes{&blueLed.brightnes, 5, 0, 250};
const PROGMEM values redFreq{&redLed.frequency, 10, 20, 5000};
const PROGMEM values redMinimum{&redLed.minimal, 10, 20, 5000};
const PROGMEM values greenFreq{&greenLed.frequency, 10, 20, 5000};
const PROGMEM values greenMinimum{&greenLed.minimal, 10, 20, 5000};
const PROGMEM values blueFreq{&blueLed.frequency, 10, 20, 5000};
const PROGMEM values blueMinimum{&blueLed.minimal, 10, 20, 5000};
const PROGMEM values mapSpeedFlappy{&flappy.mapSpeed, 1, 0, 20};
const PROGMEM values gravityFlappy{&flappy.gravity, 1, 0, 20};
const PROGMEM values flapPower{&flappy.flapPower, 1, 0, 20};
const PROGMEM values externIOID{&externIO_ID, 1, 0, 7};

const PROGMEM Mswitch greenState{&greenLed.state, {"Vyp", "Zap", "Bli","Ris","Fal"},4};
const PROGMEM Mswitch redState{&redLed.state, {"Vyp", "Zap", "Bli","Ris","Fal"},4};
const PROGMEM Mswitch blueState{&blueLed.state, {"Vyp", "Zap", "Bli","Ris","Fal"},4};

const PROGMEM struct menuListy {
  int listSize;
  int items[8];
} list[12] = {
  {5, {2, 33, 5, 14, 32}},
  {4, {6, 7,23, 0}},
  {4, {8, 9, 10, 0}},
  {4, {11, 12, 13, 0}},
  {5, {17, 15, 16, 14, 0}},
  {5, {17, 15, 21, 14, 0}},
  {4, {24, 25, 26, 0}},
  {4, {18, 19, 20, 0}},
  {4, {24, 25, 26, 0}},
  {4, {24, 25, 26, 0}},
  {6, {34,35,36, 37, 38, 0}},
  {4, {1, 3, 4, 0}},
};

const PROGMEM menuItem item[39] = {
  {"Zpet", LINK, 0},
  {"APP1", FUNCTION, 0, &initFlappy},
  {"LED", LINK, 1},
  {"Flappy bird", FUNCTION, 0, &initFlappy},
  {"Space breaker", FUNCTION, 0, &initStarBreaker},
  {"Settings", LINK, 5},
  {"Zelena led", LINK, 2},
  {"Cervena led", LINK, 3},
  {"Stav", SWITCH, &greenState},
  {"Jas/PWM", VALUE, &greenBrightnes},
  {"Prodleva", VALUE, &greenFreq},
  {"Stav", SWITCH, &redState},
  {"Jas/PWM", VALUE, &redBrightnes},
  {"Prodleva", VALUE, &redFreq},
  {"IOboard", LINK, 10},
  {"StarWars", LINK, 9},
  {"IOA", FUNCTION,0},
  {"Flappy bird", LINK, 7},
  {"MapSpeed", VALUE, &mapSpeedFlappy},
  {"Gravitace", VALUE, &gravityFlappy},
  {"FlapPower", VALUE, &flapPower},
  {"Space breaker", LINK, 8},
  {"Tenis", LINK, &redBrightnes},
  {"Modra led", LINK, 6},
  {"Stav", SWITCH, &blueState},
  {"Jas/PWM", VALUE, &blueBrightnes},
  {"Prodleva", VALUE, &blueFreq},
  {"IOB", FUNCTION,0},
  {"Minimum", VALUE, &greenMinimum},
  {"Minimum", VALUE, &redMinimum},
  {"Minimum", VALUE, &blueMinimum},
  {"Snake", FUNCTION, 0, &initFlappy},
  {"Osvetleni", FUNCTION, 0, &initBrightness},
  {"Hry", LINK, 11},
  {"Deska:", VALUE, &externIOID},
  {"Init", FUNCTION, 0, &ioBoardInit},
  {"I/O", FUNCTION, 0, &initExternInputs},
  {"BalancerKal", FUNCTION, 0, &balancerInit},
  {"Dalsi krok", FUNCTION, 0, &nextPosition}
};

#endif
