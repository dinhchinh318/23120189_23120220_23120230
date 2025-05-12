#ifndef _MENU_H_
#define _MENU_H_

#include "Button.h"

enum class AppScreen {
    MENU,
    ADD_PHONE,
    DISPLAY_LIST,
    SEARCH_PHONE,
    DELETE_PHONE,
    EDIT_PHONE
};

class Menu {
private:
    std::vector<Button> buttons;
    UITheme theme;
    sf::Text title;

public:
    Menu(sf::Font& font, UITheme theme) : theme(theme) {
        float startY = 200;
        float spacing = 70;

        title.setFont(font);
        title.setString("PHONE MANAGEMENT");
        title.setCharacterSize(32);
        title.setFillColor(theme.textColor1);
        sf::FloatRect titleBounds = title.getLocalBounds();
        title.setOrigin(titleBounds.left + titleBounds.width / 2.0f, 0);
        title.setPosition(500, 80);

        buttons.emplace_back("ADD NEW PHONE", sf::Vector2f(365, startY + spacing * 0), sf::Vector2f(290, 50), font, theme);
        buttons.emplace_back("DISPLAY PHONE LIST", sf::Vector2f(365, startY + spacing * 1), sf::Vector2f(290, 50), font, theme);
        buttons.emplace_back("SEARCH BY NAME", sf::Vector2f(365, startY + spacing * 2), sf::Vector2f(290, 50), font, theme);
        buttons.emplace_back("DELETE BY ID", sf::Vector2f(365, startY + spacing * 3), sf::Vector2f(290, 50), font, theme);
        buttons.emplace_back("EDIT PHONE", sf::Vector2f(365, startY + spacing * 4), sf::Vector2f(290, 50), font, theme);
        buttons.emplace_back("EXIT", sf::Vector2f(365, startY + spacing * 5), sf::Vector2f(290, 50), font, theme);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(title);
        for (auto& btn : buttons)
            btn.draw(window);
    }

    void update(sf::Vector2f mousePos) {
        for (auto& btn : buttons)
            btn.update(mousePos);
    }

    void handleClick(sf::Vector2f mousePos, AppScreen& screen, sf::RenderWindow& window) {
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
};

#endif
