#ifndef _DROPDOWN_H_
#define _DROPDOWN_H_

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Dropdown : public sf::Drawable
{
private:
    sf::RectangleShape box;
    sf::Text selectedText;
    std::vector<sf::Text> options;
    sf::Font& font;
    bool isOpen = false;
    int selectedIndex = 0;

    float width;
    float height;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    Dropdown(sf::Font& font, const std::vector<std::string>& items, float width = 200.f, float height = 30.f);

    void setPosition(float x, float y);
    void update(const sf::Vector2f& mousePos, bool mouseClicked);
    int getSelectedIndex() const;
    std::string getSelectedItem() const;
};

#endif
