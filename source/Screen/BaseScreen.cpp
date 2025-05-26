#include "BaseScreen.h"

// Constructor to initialize UI layout and buttons
BaseScreen::BaseScreen(sf::Font& font, UITheme theme)
    : backButton("BACK", sf::Vector2f(70.f, 20.f), sf::Vector2f(80.f, 30.f), font, theme)
{
    float startX = 70;
    float spacing = 230;

    // Setup title text
    title.setFont(font);
    title.setString("PHONE MANAGEMENT");
    title.setCharacterSize(36);
    title.setFillColor(theme.textColor1);
    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setOrigin(titleBounds.left + titleBounds.width / 2.0f, 0);
    title.setPosition(750, 10); // center on top

    // Initialize navigation buttons with spacing
    buttons.emplace_back("ADD",      sf::Vector2f(startX + spacing * 0, 65), sf::Vector2f(200, 40), font, theme);
    buttons.emplace_back("DISPLAY",  sf::Vector2f(startX + spacing * 1, 65), sf::Vector2f(200, 40), font, theme);
    buttons.emplace_back("SEARCH",   sf::Vector2f(startX + spacing * 2, 65), sf::Vector2f(200, 40), font, theme);
    buttons.emplace_back("DELETE",   sf::Vector2f(startX + spacing * 3, 65), sf::Vector2f(200, 40), font, theme);
    buttons.emplace_back("EDIT",     sf::Vector2f(startX + spacing * 4, 65), sf::Vector2f(200, 40), font, theme);
    buttons.emplace_back("EXIT",     sf::Vector2f(startX + spacing * 5, 65), sf::Vector2f(200, 40), font, theme);
}

// Utility function to draw a rectangle box with text centered
void BaseScreen::drawBoxWithText(sf::RenderWindow& window, sf::Font& font,
                                 const std::string& textStr,
                                 sf::Vector2f position, sf::Vector2f size,
                                 unsigned int fontSize,
                                 sf::Color boxColor,
                                 sf::Color outlineColor,
                                 sf::Color textColor)
{
    sf::RectangleShape box(size);
    box.setPosition(position);
    box.setFillColor(boxColor);
    box.setOutlineColor(outlineColor);
    box.setOutlineThickness(2);
    window.draw(box);

    sf::Text text;
    text.setFont(font);
    text.setString(textStr);
    text.setCharacterSize(fontSize);
    text.setFillColor(textColor);

    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.f,
                   textBounds.top + textBounds.height / 2.f);
    text.setPosition(position.x + size.x / 2.f, position.y + size.y / 2.f); // Center text

    window.draw(text);
}

// Draw the back navigation button
void BaseScreen::drawBack(sf::RenderWindow& window)
{
    backButton.draw(window);
}

// Draw the full top menu UI and welcome screen if INIT_SCREEN
void BaseScreen::drawDefaultScreen(sf::RenderWindow& window, AppScreen& screen, sf::Font& font) {
    window.draw(title);

    // Highlight the selected screen’s button
    int selectedButtonIndex = -1;
    if (screen == AppScreen::ADD_PHONE)       selectedButtonIndex = 0;
    else if (screen == AppScreen::DISPLAY_LIST) selectedButtonIndex = 1;
    else if (screen == AppScreen::SEARCH_PHONE) selectedButtonIndex = 2;
    else if (screen == AppScreen::DELETE_PHONE) selectedButtonIndex = 3;
    else if (screen == AppScreen::EDIT_PHONE)   selectedButtonIndex = 4;

    // Set default color for all buttons
    for (auto& button : buttons)
        button.setButtonColor(sf::Color(44, 62, 90));

    // Set highlight color (red) for selected button
    if (selectedButtonIndex != -1)
        buttons[selectedButtonIndex].setButtonColor(sf::Color(231, 76, 60));

    // Draw buttons to the screen
    for (auto& btn : buttons)
        btn.draw(window);

    // Special welcome screen for INIT_SCREEN
    if (screen == AppScreen::INIT_SCREEN) {
        sf::Image image;
        if (!image.loadFromFile("Pictures/decorBackground2.png")) {
            std::cerr << "Can't load file decorBackground2.png" << std::endl;
            return;
        }

        // Make white pixels transparent
        sf::Vector2u size = image.getSize();
        for (unsigned int x = 0; x < size.x; ++x) {
            for (unsigned int y = 0; y < size.y; ++y) {
                if (image.getPixel(x, y) == sf::Color::White) {
                    image.setPixel(x, y, sf::Color(255, 255, 255, 0));
                }
            }
        }

        sf::Texture texture;
        texture.loadFromImage(image);
        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprite.setPosition(200.f, 130.f);
        window.draw(sprite);

        // Draw welcome text
        sf::Text welcome;
        welcome.setFont(font);

        auto drawLine = [&](const std::string& str, float y, int size = 26) {
            welcome.setString(str);
            welcome.setCharacterSize(size);
            welcome.setFillColor(sf::Color::Black);
            welcome.setPosition(570, y);
            window.draw(welcome);
        };

        drawLine("WELCOME TO PHONE MANAGEMENT", 200, 36);
        drawLine("PROJECT PHONE MANAGEMENT", 280);
        drawLine("THANH VIEN:", 330);
        drawLine("TRAN VU DINH CHINH", 380);
        drawLine("HOANG QUOC VIET", 430);
        drawLine("NGUYEN THE DAT", 480);
        drawLine("GIAO VIEN HUONG DAN: TRAN DUY QUANG", 530);
    }
}

