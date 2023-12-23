#include <TextToSprite.h>

TFT_eSPI tft = TFT_eSPI();

// TextToSprite(TFT_eSPI *tftDisplay, const String &inputString, int maxWidth, int delayTime = 0);
// getNextSprite는 스프라이트 반환을 한다. 
// 스프라이트의 inputStringinputString 한글자당 16x16픽셀이며, maxWidth 전까지 sprite에 작성된다.
// int delayTime  타이핑 효과시 한글자 지연시간(ms 딜레이사용으로 주의), 0일시 타자 효과없음
void setup(void)
{
  Serial.begin(115200);
  for(int i = 0;; i++){
    TextToSprite *ttsprites = new TextToSprite(&tft, "test입니다. 17글자 초과시 다음 스프라이트로 작성됩니다.", 16 * 17, 0);
    ttsprites->setBackgroundColor(BG_COLOR);
    TFT_eSprite *sprite = ttsprites->getNextSprite(82, START_Y);
    if (sprite != nullptr)
    {
        sprite->pushSprite(0,16*i);
        delete sprite;
    }
    else
    {
        delete ttsprites; // TextToSprite 객체 메모리 해제
        break;
    }
  }
}
void loop()
{
}
