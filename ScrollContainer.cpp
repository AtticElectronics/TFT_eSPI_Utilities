#include "ScrollContainer.h"
#include <iostream>

ScrollContainer::ScrollContainer(TFT_eSPI *tft)
    : tft(tft)
{
    if (this->tft == nullptr)
    {
        ESP_LOGE("ScrollContainer", "ScrollContainer(TFT_eSPI *tft) : tft is nullptr");
    }
}
ScrollContainer::~ScrollContainer()
{

    // 소멸자에서 남아있는 모든 요소들의 메모리 해제
    for (auto element : elements)
    {
        delete element;
    }
}

void ScrollContainer::addElement(ScrollElement *element)
{
    elements.push_back(element);
}

void ScrollContainer::popElement()
{
    if (!elements.empty())
    {
        delete elements.back(); // 마지막 요소의 메모리 해제
        elements.pop_back();
    }
}

void ScrollContainer::debugElements() const
{
    for (const ScrollElement *element : elements)
    {
        ESP_LOGD("ScrollContainer", "Element: X=%d, Y=%d, Width=%d, Height=%d",
                 element->getX(), element->getY(), element->getWidth(), element->getHeight());
    }
}

void ScrollContainer::setVerticalStep(int step)
{
    verticalStep = step;
}
void ScrollContainer::setBackgroundColor(uint16_t color)
{
    backgroundColor = color;
}

void ScrollContainer::updateAndDraw()
{
    ScrollElement *nextElement = nullptr; // 다음 요소를 추적

    for (auto it = elements.begin(); it != elements.end(); ++it)
    {
        ScrollElement *currentElement = *it;
        int x = currentElement->getX();
        int y = currentElement->getY();
        int w = currentElement->getWidth();
        int h = currentElement->getHeight();
        currentElement->setY(y - verticalStep);
        currentElement->getSprite()->pushSprite(currentElement->getX(), currentElement->getY());

        // 다음 요소를 결정합니다.
        nextElement = (std::next(it) != elements.end()) ? *std::next(it) : nullptr;

        // 현재 요소가 텍스트가 아니거나, 다음 요소가 없거나, 다음 요소의 isText() 값이 현재와 다를 경우 fillRect를 실행합니다.
        if (!currentElement->isText() || nextElement == nullptr || currentElement->isText() != nextElement->isText())
        {
            tft->fillRect(x, y + h - verticalStep, w, verticalStep, backgroundColor);
        }
    }

    clearOverflowElements();
}

void ScrollContainer::updateAndDraw(int step)
{
    ScrollElement *nextElement = nullptr; // 다음 요소를 추적

    for (auto it = elements.begin(); it != elements.end(); ++it)
    {
        ScrollElement *currentElement = *it;
        int x = currentElement->getX();
        int y = currentElement->getY();
        int w = currentElement->getWidth();
        int h = currentElement->getHeight();
        currentElement->setY(y - step);
        currentElement->getSprite()->pushSprite(currentElement->getX(), currentElement->getY());

        // 다음 요소를 결정합니다.
        nextElement = (std::next(it) != elements.end()) ? *std::next(it) : nullptr;

        // 현재 요소가 텍스트가 아니거나, 다음 요소가 없거나, 다음 요소의 isText() 값이 현재와 다를 경우 fillRect를 실행합니다.
        if (!currentElement->isText() || nextElement == nullptr || currentElement->isText() != nextElement->isText())
        {
            tft->fillRect(x, y + h - step, w, step, backgroundColor);
        }
    }

    clearOverflowElements();
}

void ScrollContainer::clearOverflowElements()
{
    for (auto it = elements.begin(); it != elements.end();)
    {
        if (((*it)->getY() + (*it)->getHeight()) < 0)
        {
            delete *it; // 메모리 해제 //TODO:확인전
            it = elements.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void ScrollContainer::drawElements()
{
    for (ScrollElement *element : elements)
    {
        element->getSprite()->pushSprite(element->getX(), element->getY());
    }
}