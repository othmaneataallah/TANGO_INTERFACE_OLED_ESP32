#include <string>
#include "Screen.cpp"

class Option
{
private:
    std::string label;  // Label for the option
    Screen *nextScreen; // Next screen to navigate to when this option is selected

public:
    // Constructor
    Option(const std::string &label, Screen *nextScreen)
        : label(label), nextScreen(nextScreen) {}

    // Get the label of the option
    std::string getLabel() const
    {
        return label;
    }

    // Get the next screen for the option
    Screen *getNextScreen() const
    {
        return nextScreen;
    }
};