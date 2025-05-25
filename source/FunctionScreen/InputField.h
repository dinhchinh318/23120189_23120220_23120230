#ifndef _INPUT_FIELD_H_
#define _INPUT_FIELD_H_

#include "Popup.h"

class InputField {
private:
    sf::RectangleShape box;
    sf::Text text;
    sf::String content;
    sf::Text label;
    sf::RectangleShape cursor;
    sf::Clock cursorTimer;
    bool cursorVisible = true;

    bool checkLength = false;
    bool isSelected = false;

public:
    InputField(sf::Font& font, sf::Vector2f pos, sf::Vector2f size);
    InputField(sf::Font& font, sf::Vector2f pos, sf::Vector2f size, string l);

    void handleEvent(sf::Event event);

    bool getSelected();

    void setSelected(bool selected);

    bool contains(sf::Vector2f point) const;

    std::string getText() const;

    void draw(sf::RenderWindow& window);

    void setlabel(std::string l);

    void setText(std::string t);

    void setContent(std::string t);

    void setOutlineBox(sf::Color& color);

    bool getLength() {
        return checkLength;
    }

    void typedOn(sf::Event input);

    void updateCursorBlink();
};

#endif
