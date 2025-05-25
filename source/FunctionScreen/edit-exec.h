#ifndef _EDIT_EXECUTE_H_
#define _EDIT_EXECUTE_H_

#include "../Screen/BaseScreen.h"
#include "InputField.h"


class EditExecute : public BaseScreen
{
private:
    Phone editingPhone;
    std::vector<InputField> fields;
    Button saveButton;
    Popup popup;

    sf::Vector2f mousePos;

    sf::Clock inputClock;

public:
    EditExecute(sf::Font& font, UITheme theme);

    void setPhoneToEdit(const Phone& phone);
    void draw(sf::RenderWindow& window, sf::Font& font, AppScreen& screen) override;
    void pollEvent(sf::RenderWindow& window, sf::Event& event, AppScreen& screen) override;

    void update(sf::Vector2f mousePos) override
    {        
        for (auto& btn : buttons)
            btn.update(mousePos);
        popup.update();
        backButton.update(mousePos);
        saveButton.update(mousePos);
    }

    void resetAllFields() {
        for (auto& field : fields) {
            field.setText("");
            field.setContent("");
            field.setSelected(false);
        }
    }

    void updatePhoneInDatabase(SQLHDBC db, AppScreen& screen);
};

#endif