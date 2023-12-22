#ifndef SCROLL_ELEMENT_H
#define SCROLL_ELEMENT_H

#include <TFT_eSPI.h>

class ScrollElement
{
public:
    ScrollElement(int x, int y, int width, int height, TFT_eSprite *sprite, bool isText = false);

    // Setter 메서드들

    void setY(int newY);
    void setX(int newX);

    // Getter 메서드들
    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;
    bool isText() const;
    TFT_eSprite *getSprite() const;

private:
    int x, y, width, height;
    TFT_eSprite *sprite;
    bool _isText;        
};

#endif // SCROLL_ELEMENT_H
