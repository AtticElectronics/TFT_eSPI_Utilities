#include "ScrollElement.h"

ScrollElement::ScrollElement(int x, int y, int width, int height, TFT_eSprite *sprite, bool isText)
    : x(x), y(y), width(width), height(height), sprite(sprite), _isText(isText) {}

void ScrollElement::setY(int newY)
{
    y = newY;
}
void ScrollElement::setX(int newX)
{
    x = newX;
}
int ScrollElement::getX() const { return x; }
int ScrollElement::getY() const { return y; }
int ScrollElement::getWidth() const { return width; }
int ScrollElement::getHeight() const { return height; }
bool ScrollElement::isText() const { return _isText; }
TFT_eSprite *ScrollElement::getSprite() const { return sprite; }
