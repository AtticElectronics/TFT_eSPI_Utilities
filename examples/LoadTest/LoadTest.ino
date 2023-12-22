#include <Arduino.h>
#include <SPIFFS.h>
#include <TFT_eSPI.h>
#include "SimgSprite.h"
TFT_eSPI tft;
TFT_eSprite** sprites;
void setup() {
  Serial.begin(115200);
  tft.init();
  tft.fillScreen(TFT_BLACK);
  tft.setRotation(3);

  sprites = new TFT_eSprite*[7];
  
  SimgSprite simg(&tft);

  sprites[0] = simg.load("/1.simg");
  sprites[0]->pushSprite(0,0,simg.TRANS);
  sprites[1] = simg.load("/2.simg");
  sprites[1]->pushSprite(50,0);
  sprites[2] = simg.load("/3.simg");
  sprites[2]->pushSprite(100,0,simg.TRANS);
  sprites[3] = simg.load("/4.simg");
  sprites[3]->pushSprite(150,0,simg.TRANS);
  sprites[4] = simg.load("/5.simg");
  sprites[4]->pushSprite(200,0,simg.TRANS);
  sprites[5] = simg.load("/6.simg");
  sprites[5]->pushSprite(250,0,simg.TRANS);
  sprites[6] = simg.load("/7.simg");
  sprites[6]->pushSprite(0,100,simg.TRANS);


  sprites[0] = simg.load("/8.simg");
  sprites[0]->pushSprite(0,50,simg.TRANS);
  sprites[1] = simg.load("/9.simg");
  sprites[1]->pushSprite(50,50,simg.TRANS);
  sprites[2] = simg.load("/10.simg");
  sprites[2]->pushSprite(100,50,simg.TRANS);
  sprites[3] = simg.load("/11.simg");
  sprites[3]->pushSprite(150,50,simg.TRANS);
  sprites[4] = simg.load("/12.simg");
  sprites[4]->pushSprite(200,50,simg.TRANS);
  sprites[5] = simg.load("/13.simg");
  sprites[5]->pushSprite(250,50,simg.TRANS);
  sprites[6] = simg.load("/19.simg");
  sprites[6]->pushSprite(50,100);

}

void loop() {}
