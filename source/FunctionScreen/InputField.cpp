#include "InputField.h"

InputField::InputField(sf::Font& font, sf::Vector2f pos, sf::Vector2f size) {
    box.setPosition(pos);
    box.setSize(size);
    box.setFillColor(sf::Color::White);
    box.setOutlineColor(sf::Color::Black);
    box.setOutlineThickness(2);

    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);
    text.setPosition(pos.x + 5, pos.y + 5);

    label.setFont(font);
    label.setCharacterSize(20);
    label.setFillColor(sf::Color::Black);
    label.setPosition(pos.x - 180, pos.y + 5);
}

void InputField::handleEvent(sf::Event event) {
    if (!isSelected) return;

    if (event.type == sf::Event::TextEntered) 
    {
        if (event.text.unicode == '\b' && !content.isEmpty()) 
        {
            content.erase(content.getSize() - 1, 1);
            checkLength = false;
        } 
        else if (event.text.unicode >= 32 && event.text.unicode < 128) 
        {
            if (content.getSize() < 30) 
            {
                content += static_cast<char>(event.text.unicode);
                checkLength = false;
            }
            else
            {
                checkLength = true;
            }
        }
        text.setString(content);
    }
}

bool InputField::getSelected()
{
    return isSelected;
}

void InputField::setSelected(bool selected) {
    isSelected = selected;
    box.setOutlineColor(selected ? sf::Color::Blue : sf::Color::Black);
}

bool InputField::contains(sf::Vector2f point) const {
    return box.getGlobalBounds().contains(point);
}

std::string InputField::getText() const { return content; }

void InputField::draw(sf::RenderWindow& window) {
    window.draw(box);
    window.draw(text);
    window.draw(label);
}

void InputField::setlabel(string l)
{
    label.setString(l);
}

void InputField::setText(string t)
{
    text.setString(t);
}

void InputField::setContent(string t)
{
    content = "";
}

void InputField::setOutlineBox(sf::Color& color)
{
    box.setOutlineColor(color);
}

void InputField::typedOn(sf::Event input) {
    if (input.type == sf::Event::TextEntered) {      
        if (isSelected) {
            sf::String currentText = text.getString();
            if (input.text.unicode < 128 && input.text.unicode >= 32) {
                if (currentText.getSize() < 30 && content.getSize() < 30) {
                    currentText += static_cast<char>(input.text.unicode);
                    text.setString(currentText);
                    checkLength = false;
                }
                else
                {
                    checkLength = true;
                }
            }
            else if (input.text.unicode == 8) {
                if (currentText.getSize() > 0) {
                    currentText.erase(currentText.getSize() - 1, 1);
                    text.setString(currentText);
                    checkLength = false;
                }
            }
        }
    }
}
