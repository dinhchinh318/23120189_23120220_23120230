#ifndef _BASE_SCREEN_H_
#define _BASE_SCREEN_H_

#include "../App/Button.h"
#include "AppScreen.h"

// ============================================================================
// BaseScreen (Abstract Class)
// ----------------------------------------------------------------------------
// This class serves as a base for all UI screens in the application. It handles:
// - SQL database connectivity
// - Common UI elements like header, back button, and top menu buttons
// - Required interfaces for drawing and polling events in derived screens
// ============================================================================
class BaseScreen 
{
protected:
    SQLHENV hEnv;                           // ODBC environment handle
    SQLHDBC hDbc;                           // ODBC database connection handle

    std::vector<Button> buttons;           // Top menu buttons (ADD, DELETE, etc.)
    Button backButton;                     // Back navigation button
    UITheme theme;                         // UI theme for styling
    sf::Text title;                        // Screen title text

public:
    // Constructor: initializes the base screen with font and theme
    BaseScreen(sf::Font& font, UITheme theme);

    // Virtual destructor
    virtual ~BaseScreen() = default;

    // ===============================
    // Abstract Methods (must override)
    // ===============================

    // Renders the screen content
    virtual void draw(sf::RenderWindow& window, sf::Font& font, AppScreen& screen) = 0;

    // Handles input events (keyboard, mouse, etc.)
    virtual void pollEvent(sf::RenderWindow& window, sf::Event& event, AppScreen& screen) = 0;

    // Updates hover or visual states based on mouse position
    virtual void update(sf::Vector2f mousePos) = 0;

    // ===============================
    // Navigation & Interaction
    // ===============================

    // Handles top menu button clicks (e.g. ADD, DISPLAY, EXIT)
    virtual bool handleClicked(sf::Vector2f mousePos, AppScreen& screen, sf::RenderWindow& window) 
    {
        for (auto& btn : buttons) {
            if (btn.isClicked(mousePos)) {
                std::string label = btn.getLabel();
                std::cout << "Clicked: " << label << std::endl;

                if (label == "ADD")        screen = AppScreen::ADD_PHONE;
                else if (label == "DISPLAY") screen = AppScreen::DISPLAY_LIST;
                else if (label == "SEARCH")  screen = AppScreen::SEARCH_PHONE;
                else if (label == "DELETE")  screen = AppScreen::DELETE_PHONE;
                else if (label == "EDIT")    screen = AppScreen::EDIT_PHONE;
                else if (label == "EXIT") {
                    window.close();
                    return true;
                } else {
                    return false;
                }

                return true;
            }
        }
        return false;
    }

    // ===============================
    // Drawing Helpers
    // ===============================

    // Draws the back button
    void drawBack(sf::RenderWindow& window);

    // Draws top bar with menu buttons and title
    void drawDefaultScreen(sf::RenderWindow& window, AppScreen& screen, sf::Font& font);

    // Utility to draw a labeled box with custom style
    void drawBoxWithText(sf::RenderWindow& window, sf::Font& font, 
                         const std::string& textStr,
                         sf::Vector2f position, sf::Vector2f size,
                         unsigned int fontSize = 20,
                         sf::Color boxColor = sf::Color(255, 255, 255, 180),
                         sf::Color outlineColor = sf::Color::Black,
                         sf::Color textColor = sf::Color::Black);
};

#endif
