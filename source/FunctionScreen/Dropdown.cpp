#include "Dropdown.h"

Dropdown::Dropdown(sf::Font& fontRef, const std::vector<std::string>& items, float width, float height)
    : font(fontRef), width(width), height(height)
{
    box.setSize({width, height});
    box.setFillColor(sf::Color::White);
    box.setOutlineColor(sf::Color::Black);
    box.setOutlineThickness(2);

    selectedText.setFont(font);
    selectedText.setCharacterSize(18);
    selectedText.setFillColor(sf::Color::Black);
    selectedText.setPosition(box.getPosition().x + 5.f, box.getPosition().y + 5.f);

    for (const auto& item : items)
    {
        sf::Text optionText;
        optionText.setFont(font);
        optionText.setCharacterSize(18);
        optionText.setFillColor(sf::Color::Black);
        optionText.setString(item);
        options.push_back(optionText);
    }

    if (!options.empty())
    {
        selectedText.setString(options[0].getString());
    }
}

void Dropdown::setPosition(float x, float y)
{
    box.setPosition(x, y);
    selectedText.setPosition(x + 5.f, y + 5.f);

    for (size_t i = 0; i < options.size(); ++i)
    {
        options[i].setPosition(x + 5.f, y + height * (i + 1) + 5.f);
    }
}

void Dropdown::update(const sf::Vector2f& mousePos, bool mouseClicked)
{
    if (box.getGlobalBounds().contains(mousePos) && mouseClicked)
    {
        isOpen = !isOpen;
    }
    else if (mouseClicked && isOpen)
    {
        // Kiểm tra click vào lựa chọn nào
        for (size_t i = 0; i < options.size(); ++i)
        {
            if (options[i].getGlobalBounds().contains(mousePos))
            {
                selectedIndex = (int)i;
                selectedText.setString(options[i].getString());
                isOpen = false;
                break;
            }
        }
    }
}

int Dropdown::getSelectedIndex() const
{
    return selectedIndex;
}

std::string Dropdown::getSelectedItem() const
{
    return selectedText.getString();
}

void Dropdown::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(box, states);
    target.draw(selectedText, states);

    if (isOpen)
    {
        for (const auto& option : options)
        {
            sf::RectangleShape optionBox;
            optionBox.setSize({width, height});
            optionBox.setFillColor(sf::Color::White);
            optionBox.setOutlineColor(sf::Color::Black);
            optionBox.setOutlineThickness(1);
            optionBox.setPosition(option.getPosition().x - 5.f, option.getPosition().y - 5.f);

            target.draw(optionBox, states);
            target.draw(option, states);
        }
    }
}
