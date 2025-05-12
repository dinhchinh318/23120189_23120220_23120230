#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "../PhoneManagement.h"

using namespace std;

struct UITheme {
    sf::Color background = sf::Color(34, 40, 49);
    sf::Color buttonColor = sf::Color(57, 62, 70);
    sf::Color hoverColor = sf::Color(0, 173, 181);
    sf::Color textColor = sf::Color::White;
    sf::Color textColor1 = sf::Color::Red;
    sf::Color borderColor = sf::Color(0, 173, 181);
    float borderRadius = 16.f;
    int outlineThickness = 2;

    unsigned int characterSize = 22;  // 👈 Thêm dòng này để dùng trong Button
};


class Button {
private:
    sf::RectangleShape shape;
    sf::Text text;
    sf::Font& font;
    UITheme theme;
    sf::Color currentColor;

public:
    // Constructor
    Button();
    Button(const std::string& label, sf::Vector2f pos, sf::Vector2f size, sf::Font& f, UITheme theme);

    // function
    void setFont(sf::Font &font);
    void setTextSize(unsigned int size);
    void setTextColor(sf::Color color);
    void setTitle(std::string str);
    void setBackgroundColor(sf::Color color);
    void setPosition(float x, float y);
    void setSize(float width, float height);
    void setScale(float w, float h);
    void setTexture(sf::Texture &texture);
    int getLocalBoundsWidth();
    int getLocalBoundsHeight();
    int getPositionX();
    int getPositionY();
    int getSizeWidth();
    int getSizeHeight();
    void drawTo(sf::RenderWindow &window);

    void centerText();

    void draw(sf::RenderWindow& window) {
        shape.setFillColor(currentColor);
        window.draw(shape);
        window.draw(text);
    }

    void update(sf::Vector2f mousePos) {
        sf::Color targetColor = theme.buttonColor;
        if (shape.getGlobalBounds().contains(mousePos)) {
            targetColor = theme.hoverColor;
        }

        float factor = 0.1f;
        currentColor.r += (targetColor.r - currentColor.r) * factor;
        currentColor.g += (targetColor.g - currentColor.g) * factor;
        currentColor.b += (targetColor.b - currentColor.b) * factor;
    }

    bool isClicked(sf::Vector2f mousePos) {
        return shape.getGlobalBounds().contains(mousePos);
    }

    std::string getLabel() const {
        return text.getString();
    }
    
    bool isMouseOver(sf::RenderWindow &window);
    void setOriginToCenter();
    void setOriginToCenterForText();
};

#endif
