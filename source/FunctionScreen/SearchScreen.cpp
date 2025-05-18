#include "SearchScreen.h"

void SearchScreen::draw(sf::RenderWindow& window, sf::Font& font)
{
    sf::Text t("SEARCH BY NAME", font, 28);
    t.setFillColor(sf::Color::Red);
    t.setPosition(280, 100);
    window.draw(t);
    drawBackButton(window);
}