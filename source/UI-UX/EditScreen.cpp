#include "EditScreen.h"

void EditScreen::draw(sf::RenderWindow& window, sf::Font& font)
{
    sf::Text t("EDIT PHONE INFORMATION", font, 28);
    t.setFillColor(sf::Color::Red);
    t.setPosition(300, 100);
    window.draw(t);
    drawBackButton(window);
}