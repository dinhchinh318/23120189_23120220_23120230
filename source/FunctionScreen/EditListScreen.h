#ifndef _EDIT_LIST_SCREEN_H_
#define _EDIT_LIST_SCREEN_H_

#include "../Screen/BaseScreen.h"

// class chooseButton 
// {
// private:
//     sf::RectangleShape shape;
//     UITheme theme;
//     sf::Color currentColor;
// public:
//     chooseButton();
//     chooseButton(sf::Vector2f pos, sf::Vector2f size, UITheme theme);
//     void draw(sf::RenderWindow& window);
//     void update(sf::Vector2f mousePos);
//     bool isClicked(sf::Vector2f mousePos);
//     void setPosition(float x, float y);
//     void setSize(float width, float height);
//     void setScale(float w, float h);
//     void setOriginToCenter() {
//         this->shape.setOrigin(this->shape.getLocalBounds().width/2, this->shape.getLocalBounds().height/2);
//     }
// };

class EditListScreen : public BaseScreen
{
private:
    std::vector<Phone> phones;
    // chooseButton eBtns[12];

    float scrollOffsetY = 0;
    int currentPage = 0;
    int rowsPerPage = 11;

    sf::Vector2f mousePos;
public:
    EditListScreen(sf::Font& font, UITheme theme);

    void draw(sf::RenderWindow& window, sf::Font& font, AppScreen& screen) override;
    void pollEvent(sf::RenderWindow& window, sf::Event& event) override;

    void update(sf::Vector2f mousePos) override
    {        
        for (auto& btn : buttons)
            btn.update(mousePos);
    }

    void setPhones(const std::vector<Phone>& list);
};

#endif