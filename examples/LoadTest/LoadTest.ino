/*
  현재 LittleFS 만 사용한다.
*/
#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SimgSprite.h>

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
}
void loop() {}
