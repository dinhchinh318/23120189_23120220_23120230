#ifndef _EDIT_LIST_SCREEN_H_
#define _EDIT_LIST_SCREEN_H_

#include "../Screen/BaseScreen.h"

class EditListScreen : public BaseScreen
{
private:
    std::vector<Phone> phones;

    float scrollOffsetY = 0;
    int currentPage = 0;
    int rowsPerPage = 11;

    sf::Vector2f mousePos;

    sf::Clock clickClock;
    sf::Vector2f lastClickPos;
    bool waitingForDoubleClick = false;

    int indexPhone = -1;
public:
    EditListScreen(sf::Font& font, UITheme theme);

    void draw(sf::RenderWindow& window, sf::Font& font, AppScreen& screen) override;
    void pollEvent(sf::RenderWindow& window, sf::Event& event, AppScreen& screen) override;

    void update(sf::Vector2f mousePos) override
    {        
        for (auto& btn : buttons)
            btn.update(mousePos);
        backButton.update(mousePos);
    }

    void setPhones(const std::vector<Phone>& list);
   
    void handleMouseClick();
    void handleScroll(float delta);
    void handleKeyboard(sf::Keyboard::Key key);
    void drawTableFrame(sf::RenderWindow& window);
    void drawTableContent(sf::RenderWindow& window, sf::Font& font);
    void drawPageIndicator(sf::RenderWindow& window, sf::Font& font);

    int getIndex() const;
};

#endif