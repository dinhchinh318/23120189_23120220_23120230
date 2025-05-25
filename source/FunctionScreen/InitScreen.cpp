#include "InitScreen.h"

InitScreen::InitScreen(sf::Font& font, UITheme theme) : BaseScreen(font, theme)
{
}


void InitScreen::draw(sf::RenderWindow& window, sf::Font& font, AppScreen& screen)
{
    drawDefaultScreen(window, screen, font);
    /* drawBoxWithText(window, font, "Welcome to Phone Manager!",
        sf::Vector2f(450, 200), sf::Vector2f(600, 500)); */
}

void InitScreen::pollEvent(sf::RenderWindow& window, sf::Event& event, AppScreen& screen)
{
}