#ifndef _FIND_LIST_SCREEN_H_
#define _FIND_LIST_SCREEN_H_

#include "../Screen/BaseScreen.h"

class FindListScreen : public BaseScreen
{
private:
    std::vector<Phone> phones;

    float scrollOffsetY = 0;
    int currentPage = 0;
    int rowsPerPage = 11;

    sf::Vector2f mousePos;
public:
    FindListScreen(sf::Font& font, UITheme theme);

    void draw(sf::RenderWindow& window, sf::Font& font, AppScreen& screen) override;
    void pollEvent(sf::RenderWindow& window, sf::Event& event) override;
    void update(sf::Vector2f mousePos) override 
    {
        for (auto& btn : buttons)
            btn.update(mousePos);
    }

    void setPhones(const std::vector<Phone>& phones) {
        this->phones = phones;
    }
};

#endif