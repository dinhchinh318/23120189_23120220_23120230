#ifndef _MENU_SCREEN_H_
#define _MENU_SCREEN_H_

#include "../Screen/BaseScreen.h"

class InitScreen : public BaseScreen 
{
private:

public:
    InitScreen(sf::Font& font, UITheme theme);

    void draw(sf::RenderWindow& window, sf::Font& font, AppScreen& screen) override;
    
    void pollEvent(sf::RenderWindow& window, sf::Event& event, AppScreen& screen) override;

    void update(sf::Vector2f mousePos) override
    {
        for (auto& btn : buttons)
            btn.update(mousePos);
    }
};

#endif