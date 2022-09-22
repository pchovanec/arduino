#ifndef _inputs_h
#define _inputs_h

#include <arduino.h>

extern bool keyPressed;
extern long int keyTimer;
extern bool input[3];
extern uint8_t button[3];
void catchInputs();
void keypadInit();
extern long int displayTimer;

#endif
