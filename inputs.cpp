#include "inputs.h"

void catchInputs(){
   for (int i = 0; i < 3; i++) {
      input[i] = !digitalRead(button[i]);
      if(!keyPressed){
          keyPressed = true;
          keyTimer = keyTimer + 2500;
        }
   }
}

void keypadInit(){
  for (int i = 0; i < 3; i++)pinMode(button[i], INPUT_PULLUP);
}
