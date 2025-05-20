#include "BaseScreen.h"

BaseScreen::BaseScreen(sf::Font& font, UITheme theme)
        : backButton("<< BACK", sf::Vector2f(20, 20), sf::Vector2f(120, 40), font, theme) {}

void BaseScreen::drawBackButton(sf::RenderWindow& window) 
{
    backButton.draw(window);
}