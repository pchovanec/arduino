#ifndef _flappyBird_h
#define _flappyBird_h

#include "app.h"
#include "menu.h"
#include "U8glib.h"
#include "inputs.h"
#include "constants.h"

extern U8GLIB_SSD1306_128X64 OLED;

class flappyBird:public app{
  private:
     bool startFlappyBird = true;
     signed long int box[2][7] = {{100, 130, 150, 180, 200, 230, 250}, {-30, -25, -20, -15, -30, -15, -15}};
     int boxSetup[7] = {100, 130, 150, 180, 200, 230, 250};
     bool gameOver = true;
     int birdY = 20;
     int upVector = 0;
     int score = 80;
     int minHeight = 64;
     int maxHeight = 0;
     bool startGame;
     void gamePlay();
     void gameOverScreen();
     void startGameScreen();
     void gameOverAnime();
     void gameLoop(void);
     void physics(void);
  
  public:
     void render();
     int mapSpeed = 3;
     int flapPower = 4;
     int gravity = 2;
     void inputApp();
     void (flappyBird::*SCENE)(void) = &startGameScreen;

  protected:
     int renderTime=30; 
};

#endif
