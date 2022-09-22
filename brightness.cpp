#include "brightness.h"
#include <BH1750.h>

extern U8GLIB_SSD1306_128X64 OLED;
extern uint16_t lux;
extern BH1750 luxSenzor;

void brightness::render(void){
 
 OLED.firstPage();
    do {
        (this->*SCENE)();
    } while ( OLED.nextPage() );

   if((millis() - measureTimer) > 2000){
    lux = luxSenzor.readLightLevel();
    measureTimer = millis();
  }
}

void brightness::inputApp(void){
   if (input[UP]) {
    exitApp = true;
   }
   else if (input[DOWN]) {
    exitApp = true;
   }
}

void brightness::mainScreen(void){
    OLED.setFont(u8g_font_unifont);
    OLED.setColorIndex(1);
    OLED.drawBox(0, 0, 128, 14);
    OLED.setColorIndex(0);
    OLED.setPrintPos(35, 12);
    OLED.print("Senzor osvetleni");
    OLED.setColorIndex(1);
    OLED.setPrintPos(10, 35);
    OLED.print("Osvetleni: ");
    OLED.setPrintPos(28, 55);
    OLED.print(lux);
    OLED.print(" Lux");
}
