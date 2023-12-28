#ifndef TextToSprite_h
#define TextToSprite_h

#include <TFT_eSPI.h>
#include <vector>
#include <fonts/KSFont.h>
#include <fonts/NotoSans.h> 
#include <esp_log.h>

class TextToSprite
{
public:
    TextToSprite(TFT_eSPI *tftDisplay, const String &inputString, int maxWidth, int delayTime = 0);
    ~TextToSprite();
    void setBackgroundColor(uint16_t color);
    void setTextColor(uint16_t color);
    TFT_eSprite *getNextSprite(int x, int y);

private:
    TFT_eSPI *tft; // TFT_eSPI 객체 포인터

    char *paramChar; // 입력 문자열
    char *tempChar;  // 입력 문자열
    int _x, _y;      // 출력 위치
    int delayTime;   // 딜레이 시간

    size_t currentLineIndex;  // 현재 처리 중인 라인 인덱스
    int maxWidth;             // 최대 너비
    int BG_COLOR = TFT_BLACK; // 배경색
    int TXT_COLOR = TFT_WHITE; // 배경색
    byte HANFontImage[32];

    // void matrixPrint(TFT_eSPI *tft, TFT_eSprite *sprite, int tftX, int tftY, char *pChar); // matrixPrint 함수
    byte *getHAN_font(byte HAN1, byte HAN2, byte HAN3); // 한글 비트맵 생성 함수
};

#endif
