#ifndef _MENU_SCREEN_H_
#define _MENU_SCREEN_H_

#include "BaseScreen.h"

class MenuScreen : public BaseScreen 
{
private:
    std::vector<Button> buttons;
    UITheme theme;
    sf::Text title;

public:
    MenuScreen(sf::Font& font, UITheme theme);

    void draw(sf::RenderWindow& window, sf::Font& font) override;
    
    void pollEvent(sf::RenderWindow& window, sf::Event& event) override;

    void update(sf::Vector2f mousePos);

    void handleClick(sf::Vector2f mousePos, AppScreen& screen, sf::RenderWindow& window);
};

#endif