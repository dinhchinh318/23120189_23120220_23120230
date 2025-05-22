#include "BaseScreen.h"

BaseScreen::BaseScreen(sf::Font& font, UITheme theme)
{
    float startX = 70;
    float spacing = 230;

    title.setFont(font);
    title.setString("PHONE MANAGEMENT");
    title.setCharacterSize(36);
    title.setFillColor(theme.textColor1);
    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setOrigin(titleBounds.left + titleBounds.width / 2.0f, 0);
    title.setPosition(750, 10);

    buttons.emplace_back("ADD", sf::Vector2f(startX, 65), sf::Vector2f(200, 40), font, theme);
    buttons.emplace_back("DISPLAY", sf::Vector2f(startX + spacing * 1, 65), sf::Vector2f(200, 40), font, theme);
    buttons.emplace_back("SEARCH", sf::Vector2f(startX + spacing * 2, 65), sf::Vector2f(200, 40), font, theme);
    buttons.emplace_back("DELETE", sf::Vector2f(startX + spacing * 3, 65), sf::Vector2f(200, 40), font, theme);
    buttons.emplace_back("EDIT", sf::Vector2f(startX + spacing * 4, 65), sf::Vector2f(200, 40), font, theme);
    buttons.emplace_back("EXIT", sf::Vector2f(startX + spacing * 5, 65), sf::Vector2f(200, 40), font, theme);
}

void BaseScreen::drawDefaultScreen(sf::RenderWindow& window, AppScreen& screen) {
    window.draw(title);

    // Thiết lập chỉ mục của nút được chọn
    int selectedButtonIndex = -1;

    if (screen == AppScreen::ADD_PHONE) selectedButtonIndex = 0;
    else if (screen == AppScreen::DISPLAY_LIST) selectedButtonIndex = 1;
    else if (screen == AppScreen::SEARCH_PHONE) selectedButtonIndex = 2;
    else if (screen == AppScreen::DELETE_PHONE) selectedButtonIndex = 3;
    else if (screen == AppScreen::EDIT_PHONE) selectedButtonIndex = 4;

    // Thiết lập màu chung cho tất cả các nút
    for (auto& button : buttons)
        button.setButtonColor(sf::Color(44, 62, 90)); // Màu mặc định

    // Nếu có nút cần đổi màu, áp dụng màu đỏ cho nút tương ứng
    if (selectedButtonIndex != -1)
        buttons[selectedButtonIndex].setButtonColor(sf::Color(231, 76, 60)); // Màu khi được chọn

    // Vẽ các nút
    for (auto& btn : buttons)
        btn.draw(window);
}
