#include "Screen.cpp"
#include "Option.cpp"
#include <U8g2lib.h>
#include <vector>
#include <string>

class MenuScreen : public Screen
{
private:
    std::vector<Option> options; // List of menu options as Option objects
    int selectedOption = 0;      // Index of the currently selected option
    int firstVisibleOption = 0;  // Index of the first option displayed on the screen

    static const int OPTION_HEIGHT = 12;      // Height of each option in pixels
    static const int MAX_VISIBLE_OPTIONS = 5; // Maximum number of options visible at once (64 / 12)

public:
    // Constructor that takes the list of menu options
    MenuScreen(Screen *previousScreen, const std::vector<Option> &options)
        : Screen(previousScreen, nullptr), options(options) {}

    // Override getType to return MENU_SCREEN for MenuScreen
    ScreenType getType() const override
    {
        return ScreenType::MENU_SCREEN;
    }

    // Display the menu options using U8G2 library
    void displayContent(U8G2 &u8g2) const override
    {
        u8g2.clearBuffer();

        // Set font for menu text
        u8g2.setFont(u8g2_font_ncenB08_tr);

        // Display only the visible options based on firstVisibleOption
        for (int i = 0; i < MAX_VISIBLE_OPTIONS && (i + firstVisibleOption) < options.size(); i++)
        {
            int optionIndex = i + firstVisibleOption; // Index of the option to display

            // Highlight the selected option
            if (optionIndex == selectedOption)
            {
                u8g2.setDrawColor(1);                                   // Set text to inverse for highlighting
                u8g2.drawBox(0, i * OPTION_HEIGHT, 128, OPTION_HEIGHT); // Draw box to highlight selected option
                u8g2.setDrawColor(0);                                   // Set text to background color
            }
            else
            {
                u8g2.setDrawColor(1); // Regular color for unselected options
            }

            // Draw the menu option at position (0, i*12) with some padding
            u8g2.drawStr(2, (i + 1) * OPTION_HEIGHT - 2, options[optionIndex].getLabel().c_str());
        }

        u8g2.sendBuffer(); // Send the buffer to the display
    }

    // Move selection up
    void moveUp()
    {
        if (selectedOption > 0)
        {
            selectedOption--;
            // Update the visible window if needed
            if (selectedOption < firstVisibleOption)
            {
                firstVisibleOption = selectedOption;
            }
        }
    }

    // Move selection down
    void moveDown()
    {
        if (selectedOption < options.size() - 1)
        {
            selectedOption++;
            // Update the visible window if needed
            if (selectedOption >= firstVisibleOption + MAX_VISIBLE_OPTIONS)
            {
                firstVisibleOption = selectedOption - MAX_VISIBLE_OPTIONS + 1;
            }
        }
    }

    // Get the currently selected option's next screen
    Screen *getSelectedOptionNextScreen() const
    {
        return options[selectedOption].getNextScreen();
    }

    // Get the currently selected option's label
    std::string getSelectedOptionLabel() const
    {
        return options[selectedOption].getLabel();
    }

    // Destructor
    virtual ~MenuScreen() {}
};