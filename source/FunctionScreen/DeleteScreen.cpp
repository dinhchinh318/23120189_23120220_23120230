#include "DeleteScreen.h"

void DeleteScreen::draw(sf::RenderWindow& window, sf::Font& font) 
{
    sf::Text t("DELETE BY ID", font, 28);
    t.setFillColor(sf::Color::Red);
    t.setPosition(290, 100);
    window.draw(t);
    drawBackButton(window);
}