#ifndef _EDIT_LIST_SCREEN_H_
#define _EDIT_LIST_SCREEN_H_

#include "../Screen/BaseScreen.h"

class EditListScreen : public BaseScreen
{
private:
    std::vector<Phone> phones;
    std::vector<Button> editButtons;

    float scrollOffsetY = 0;
    int currentPage = 0;
    int rowsPerPage = 11;

    sf::Vector2f mousePos;
public:
    EditListScreen(sf::Font& font, UITheme theme);

    void draw(sf::RenderWindow& window, sf::Font& font) override;
    void pollEvent(sf::RenderWindow& window, sf::Event& event) override;

    void update(sf::Vector2f mousePos);

    void setPhones(const std::vector<Phone>& list);
};

#endif