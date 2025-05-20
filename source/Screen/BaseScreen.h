#ifndef _BASE_SCREEN_H_
#define _BASE_SCREEN_H_

#include "../App/Button.h"
#include "AppScreen.h"

class BaseScreen 
{
protected:
    Button backButton;
    SQLHENV hEnv;
    SQLHDBC hDbc;

public:
    BaseScreen(sf::Font& font, UITheme theme);

    virtual ~BaseScreen() = default;

    virtual void draw(sf::RenderWindow& window, sf::Font& font) = 0;
    virtual void pollEvent(sf::RenderWindow& window, sf::Event& event) = 0;

    virtual bool handleBack(sf::Vector2f mousePos, AppScreen& screen) 
    {
        if (!backButton.isClicked(mousePos))
            return false;

        switch (screen) {
            case AppScreen::EDIT_LIST:
                screen = AppScreen::EDIT_PHONE;
                return true;
                break;
            case AppScreen::FIND_LIST:
                screen = AppScreen::SEARCH_PHONE;
                return true;
                break;         
            default:
                screen = AppScreen::MENU;
                return true;
        }
    }


    virtual void update(sf::Vector2f) {} // Optional override

    void drawBackButton(sf::RenderWindow& window);
};

#endif