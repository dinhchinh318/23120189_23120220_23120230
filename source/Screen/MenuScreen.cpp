#include "MenuScreen.h"

MenuScreen::MenuScreen(sf::Font& font, UITheme theme) : BaseScreen(font, theme)
{
    float startY = 235;
    float spacing = 70;

    title.setFont(font);
    title.setString("PHONE MANAGEMENT");
    title.setCharacterSize(32);
    title.setFillColor(theme.textColor1);
    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setOrigin(titleBounds.left + titleBounds.width / 2.0f, 0);
    title.setPosition(585, 80);

    buttons.emplace_back("ADD NEW PHONE", sf::Vector2f(445, startY + spacing * 0), sf::Vector2f(290, 50), font, theme);
    buttons.emplace_back("DISPLAY PHONE LIST", sf::Vector2f(445, startY + spacing * 1), sf::Vector2f(290, 50), font, theme);
    buttons.emplace_back("SEARCH BY NAME", sf::Vector2f(445, startY + spacing * 2), sf::Vector2f(290, 50), font, theme);
    buttons.emplace_back("DELETE BY ID", sf::Vector2f(445, startY + spacing * 3), sf::Vector2f(290, 50), font, theme);
    buttons.emplace_back("EDIT PHONE", sf::Vector2f(445, startY + spacing * 4), sf::Vector2f(290, 50), font, theme);
    buttons.emplace_back("EXIT", sf::Vector2f(445, startY + spacing * 5), sf::Vector2f(290, 50), font, theme);
}

void MenuScreen::draw(sf::RenderWindow& window, sf::Font& font)
{
    window.draw(title);
    for (auto& btn : buttons)
        btn.draw(window);
}

void MenuScreen::update(sf::Vector2f mousePos) 
{
    for (auto& btn : buttons)
        btn.update(mousePos);
}

void MenuScreen::handleClick(sf::Vector2f mousePos, AppScreen& screen, sf::RenderWindow& window) {
    for (auto& btn : buttons) {
        if (btn.isClicked(mousePos)) {
            std::string label = btn.getLabel();
            std::cout << "Clicked: " << label << std::endl;

            if (label == "ADD NEW PHONE")
                screen = AppScreen::ADD_PHONE;
            else if (label == "DISPLAY PHONE LIST")
                screen = AppScreen::DISPLAY_LIST;
            else if (label == "SEARCH BY NAME")
                screen = AppScreen::SEARCH_PHONE;
            else if (label == "DELETE BY ID")
                screen = AppScreen::DELETE_PHONE;
            else if (label == "EDIT PHONE")
                screen = AppScreen::EDIT_PHONE;
            else if (label == "EXIT")
                window.close();
        }
    }
}