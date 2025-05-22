#ifndef _DELETE_SCREEN_H_
#define _DELETE_SCREEN_H_

#include "../Screen/BaseScreen.h"
#include "InputField.h"
#include "Popup.h"

class DeleteScreen : public BaseScreen 
{
private:
    vector<Phone> pList;

    Button deleteButton;
    Button findButton;

    std::vector<InputField> fields;

    sf::Vector2f mousePos;

    Popup popup;

    sf::Clock inputClock;

    SQLHENV hEnv;
    SQLHDBC hDbc;
public:
    DeleteScreen(sf::Font& font, UITheme theme);
    
    void draw(sf::RenderWindow& window, sf::Font& font, AppScreen& screen) override;
    void pollEvent(sf::RenderWindow& window, sf::Event& event) override;

    bool validateFields();
    void handleFindButton(SQLHDBC db);

    void update(sf::Vector2f mousePos) override
    {
        for (auto& btn : buttons)
            btn.update(mousePos);
        deleteButton.update(mousePos);
        findButton.update(mousePos);
        popup.update();
    }
    
    void deletePhone(SQLHDBC db, const int& id); 
};



#endif