#include "menu.h"
#include "itemList.h"

extern U8GLIB_SSD1306_128X64 OLED;
int Menu::getCursorPosition(){
  return cursorPos;
}

void Menu::getItemText(char **text, int id){
  char temp[8];
  int i;
  i = pgm_read_word(&(list[currentList].items[index+id]));
  strcpy_P(temp,(item[i].text));
  if (index+id<listSize)
   *text = temp;
   else
   *text = 0;
}

void Menu::setList(int listId){
  currentList = listId;
  selected = 1;
  index = 0;
  cursorPos = 1;
  listSize = pgm_read_word(&(list[currentList].listSize));
}

void Menu::returnFun(void){
  int id = pgm_read_word(&(list[currentList].items[selected-1]));
  theFunc = pgm_read_word(&(item[id].function));
  theFunc();
}

int Menu::getValue(int id){
  int i = pgm_read_word(&(list[currentList].items[index+id]));
  int type = pgm_read_word(&(item[i].type));
  values* VALUEP = pgm_read_word(&(item[i].target));
  int *valueItem = pgm_read_word(&(VALUEP->variable));
  if (type == 2)
   return *valueItem;
   else
   return -1;
}

void Menu::getSelection(char **text, int id){
  char tem[3];
  int i = pgm_read_word(&(list[currentList].items[index+id]));
  int type = pgm_read_word(&(item[i].type));
  Mswitch* POINT = pgm_read_word(&(item[i].target));
  int* sel = pgm_read_word(&(POINT->variable));
    
  strcpy_P(tem,(POINT->text[*sel]));
  if (index+id<listSize)
   *text = tem;

}

int Menu::getIndex(){
  return index;
}

void* Menu::getLink(){
  int id = pgm_read_word(&(list[currentList].items[selected-1]));
  return pgm_read_word(&(item[id].target));
}

int Menu::getItemSetting(){
  int i = pgm_read_word(&(list[currentList].items[selected-1]));
  return pgm_read_word(&(item[i].type));
}

int Menu::getSetting(int id){
  int i = pgm_read_word(&(list[currentList].items[index+id]));
  return pgm_read_word(&(item[i].type));
}

void Menu::inputApp(){

  int set = this->getItemSetting(); 
  if(input[ENTER]){
    if(set == 4){
      this->returnFun();
    }
    else if(set == 1){
      int link = (int)this->getLink();
      this->setList(link);
    }
    else if(set == 2){
      if(active){
      active = false;
       cursorVisible = true;
      }
      else if(!active){
        active = true;
        int id = pgm_read_word(&(list[currentList].items[selected-1]));
        VALUEPOINER = pgm_read_word(&(item[id].target));
        activeValue = pgm_read_word(&(VALUEPOINER->variable));
        increment = pgm_read_word(&(VALUEPOINER->increment));
        minimum = pgm_read_word(&(VALUEPOINER->minimum));
        maximum = pgm_read_word(&(VALUEPOINER->maximum));
      }
    }
    else if(set == 3){
      if(active){
       active = false;
       cursorVisible = true;
      }
      else if(!active){
        active = true;  
        int id = pgm_read_word(&(list[currentList].items[selected-1]));
        SWITCHPOINTER = pgm_read_word(&(item[id].target));
        activeValue = pgm_read_word(&(SWITCHPOINTER->variable));
        maximum = pgm_read_word(&(SWITCHPOINTER->sizeS));
      }
    }
  }  
  else if(input[UP]){
   if(!active){
   if(cursorPos > 1){
    selected--;
    cursorPos--;
   }
   else if(cursorPos == 1 && selected > 1){
    index-=3;
    cursorPos = 3;
    selected--;
   }
  }
  else if(set == 2){
    int var = *activeValue;
    if(var<maximum)var+=increment;
    *activeValue = var;
  }
  else if(set == 3){
    int var = *activeValue;
    if(var<maximum)var++;
    *activeValue = var;
  }
  }
  else if(input[DOWN]){
  if(!active){
   if(cursorPos < 3 && selected < listSize){
    selected++;
    cursorPos++;
   }else if(cursorPos==3 && selected < listSize){
   index+=3;
    cursorPos = 1;
    selected++;
   }   
  }
  else if(set == 2){
    int var = *activeValue;
    if(var>minimum)var-=increment;
    *activeValue = var;
  }
    else if(set == 3){
    int var = *activeValue;
    if(var>0)var--;
    *activeValue = var;
  }
  }
}

Menu::Menu(int List){
  currentList = List;
  selected = 1;
  cursorPos = 1;
}

void Menu::render(void){
  OLED.firstPage();
    do {
  int positionY = 30;
  
  OLED.setColorIndex(1);
  OLED.drawBox(0, 0, 128, 14);
  OLED.setFont(u8g_font_unifont);
  OLED.setPrintPos(12, positionY);

  for(int i= 0;i<3;i++){
   char *itemText;
   char *itemSelection;
    this->getItemText(&itemText,i);
    int type = this->getSetting(i);
    OLED.setPrintPos(12, positionY);
    OLED.print(itemText);
    OLED.setPrintPos(94, positionY);
    if(type == 2){
      int itemValue = this->getValue(i);
      OLED.print(itemValue);
    }
    
    if(type == 3){
      this->getSelection(&itemSelection,i);
     OLED.print(itemSelection);
    }
    OLED.setPrintPos(50, 12);
    positionY += 15;
  }
  OLED.setColorIndex(0);
  OLED.setPrintPos(50, 12);
  OLED.print("Menu");
  
  if(this->cursorVisible){
    OLED.setColorIndex(1);
    this->showCursor();
  }
  if(active)if(millis() - cursorTimer > 380){
    cursorVisible = !cursorVisible;
    cursorTimer = millis();
  }
    } while ( OLED.nextPage() ); 
}

void Menu::showCursor(void){
 cursorPos = getCursorPosition();
 switch (cursorPos) {
    case 1:
      OLED.drawLine(8, 25, 4, 30);
      OLED.drawLine(4, 20, 8, 25);
      break;
    case 2:
      OLED.drawLine(8, 40, 4, 45);
      OLED.drawLine(4, 35, 8, 40);
      break;
    case 3:
      OLED.drawLine(8, 55, 4, 60);
      OLED.drawLine(4, 50, 8, 55);
      break;
    case 4:
      break;
    }

}
