#include "ScreenManager.h"
#include "Bitmaps.h"

#define UP_BUTTON 32
#define BACK_BUTTON 33
#define SELECT_BUTTON 34
#define DOWN_BUTTON 35

// Example bitmaps (replace with actual bitmap data)
extern const unsigned char epd_bitmap_itc_logo[];

void ScreenManager::initialize()
{
    // Create and store screens
    StaticScreen *logoScreen = new StaticScreen(nullptr, nullptr, nullptr);

    StaticScreen *itcScreen1 = new StaticScreen(nullptr, nullptr, itc_screen_1);
    StaticScreen *itcScreen2 = new StaticScreen(nullptr, nullptr, itc_screen_2);

    StaticScreen *presidentScreen = new StaticScreen(nullptr, nullptr, president);
    StaticScreen *vicePresidentScreen = new StaticScreen(nullptr, nullptr, vice_president);
    StaticScreen *adviserScreen = new StaticScreen(nullptr, nullptr, adviser);
    StaticScreen *generalSecretaryScreen = new StaticScreen(nullptr, nullptr, general_secretary);
    StaticScreen *techLeaderScreen = new StaticScreen(nullptr, nullptr, tech_leader);
    StaticScreen *communityManagerScreen = new StaticScreen(nullptr, nullptr, community_manager);
    StaticScreen *sponsoringManagerScreen = new StaticScreen(nullptr, nullptr, sponsoring_manager);
    StaticScreen *talentManagerScreen = new StaticScreen(nullptr, nullptr, talent_manager);
    StaticScreen *eventManagerScreen = new StaticScreen(nullptr, nullptr, event_manager);
    StaticScreen *trainingManagerScreen = new StaticScreen(nullptr, nullptr, training_manager);

    StaticScreen *emergencyScreen = new StaticScreen(nullptr, nullptr, emergency);

    // Create options for ExecutiveBoardMenu
    std::vector<Option> executiveBoardMenuOptions = {
        Option("President", presidentScreen),
        Option("Vice President", vicePresidentScreen),
        Option("Adviser", adviserScreen),
        Option("General Secretary", generalSecretaryScreen),
        Option("Tech Leader", techLeaderScreen),
        Option("Community Manager", communityManagerScreen),
        Option("Sponsoring Manager", sponsoringManagerScreen),
        Option("Talent Manager", talentManagerScreen),
        Option("Event Manager", eventManagerScreen),
        Option("Training Manager", trainingManagerScreen),
    };

    // Create options for TeamsMenu
    std::vector<Option> teamsMenuOptions = {
        Option("Robotics", nullptr),
        Option("Security", nullptr),
        Option("Web Dev Frontend", nullptr),
        Option("Web Dev Backend", nullptr),
        Option("Mobile Dev", nullptr),
        Option("Design", nullptr),
        Option("Sponsoring", nullptr),
    };

    // Create options for EventsMenu
    std::vector<Option> eventsMenuOptions = {
        Option("IT Competitive Programming", nullptr),
        Option("ITC Content Creation", nullptr),
        Option("ITC Talks", nullptr),
    };

    MenuScreen *executiveBoardMenu = new MenuScreen(nullptr, executiveBoardMenuOptions);

    presidentScreen->setPreviousScreen(executiveBoardMenu);
    vicePresidentScreen->setPreviousScreen(executiveBoardMenu);
    adviserScreen->setPreviousScreen(executiveBoardMenu);
    generalSecretaryScreen->setPreviousScreen(executiveBoardMenu);
    techLeaderScreen->setPreviousScreen(executiveBoardMenu);
    communityManagerScreen->setPreviousScreen(executiveBoardMenu);
    sponsoringManagerScreen->setPreviousScreen(executiveBoardMenu);
    talentManagerScreen->setPreviousScreen(executiveBoardMenu);
    eventManagerScreen->setPreviousScreen(executiveBoardMenu);
    trainingManagerScreen->setPreviousScreen(executiveBoardMenu);

    MenuScreen *teamsMenu = new MenuScreen(nullptr, teamsMenuOptions);
    MenuScreen *eventsMenu = new MenuScreen(nullptr, eventsMenuOptions);

    // Create options for MainMenu
    std::vector<Option> mainMenuOptions = {
        Option("IT Community", itcScreen1),
        Option("Executive Board", executiveBoardMenu),
        Option("Teams", teamsMenu),
        Option("Events", eventsMenu),
        Option("Emergency", emergencyScreen),
    };

    // Create MenuScreen and set as current screen
    MenuScreen *mainMenu = new MenuScreen(nullptr, mainMenuOptions);

    executiveBoardMenu->setPreviousScreen(mainMenu);

    switchToScreen(logoScreen);

    // Store the created screens in the vector for future reference
    screens.push_back(logoScreen);
    screens.push_back(itcScreen1);
    screens.push_back(itcScreen2);
    screens.push_back(presidentScreen);
    screens.push_back(vicePresidentScreen);
    screens.push_back(adviserScreen);
    screens.push_back(generalSecretaryScreen);
    screens.push_back(techLeaderScreen);
    screens.push_back(communityManagerScreen);
    screens.push_back(sponsoringManagerScreen);
    screens.push_back(talentManagerScreen);
    screens.push_back(eventManagerScreen);
    screens.push_back(trainingManagerScreen);
    screens.push_back(emergencyScreen);
    screens.push_back(executiveBoardMenu);
    screens.push_back(teamsMenu);
    screens.push_back(eventsMenu);
    screens.push_back(mainMenu);

    switchToScreen(mainMenu);
}

void ScreenManager::switchToScreen(Screen *newScreen)
{
    if (newScreen)
    {
        if (currentScreen)
        {
            delete currentScreen; // Clean up the previous screen
        }
        currentScreen = newScreen;
    }
}

void ScreenManager::handleInput()
{
    if (digitalRead(UP_BUTTON) == HIGH)
    {
        if (currentScreen->getType() == MENU_SCREEN)
        {
            static_cast<MenuScreen *>(currentScreen)->moveUp();
        }
        delay(200); // Debounce delay
    }

    if (digitalRead(DOWN_BUTTON) == HIGH)
    {
        if (currentScreen->getType() == MENU_SCREEN)
        {
            static_cast<MenuScreen *>(currentScreen)->moveDown();
        }
        delay(200); // Debounce delay
    }

    if (digitalRead(SELECT_BUTTON) == HIGH)
    {
        if (currentScreen->getType() == MENU_SCREEN)
        {
            Screen *nextScreen = static_cast<MenuScreen *>(currentScreen)->getSelectedOptionNextScreen();
            if (nextScreen != nullptr)
            {
                switchToScreen(nextScreen);
            }
        }
        delay(200); // Debounce delay
    }

    if (digitalRead(BACK_BUTTON) == HIGH)
    {
        Screen *previousScreen = currentScreen->getPreviousScreen();
        if (previousScreen != nullptr)
        {
            switchToScreen(previousScreen);
        }
        delay(200); // Debounce delay
    }
}

void ScreenManager::displayCurrentScreen(U8G2 &u8g2)
{
    if (currentScreen)
    {
        currentScreen->displayContent(u8g2);
    }
}

// Destructor to clean up allocated screens
ScreenManager::~ScreenManager()
{
    for (Screen *screen : screens)
    {
        delete screen; // Clean up all allocated screens
    }
}