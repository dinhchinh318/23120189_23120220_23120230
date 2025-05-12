#ifndef _BASE_SCREEN_H_
#define _BASE_SCREEN_H_

#include "Button.h"
#include "AppScreen.h"

class BaseScreen 
{
protected:
    Button backButton;

public:
    BaseScreen(sf::Font& font, UITheme theme)
        : backButton("<< BACK", sf::Vector2f(20, 20), sf::Vector2f(120, 40), font, theme) {}

    virtual ~BaseScreen() = default;
    virtual void draw(sf::RenderWindow& window, sf::Font& font) = 0;
    virtual bool handleBack(sf::Vector2f mousePos, AppScreen& screen) 
    {
        if (backButton.isClicked(mousePos)) {
            screen = AppScreen::MENU;
            return true;
        }
        return false;
    }

    virtual void update(sf::Vector2f) {} // Optional override

    void drawBackButton(sf::RenderWindow& window);
};

#endif