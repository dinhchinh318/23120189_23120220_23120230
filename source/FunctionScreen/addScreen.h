#ifndef _ADD_SCREEN_H_
#define _ADD_SCREEN_H_

#include "../Screen/BaseScreen.h"
#include "InputField.h"
#include "Popup.h"

class AddPhoneScreen : public BaseScreen 
{
private:
    vector<Phone> pList;

    std::vector<InputField> fields;
    Button addButton;
    sf::Vector2f mousePos;

    Popup popup;

    sf::Clock inputClock;
public:
    AddPhoneScreen(sf::Font& font, UITheme theme);

    void draw(sf::RenderWindow& window, sf::Font& font, AppScreen& screen) override;
    void pollEvent(sf::RenderWindow& window, sf::Event& event, AppScreen& screen) override;
    void update(sf::Vector2f mousePos) override 
    {
        for (auto& btn : buttons)
            btn.update(mousePos);

        addButton.update(mousePos);
        popup.update();
        
        for (auto& field : fields)
            field.updateCursorBlink();
    }

    void resetAllFields();


    bool validateFields();
    bool checkFields();

    bool isPhoneIDExisted(SQLHDBC db, int id);
    void addPhone(SQLHDBC db);
};

#endif