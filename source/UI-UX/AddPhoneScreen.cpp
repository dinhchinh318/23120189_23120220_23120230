#include "AddPhoneScreen.h"

void AddPhoneScreen::draw(sf::RenderWindow& window, sf::Font& font)
{
    sf::Text t("ADD NEW PHONE", font, 28);
    t.setFillColor(sf::Color::Red);
    t.setPosition(300, 100);
    window.draw(t);
    drawBackButton(window);
}