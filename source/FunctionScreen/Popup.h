#ifndef _POP_UP_H_
#define _POP_UP_H_

#include "../App/Button.h"

class Popup {
private:
    sf::RectangleShape background;
    // sf::Texture backgroundTexture;
    sf::Text message;
    sf::Font font;
    bool visible = false;
    sf::Clock clock;
    float duration = 2.0f;

public:
    Popup(float width, float height);

    void show(const std::string& msg, sf::Color color = sf::Color::White, float duration = 2.0f);
    void update();
    void draw(sf::RenderWindow& window);
    bool isVisible() const;
};


#endif