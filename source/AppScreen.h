#ifndef _APP_SCREEN_H_
#define _APP_SCREEN_H_

#include "Menu.h"

class BaseScreen {
protected:
    Button backButton;

public:
    BaseScreen(sf::Font& font, UITheme theme)
        : backButton("<< BACK", sf::Vector2f(20, 20), sf::Vector2f(120, 40), font, theme) {}

    virtual void draw(sf::RenderWindow& window, sf::Font& font) = 0;
    virtual bool handleBack(sf::Vector2f mousePos, AppScreen& screen) {
        if (backButton.isClicked(mousePos)) {
            screen = AppScreen::MENU;
            return true;
        }
        return false;
    }
    void drawBackButton(sf::RenderWindow& window) {
        backButton.draw(window);
    }
};

class AddPhoneScreen : public BaseScreen {
public:
    AddPhoneScreen(sf::Font& font, UITheme theme) : BaseScreen(font, theme) {}
    void draw(sf::RenderWindow& window, sf::Font& font) override {
        sf::Text t("ADD NEW PHONE", font, 28);
        t.setFillColor(sf::Color::Red);
        t.setPosition(300, 100);
        window.draw(t);
        drawBackButton(window);
    }
};

// Tương tự cho các màn hình còn lại
class DisplayListScreen : public BaseScreen {
public:
    DisplayListScreen(sf::Font& font, UITheme theme) : BaseScreen(font, theme) {}
    void draw(sf::RenderWindow& window, sf::Font& font) override {
        sf::Text t("DISPLAY PHONE LIST", font, 28);
        t.setFillColor(sf::Color::Red);
        t.setPosition(250, 100);
        window.draw(t);
        drawBackButton(window);
    }
};

class SearchScreen : public BaseScreen {
public:
    SearchScreen(sf::Font& font, UITheme theme) : BaseScreen(font, theme) {}
    void draw(sf::RenderWindow& window, sf::Font& font) override {
        sf::Text t("SEARCH BY NAME", font, 28);
        t.setFillColor(sf::Color::Red);
        t.setPosition(280, 100);
        window.draw(t);
        drawBackButton(window);
    }
};

class DeleteScreen : public BaseScreen {
public:
    DeleteScreen(sf::Font& font, UITheme theme) : BaseScreen(font, theme) {}
    void draw(sf::RenderWindow& window, sf::Font& font) override {
        sf::Text t("DELETE BY ID", font, 28);
        t.setFillColor(sf::Color::Red);
        t.setPosition(290, 100);
        window.draw(t);
        drawBackButton(window);
    }
};

class EditScreen : public BaseScreen {
public:
    EditScreen(sf::Font& font, UITheme theme) : BaseScreen(font, theme) {}
    void draw(sf::RenderWindow& window, sf::Font& font) override {
        sf::Text t("EDIT PHONE INFORMATION", font, 28);
        t.setFillColor(sf::Color::Red);
        t.setPosition(300, 100);
        window.draw(t);
        drawBackButton(window);
    }
};

#endif