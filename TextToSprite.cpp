#include "TextToSprite.h"

TextToSprite::TextToSprite(TFT_eSPI *tftDisplay, const String &inputString, int maxWidth, int delayTime)
    : tft(tftDisplay), currentLineIndex(0), maxWidth(maxWidth), delayTime(delayTime)
{
    _x = 0;
    _y = 0;
    paramChar = new char[inputString.length() + 1];
    tempChar = paramChar;
    inputString.toCharArray(paramChar, inputString.length() + 1);
}

TextToSprite::~TextToSprite()
{
    delete[] paramChar; // 할당된 메모리 해제
}

void TextToSprite::setBackgroundColor(uint16_t color)
{
    BG_COLOR = color;
}
void TextToSprite::setTextColor(uint16_t color)
{
    TXT_COLOR = color;
}
TFT_eSprite *TextToSprite::getNextSprite(int x, int y)
{
    TFT_eSprite *sprite = new TFT_eSprite(tft);
    int spirte_width = 0;
    int sprite_height = 16;
    sprite->createSprite(maxWidth + 16, 16); // 라인 높이 16
    sprite->fillSprite(BG_COLOR);
    sprite->loadFont(NotoSansBold15);
    sprite->setTextColor(TXT_COLOR, BG_COLOR, 1);

    // 처음부터가아닌 currentLineIndex 부터 순회.

    while (*tempChar != '\0')
    {
        byte c = *(byte *)tempChar++;

        if (c == 0x0A)
        {
            tempChar++;
            _x = 0;
            return sprite;
        }
        else if (c >= 0x80)
        {
            byte c2 = *(byte *)tempChar++;
            byte c3 = *(byte *)tempChar++;
            byte *pFs = getHAN_font(c, c2, c3);
            sprite->drawBitmap(_x, _y, pFs, 16, 16, TXT_COLOR, BG_COLOR);
            _x += 16;
            if (delayTime > 0)
            {
                sprite->fillRect(_x + 3, 0, 8, 16, TXT_COLOR);
                sprite->pushSprite(x, y);
                sprite->fillRect(_x + 3, 0, 8, 16, BG_COLOR);
                delay(delayTime);
            }
            if (*tempChar == '\0')
            {
                return sprite;
            }
        }
        else
        {
            sprite->setCursor(_x, _y);
            sprite->println(c, 0);
            _x += 8;
            if (delayTime > 0)
            {
                sprite->fillRect(_x + 3, 0, 8, 16, TXT_COLOR);
                sprite->pushSprite(x, y);
                sprite->fillRect(_x + 3, 0, 8, 16, BG_COLOR);
                delay(delayTime);
            }

            if (*tempChar == '\0')
            {
                return sprite;
            }
        }
        // 필요한 경우 줄바꿈
        if (_x > maxWidth)
        {
            _x = 0;
            return sprite;
        }
    }
    if (*tempChar == '\0')
    {
        return nullptr;
    }
}
byte *TextToSprite::getHAN_font(byte HAN1, byte HAN2, byte HAN3)
{
    const byte cho[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 3, 1, 2, 4, 4, 4, 2, 1, 3, 0};
    const byte cho2[] = {0, 5, 5, 5, 5, 5, 5, 5, 5, 6, 7, 7, 7, 6, 6, 7, 7, 7, 6, 6, 7, 5};
    const byte jong[] = {0, 0, 2, 0, 2, 1, 2, 1, 2, 3, 0, 2, 1, 3, 3, 1, 2, 1, 3, 3, 1, 1};

    uint16_t utf16;
    byte first, mid, last;
    byte firstType, midType, lastType;
    byte i;
    byte *pB, *pF;

    utf16 = (HAN1 & 0x0f) << 12 | (HAN2 & 0x3f) << 6 | HAN3 & 0x3f;
    utf16 -= 0xac00;
    last = utf16 % 28;
    utf16 /= 28;
    mid = utf16 % 21;
    first = utf16 / 21;

    first++;
    mid++;

    if (!last)
    { // 받침 없는 경우
        firstType = cho[mid];
        midType = (first == 1 || first == 24) ? 0 : 1;
    }
    else
    { // 받침 있는 경우
        firstType = cho2[mid];
        midType = (first == 1 || first == 24) ? 2 : 3;
        lastType = jong[mid];
    }

    memset(HANFontImage, 0, 32);
    pB = HANFontImage;
    pF = (byte *)KSFont + (firstType * 20 + first) * 32;

    for (i = 32; i > 0; i--)
    {
        *pB++ = pgm_read_byte(pF++);
    }

    pB = HANFontImage;
    pF = (byte *)KSFont + (8 * 20 + midType * 22 + mid) * 32;

    for (i = 32; i > 0; i--)
    {
        *pB++ |= pgm_read_byte(pF++);
    }

    if (last)
    {
        pB = HANFontImage;
        pF = (byte *)KSFont + (8 * 20 + 4 * 22 + lastType * 28 + last) * 32;

        for (i = 32; i > 0; i--)
        {
            *pB++ |= pgm_read_byte(pF++);
        }
    }

    return HANFontImage;
}
