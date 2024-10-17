#include "Bitmaps.h"

#include "Screen.cpp"

#include <U8g2lib.h>

class StaticScreen : public Screen
{
private:
    const unsigned char *bitmap;

    static const uint8_t WIDTH = 128;
    static const uint8_t HEIGHT = 64;

public:
    // Constructor that takes only the bitmap data
    StaticScreen(Screen *previousScreen, Screen *nextScreen, const unsigned char *bitmap)
        : Screen(previousScreen, nextScreen), bitmap(bitmap) {}

    // Override getType to return STATIC_SCREEN for StaticScreen
    ScreenType getType() const override
    {
        return STATIC_SCREEN;
    }

    // Display the bitmap using U8G2 library
    void displayContent(U8G2 &u8g2) const override
    {
        u8g2.clearBuffer();

        u8g2.drawXBMP(0, 0, WIDTH, HEIGHT, bitmap);

        u8g2.sendBuffer();
    }

    void displayLogo(U8G2 &u8g2) const
    {
        u8g2.clearBuffer();

        u8g2.drawXBMP(56, 24, 16, 16, itc_logo);

        u8g2.setFont(u8g2_font_4x6_tr);

        const char *text = "sharing is caring.";
        uint8_t textWidth = u8g2.getStrWidth(text);
        uint8_t textX = (128 - textWidth) / 2;

        u8g2.drawStr(textX, 55, text);

        u8g2.sendBuffer();
    }

    // Destructor
    virtual ~StaticScreen() {}
};
