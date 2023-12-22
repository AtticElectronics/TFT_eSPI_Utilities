#include "SimgSprite.h"

SimgSprite::SimgSprite(TFT_eSPI *obj)
{
    tft = obj;
    if (!FILE_SYSTEM.begin())
    {
        Serial.println("LittleFS initialisation failed!");
        while (1)
            yield();
    }
    
}

SimgSprite::~SimgSprite()
{
    // Destructor implementation
}
uint16_t SimgSprite::swap_endian(uint16_t val) {
    return (val << 8) | (val >> 8);
}


TFT_eSprite *SimgSprite::load(const char * fileName)
{
    File file = FILE_SYSTEM.open(fileName, "r");
    if (!file)
    {
        Serial.println("Failed to open file");
        return nullptr;
    }
    uint16_t mwidth = 0;
    uint16_t mheight = 0;
    uint8_t format;
    uint32_t total_len;
    uint16_t pixel;
    uint8_t count;
    uint16_t x;
    uint16_t y;
    x = 0;
    y = 0;

    file.readBytes((char *)&mwidth, sizeof(mwidth));
    file.readBytes((char *)&mheight, sizeof(mheight));
    file.readBytes((char *)&format, sizeof(format));
    total_len = static_cast<uint32_t>(mwidth) * static_cast<uint32_t>(mheight);
    
    // 엔디언 스왑
    //mwidth = swap_endian(mwidth);
    //mheight = swap_endian(mheight);
    
    Serial.printf("mwidth: %u, mheight: %u, Format: %u len: %u\n", mwidth, mheight, format, total_len);

    TFT_eSprite *sprite = new TFT_eSprite(tft);
    sprite->createSprite(mwidth, mheight);


    if (format == 1)
    {
        while (total_len > 0)
        {
            file.readBytes((char *)&pixel, sizeof(pixel));
            Serial.printf("x: %u, y: %u, color: 0x%04X\n", x, y, pixel);
            sprite->drawPixel(x, y, pixel);
            incrementCoordinates(x, y, mwidth, total_len);
        }
    }
    else
    {
        while (total_len > 0)
        {
            file.readBytes((char *)&pixel, sizeof(pixel));
            file.readBytes((char *)&count, sizeof(count));
            //pixel = swap_endian(pixel);
            //Serial.printf("x: %u, y: %u, color: 0x%04X , count: %d\n", x, y, pixel,count);
            for (uint8_t i = 0; i < count; i++) {
                sprite->drawPixel(x, y, pixel);
                incrementCoordinates(x, y, mwidth, total_len);
                if (total_len == 0) break; // Check if the end of the image is reached
            }
        }
    }
    file.close();

    return sprite;
}

void SimgSprite::incrementCoordinates(uint16_t &x, uint16_t &y, const uint16_t width, uint32_t &total_len)
{
    total_len--;
    x++;
    if (x >= width)
    {
        x = 0;
        y++;
    }
}
