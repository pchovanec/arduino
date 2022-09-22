#include "flappyBird.h"

void flappyBird::render(void){
  if(!gameOver){
    this->physics();
  }
   OLED.firstPage();
    do {
        (this->*SCENE)();
    } while ( OLED.nextPage() );
    if(!gameOver){
    for (int i = 0; i < 7; i++) {
      box[0][i] -= mapSpeed;
      if (box[0][i] > 0 &&  box[0][i] < 15) {
        minHeight = box[1][i] + 70;
        maxHeight = box[1][i] + 45;
        if (birdY > minHeight || birdY < maxHeight) {
          gameOver = true;
          enableInput = false;
          this->SCENE = &gameOverAnime;        
        }
      }
      else {
        minHeight = 64;
        maxHeight = 0;
      }
      if (box[0][i] < -10) {
        box[0][i] = 120;
        if (box[0][i] > 50)box[0][i] += 2;
        else box[0][i] += 1;
        score++;
      }
    }
    if (birdY < 4 || birdY > 59) {
      gameOver = true;
      enableInput = false;
      this->SCENE = &gameOverAnime;
      birdY = 20;
    }
    }
}


void flappyBird::inputApp(void){
    if (input[UP]) {
      if (startFlappyBird) {
        startFlappyBird = false;
        gameOver = false;
        for (int i = 0; i < 7; i++) {
          box[0][i] =  boxSetup[i];
        }
        mapSpeed = 3;
        birdY = 30;
        gameOver = false;
        score = 0;
        this->SCENE = &gamePlay;
      }
      else if (gameOver) {
        for (int i = 0; i < 7; i++) {
          box[0][i] =  boxSetup[i];
        }
      this->SCENE = &gamePlay;
        birdY = 30;
        gameOver = false;
        score = 0;
      }
       upVector += flapPower;
    }
    else if (input[DOWN]) {
      if (gameOver || startFlappyBird) {
        exitApp = true;
      }
    }
}


void flappyBird::physics(void){
  if (upVector > 0) {
    birdY -= upVector;
    upVector -= 1;
  }
  else {
    birdY += gravity;
  }
}

void flappyBird::gamePlay(void){
    OLED.setFont(u8g_font_unifont);
    OLED.setColorIndex(1);

    for (int i = 0; i < 7; i++) {
      OLED.drawBox(box[0][i], box[1][i], 10, 40);
      OLED.drawBox(box[0][i], box[1][i] + 75, 10, 40);
    }
    OLED.setColorIndex(1);
    OLED.drawCircle(15, birdY, 4);
    OLED.drawCircle(17, birdY, 1);
    OLED.drawLine(14, birdY, 10, birdY + 2);
    OLED.drawBox(100, 0, 30, 15);

    OLED.setColorIndex(0);
    OLED.setPrintPos(105, 12);
    OLED.print(score);
}

void flappyBird::gameOverAnime(void){
  enableInput = false;
    OLED.setColorIndex(1);
    OLED.setPrintPos(22, 38);
    OLED.print("GAME OVER");
    animeIndex+=1;
    OLED.drawBox(0, 0, animeIndex, 15);
    if(animeIndex==124){
      animeIndex=0;
      enableInput = true;
      this->SCENE = &gameOverScreen;
    }
}

void flappyBird::gameOverScreen(void){
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

void flappyBird::startGameScreen(void){
    OLED.setFont(u8g_font_unifont);
    OLED.setColorIndex(1);
    OLED.drawBox(0, 0, 128, 14);
    OLED.setColorIndex(0);
    OLED.setPrintPos(13, 12);
    OLED.print("Flappy Bird");
    OLED.setColorIndex(1);
    OLED.setPrintPos(90, 52);
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
