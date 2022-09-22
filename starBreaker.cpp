#include "starBreaker.h"

bricks brick[66] = {
  {20, 12, 1},
  {28, 12, 1},
  {36, 12, 1},
  {44, 12, 1},
  {52, 12, 1},
  {56, 12, 1},
  {68, 12, 1},
  {76, 12, 1},
  {84, 12, 1},
  {92, 12, 1},
  {100, 12, 1},

  {20, 16, 1},
  {28, 16, 1},
  {52, 16, 1},
  {60, 16, 1},
  {68, 16, 1},
  {76, 16, 1},
  {100, 16, 1},

  {12, 20, 1},
  {20, 20, 1},
  {28, 20, 1},
  {36, 20, 1},
  {44, 20, 1},
  {52, 20, 1},
  {84, 20, 1},
  {92, 20, 1},
  {100, 20, 1},

  {12, 24, 1},
  {20, 24, 1},
  {28, 24, 1},
  {36, 24, 1},
  {44, 24, 1},
  {76, 24, 1},
  {84, 24, 1},
  {92, 24, 1},
  {100, 24, 1},

  {20, 28, 1},
  {36, 28, 1},
  {44, 28, 1},
  {52, 28, 1},
  {60, 28, 1},
  {68, 28, 1},
  {76, 28, 1},
  {84, 28, 1},
  {92, 28, 1},

  {20, 32, 1}, 
  {48, 32, 1},
  {52, 32, 1},
  {60, 32, 1},
  {68, 32, 1},
  {76, 32, 1},
  {92, 32, 1},

  {20, 36, 1}, 
  {28, 36, 1},
  {36, 36, 1}, 
  {84, 36, 1},
  {92, 36, 1},

  {36, 40, 1},
  {44, 40, 1},
  {52, 40, 1},
  {60, 40, 1},
  {68, 40, 1}, 
  {76, 40, 1},
  {84, 40, 1},
  {92, 40, 1}
};
balls ball[1] = {
  {0,0, 0, 0,0}
};

void starBreakerGame::render() {
     OLED.firstPage();
    do {
        (this->*pointer)();
    } while ( OLED.nextPage() );
    if(!gameOver){
       for(int i=0;i < 64; i++){
    if(brick[i].active){
      if(brick[i].position_Y + 3 >= ball[0].position_Y && brick[i].position_Y <= ball[0].position_Y)if(brick[i].position_X -2 <= ball[0].position_X && brick[i].position_X + 9 >= ball[0].position_X){
        brick[i].active = false;
        bricksCount--;
        if(ball[0].position_Y + 2 >= brick[i].position_Y || ball[0].position_Y -2 <= brick[i].position_Y + 3){
        ball[0].vector_Y *= (-1);
        }
        else{
        ball[0].vector_X *= (-1);
        }
        break;
      }
    }
   }
    if(ball[0].position_Y <= 3)ball[0].vector_Y *= (-1);
    else if(ball[0].position_X >= 125 || (ball[0].position_X <= 3))ball[0].vector_X *= (-1);
    if(ball[0].position_Y >= 59 && ball[0].position_Y <= 61){
      if(ball[0].position_X >= playerX && ball[0].position_X <= playerX + 21){
        ball[0].vector_Y *= (-1);
        }
    }
   if(ball[0].position_Y >= 63){
    ball[0].vector_X = 0;
    ball[0].vector_Y = 0;
    ballsCount--;
    lives--;
    servising = true;
   }
   if(lives == 0){
    gameOver = true;
    runGame = false;
    pointer = &gameOverAnime;
   }
   if(bricksCount == 0){
    won = true;
    runGame = false;
    //pointer = &gameOverAnime;
   }
    ball[0].position_X += ball[0].vector_X;
    ball[0].position_Y += ball[0].vector_Y;
    }
}

 void starBreakerGame::inputApp() {
    if (input[ENTER]) {
      if (servising) {
        ballsCount++;
        ball[0].vector_X = 2;
        ball[0].vector_Y = -2;
        servising = false;
      }
    }
    else if (input[DOWN]) {
      if (gameOver || pointer == &startGameScreen) {
        score = 0;
        exitApp = true;
        nextLevel();
        runGame = true;
        bricksCount = 64;
        gameOver = false;
        startGame = false;
      }
     else if (playerX > 5){
        playerX-=4;
      }
    }
    else if (input[UP]) {
      if (gameOver || pointer == &startGameScreen) {
        pointer = &gamePlay;
        gameOver = false;
        servising = true;
        lives = 3;
        for(int i=0; i < 66;i++)
        brick[i].active = true;
            ball[0].position_X = playerX + 9;
    ball[0].position_Y = 56;
      }
      else if (playerX < 105) {
        playerX+=4;
      }
    }
 }

 void starBreakerGame::gamePlay() {
  if(servising){
    ball[0].position_X = playerX + 9;
    ball[0].position_Y = 56;
  }
   for(int i=0;i < 64; i++){
      if(brick[i].active)OLED.drawBox(brick[i].position_X,brick[i].position_Y,7,3);
   }
   OLED.drawCircle(ball[0].position_X,ball[0].position_Y,2);
   OLED.setPrintPos(4, 55);
   OLED.drawFrame(1,1,126,62);
   OLED.drawLine(playerX, 60, playerX + 20, 60);
}
 
void starBreakerGame::nextLevel() {
  for( int i=0; i<64; i++)
  {
//    memcpy_P(&brick[i], &brickMem[i], sizeof(bricks));
  }
}

void starBreakerGame::gameOverAnime(void){
  enableInput = false;
    OLED.setColorIndex(1);
    OLED.setPrintPos(22, 38);
    OLED.drawBox(0, 0, animeIndex, 40);
    animeIndex+=1;
    if(animeIndex==124){
      enableInput = true;
      animeIndex=0;
      this->pointer = &gameOverScreen;
    }
}

void starBreakerGame::gameOverScreen(void){
  enableInput = true;
    OLED.setColorIndex(1);
    OLED.setPrintPos(0, 10);
    OLED.print("Score:");
    OLED.print(score);
    OLED.setPrintPos(50, 10);
    OLED.setColorIndex(1);
    OLED.drawCircle(90, 30, 8);
    OLED.drawLine(90, 25, 96, 35);
    OLED.drawLine(90, 25, 84, 35);
    OLED.drawCircle(90, 55, 8);
    OLED.drawLine(90, 60, 96, 50);
    OLED.drawLine(90, 60, 84, 50);
    
    OLED.setPrintPos(5, 35);
    OLED.print("Spustit");
    OLED.setPrintPos(5, 60);
    OLED.print("Zpet");
}

 void starBreakerGame::startGameScreen(void){
    OLED.setFont(u8g_font_unifont);
    OLED.setColorIndex(1);
    OLED.drawBox(0, 0, 128, 14);
    OLED.setColorIndex(0);
    OLED.setPrintPos(19, 12);
    OLED.print("Star breaker");
    OLED.setColorIndex(1);

    OLED.drawCircle(90, 30, 8);
    OLED.drawLine(90, 25, 96, 35);
    OLED.drawLine(90, 25, 84, 35);
    OLED.drawCircle(90, 55, 8);
    OLED.drawLine(90, 60, 96, 50);
    OLED.drawLine(90, 60, 84, 50);
    
    OLED.setPrintPos(5, 35);
    OLED.print("Spustit");
    OLED.setPrintPos(5, 60);
    OLED.print("Zpet");
}
