#ifndef _EDIT_SCREEN_H_
#define _EDIT_SCREEN_H_

#include "../Screen/BaseScreen.h"
#include "InputField.h"
#include "Popup.h"

class EditScreen : public BaseScreen 
{
private:
    vector<Phone> pList;

    Button findButton;
    vector<Button> editButton;

    std::vector<InputField> fields;

    sf::Vector2f mousePos;

    Popup popup;

    sf::Clock inputClock;
public:
    EditScreen(sf::Font& font, UITheme theme);
    void draw(sf::RenderWindow& window, sf::Font& font, AppScreen& screen) override;
    void pollEvent(sf::RenderWindow& window, sf::Event& event) override;

    std::vector<Phone> handleFindButton(SQLHDBC db, vector<Phone>& pList);

    vector<Phone> getPhone();

    void update(sf::Vector2f mousePos) override
    {
        for (auto& btn : buttons)
            btn.update(mousePos);
        findButton.update(mousePos);
        popup.update();
    }

    void handleClick(sf::Vector2f mousePos, AppScreen& screen, sf::RenderWindow& window);
};

#endif