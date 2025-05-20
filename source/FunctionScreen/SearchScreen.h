#ifndef _SEARCH_SCREEN_H_
#define _SEARCH_SCREEN_H_

#include "../Screen/BaseScreen.h"
#include "InputField.h"
#include "Popup.h"

class SearchScreen : public BaseScreen 
{
private:
    vector<Phone> pList;

    Button findButton;

    std::vector<InputField> fields;

    sf::Vector2f mousePos;

    Popup popup;

    sf::Clock inputClock;
public:
    SearchScreen(sf::Font& font, UITheme theme);
    void draw(sf::RenderWindow& window, sf::Font& font) override;
    void pollEvent(sf::RenderWindow& window, sf::Event& event) override;

    std::vector<Phone> handleFindButton(SQLHDBC db, vector<Phone>& pList);

    vector<Phone> getPhone();

    void update(sf::Vector2f mousePos);
    void handleClick(sf::Vector2f mousePos, AppScreen& screen, sf::RenderWindow& window);
};

#endif