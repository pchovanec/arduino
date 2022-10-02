#include "externIO.h"
#include "arduino.h"

byte displayCache;
extern U8GLIB_SSD1306_128X64 OLED;
extern uint8_t externIO_ID;
extern MCP onechip;
MCP IOboard(1, A1); 

exterinIO(){
  //MCP externBoard(7, A1); 
}

void externIO::render(void){
 OLED.firstPage();
    do {
        (this->*SCENE)();
    } while ( OLED.nextPage() );

   if((millis() - timer) > 1000){   
     SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
     inputCache = onechip.byteRead(GPIOB);
     onechip.byteWrite(GPIOA,outputCache);
   }
}

void externIO::inputApp(void){
   if (input[UP] && selected<7) {
    selected++;
   }
   else if (input[DOWN] && selected>=7) {
    exitApp = true;
    selected = 1;
   }
   else if (input[DOWN] && selected>0) {
    selected--;
   }
   else if (input[ENTER]){
      outputCache ^= (1 << selected);
   }
}

void externIO::mainScreen(void){
    OLED.setFont(u8g_font_unifont);
    OLED.setColorIndex(1);
    OLED.drawBox(0, 0, 128, 14);
    
    OLED.drawLine((15+(selected*12)), 46, (24+(selected*12)), 46);
    OLED.setColorIndex(0);
    OLED.setPrintPos(9, 12);
    OLED.print("Vstupy/Vystupy");
    OLED.setColorIndex(1);
    OLED.setPrintPos(2, 37);
    OLED.print("I");
    OLED.setPrintPos(2, 57);
    OLED.print("O");
    
    for(int i = 0, x = 15, y = 27;i < 8;i++, x += 12){
      if(inputCache & (1 << i)){
        OLED.drawBox(x, y, 10, 10);
      }
      else{
        OLED.drawFrame(x, y, 10, 10);
      }
    }
    
    for(int i = 0, x = 15, y = 48;i < 8;i++, x += 12){
      if(outputCache & (1 << i)){
        OLED.drawBox(x, y, 10, 10);
      }
      else{
        OLED.drawFrame(x, y, 10, 10);
      }
    }
}
