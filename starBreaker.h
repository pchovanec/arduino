#ifndef _starBreaker_h
#define _starBreaker_h

#include <arduino.h>
#include "menu.h"
#include "app.h"
#include "starBreaker.h"
#include "constants.h"
#include "inputs.h"
#include "U8glib.h"
extern U8GLIB_SSD1306_128X64 OLED;

struct balls {
  int position_X;
  int position_Y;
  int vector_X;
  int vector_Y;
  bool active;
};

struct bricks{
  int position_X;
  int position_Y;
  bool active;
};

class starBreakerGame: public app{
  private:
    bool servising=true;
    bool runGame;
    int ballsCount=65;
    int playerX;
    bool gameOver=true;
    bool startGame=true;
    bool won;
    int score;
    bool renderGame;
    int bricksCount;
    long int keyboardTimer;
    bool renderEnable;
    int lives = 5;
    
  public:
    void gameLoop(void);
    void render();
    void inputApp();
    void nextLevel();
    void startGameScreen(void);
    void gameOverAnime(void);
    void gameOverScreen(void);
    void gamePlay(void);
    void (starBreakerGame::*pointer)(void) = &startGameScreen;
    int renderTime=25; 
};

#endif
