#ifndef SCROLL_CONTAINER_H
#define SCROLL_CONTAINER_H

#include "ScrollElement.h"
#include <esp_log.h>
#include <vector>

class ScrollContainer
{
public:
    ScrollContainer(TFT_eSPI *tft);
    ~ScrollContainer();

    ScrollContainer(const ScrollContainer &) = delete;
    ScrollContainer &operator=(const ScrollContainer &) = delete;

    void addElement(ScrollElement *element);
    void popElement();
    void debugElements() const;

    void setVerticalStep(int step);
    void setBackgroundColor(uint16_t color);

    void updateAndDraw();
    void updateAndDraw(int step);

    void clearOverflowElements();
    void drawElements();

private:
    TFT_eSPI *tft;
    std::vector<ScrollElement *> elements;
    int verticalStep = 16;
    uint16_t backgroundColor = 12712;
};

#endif // SCROLL_CONTAINER_H
