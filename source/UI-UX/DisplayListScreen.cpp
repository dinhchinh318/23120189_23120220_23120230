#include "DisplayListScreen.h"

void DisplayListScreen::draw(sf::RenderWindow& window, sf::Font& font) 
{
    sf::Text t("DISPLAY PHONE LIST", font, 28);
    t.setFillColor(sf::Color::Red);
    t.setPosition(250, 100);
    window.draw(t);
    drawBackButton(window);
}