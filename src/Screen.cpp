#ifndef SCREEN_H
#define SCREEN_H

#include <U8g2lib.h>

enum ScreenType
{
    STATIC_SCREEN,
    MENU_SCREEN
};

class Screen
{
protected:
    Screen *nextScreen = nullptr;
    Screen *previousScreen = nullptr;

public:
    Screen(Screen *previousScreen, Screen *nextScreen) : previousScreen(previousScreen), nextScreen(nextScreen) {}
    virtual ScreenType getType() const = 0;
    virtual void displayContent(U8G2 &u8g2) const = 0;
    Screen *getNextScreen() { return nextScreen; };
    Screen *getPreviousScreen() { return previousScreen; };

    void setPreviousScreen(Screen *previousScreen) { this->previousScreen = previousScreen; };
    void setNextScreen(Screen *nextScreen) { this->nextScreen = nextScreen; };
};

#endif // SCREEN_H