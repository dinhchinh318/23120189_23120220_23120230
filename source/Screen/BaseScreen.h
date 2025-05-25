#ifndef _BASE_SCREEN_H_
#define _BASE_SCREEN_H_

#include "../App/Button.h"
#include "AppScreen.h"

class BaseScreen 
{
protected:
    SQLHENV hEnv;
    SQLHDBC hDbc;

    std::vector<Button> buttons;

    Button backButton;
    UITheme theme;
    sf::Text title;

public:
    BaseScreen(sf::Font& font, UITheme theme);

    virtual ~BaseScreen() = default;

    virtual void draw(sf::RenderWindow& window, sf::Font& font, AppScreen& screen) = 0;
    virtual void pollEvent(sf::RenderWindow& window, sf::Event& event, AppScreen& screen) = 0;

    virtual bool handleClicked(sf::Vector2f mousePos, AppScreen& screen, sf::RenderWindow& window) 
    {
        for (auto& btn : buttons) {
            if (btn.isClicked(mousePos)) {
                std::string label = btn.getLabel();
                std::cout << "Clicked: " << label << std::endl;

                if (label == "ADD")
                {
                    screen = AppScreen::ADD_PHONE;
                    return true;
                }
                else if (label == "DISPLAY")
                {
                    screen = AppScreen::DISPLAY_LIST;
                    return true;
                }
                else if (label == "SEARCH")
                {
                    screen = AppScreen::SEARCH_PHONE;
                    return true;
                }
                else if (label == "DELETE")
                {
                    screen = AppScreen::DELETE_PHONE;
                    return true;
                }
                else if (label == "EDIT")
                {
                    screen = AppScreen::EDIT_PHONE;
                    return true;
                }
                else if (label == "EXIT")
                {
                    window.close();
                    return true;
                }
            }
        }
        return false;
    }

    virtual void update(sf::Vector2f mousePos) = 0;

    void drawBack(sf::RenderWindow& window);

    void drawDefaultScreen(sf::RenderWindow& window, AppScreen& screen, sf::Font& font);

    void drawBoxWithText(sf::RenderWindow& window, sf::Font& font, 
                     const std::string& textStr,
                     sf::Vector2f position, sf::Vector2f size,
                     unsigned int fontSize = 20,
                     sf::Color boxColor = sf::Color(255, 255, 255, 180),
                     sf::Color outlineColor = sf::Color::Black,
                     sf::Color textColor = sf::Color::Black);

};

#endif