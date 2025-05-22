#include "InitScreen.h"

InitScreen::InitScreen(sf::Font& font, UITheme theme) : BaseScreen(font, theme)
{
}


void InitScreen::draw(sf::RenderWindow& window, sf::Font& font, AppScreen& screen)
{
    drawDefaultScreen(window, screen);
}

void InitScreen::pollEvent(sf::RenderWindow& window, sf::Event& event)
{
}