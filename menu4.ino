#include <avr/io.h>
#include <OneWire.h>
#include "U8glib.h"
#include "app.h"
#include "constants.h"
#include "led.h"
#include "inputs.h"
#include "menu.h"
#include "starBreaker.h"
#include "flappyBird.h"
#include "MCP23S17.h"
#include "brightness.h"
#include "externIO.h"
#include <BH1750.h>

#define rx_pin A4
#define tx_pin A5

uint8_t button[3] = {4, 2, 7};
bool input[3];
bool keyPressed=false;
long int displayTimer=0;
long int keyTimer = 0;
void (*initFunc)(void);
int externIO_ID = 7;

U8GLIB_SSD1306_128X64 OLED(D0, D1, CS, DC, RES);
app* APP;
MCP onechip(1, A1);
BH1750 luxSenzor;
Menu mainMenu(0);
led redLed(6);
led greenLed(5);
led blueLed(3);

starBreakerGame starBreaker;
flappyBird flappy;
externIO externBoard;
bool balancerPosition;

void setup() {
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(3, OUTPUT);
  Serial.begin(9600);
  luxSenzor.begin();
  ioBoardInit();
  keypadInit();
  mainMenu.setList(0);
  APP = &mainMenu;
  blueLed.config(VYP,150,100);
  redLed.config(VYP,180,100);
  greenLed.config(VYP,200,100); 
}
 
void loop() {
  if((millis() - keyTimer) > 140){
     catchInputs();
     if(APP->enableInput)APP->inputApp();
     keyTimer = millis();
  }
  
  if(((millis() - displayTimer) > APP->renderTime)){
     if(APP->exitApp){
      APP->exitApp = false;
      APP = &mainMenu;
     }
     digitalWrite(8,LOW);
     APP->render();
     digitalWrite(8,HIGH);
     displayTimer = millis();
     keyPressed = false;
  }
    
  redLed.doLed();
  greenLed.doLed();
  blueLed.doLed(); 
}

void ioBoardInit(){
  SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
  onechip.setAdress(externIO_ID);
  onechip.begin();
  onechip.pinMode(0xFF00);
}

void initFlappy(){
  APP = &flappy;
}

void initStarBreaker(){
  APP = &starBreaker;
}

void initBrightness(){
//  APP = &brightness;
}

void initExternInputs(){
  APP = &externBoard;
}

void initExternOutputs(){
  APP = &externBoard;
}

