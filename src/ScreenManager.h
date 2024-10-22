#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include "Screen.cpp"
#include "StaticScreen.cpp"
#include "MenuScreen.cpp" // Include other screens you create
#include <vector>

class ScreenManager
{
private:
    Screen *currentScreen = nullptr;
    std::vector<Screen *> screens; // Store screens to manage them

public:
    void initialize(); // Setup all screens
    void switchToScreen(Screen *newScreen);
    void handleInput();
    void displayCurrentScreen(U8G2 &u8g2);
    
    ~ScreenManager(); // Destructor to clean up memory
};

#endif // SCREENMANAGER_H
