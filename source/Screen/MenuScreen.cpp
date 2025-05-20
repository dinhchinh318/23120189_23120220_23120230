#include "MenuScreen.h"

MenuScreen::MenuScreen(sf::Font& font, UITheme theme) : BaseScreen(font, theme)
{
    // Điều chỉnh vị trí tiêu đề và các nút cho màn hình 1500x1000
    float startY = 250;  // Vị trí bắt đầu cho nút, thay đổi từ 235
    float spacing = 90;  // Khoảng cách giữa các nút, tăng từ 70 thành 90 để tránh bị chồng lấn

    title.setFont(font);
    title.setString("PHONE MANAGEMENT");
    title.setCharacterSize(48);  // Tăng kích thước chữ tiêu đề để nổi bật hơn
    title.setFillColor(theme.textColor1);
    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setOrigin(titleBounds.left + titleBounds.width / 2.0f, 0);  // Căn chỉnh trung tâm
    title.setPosition(750, 100);  // Căn giữa tiêu đề với kích thước màn hình 1500x1000

    // Thêm các nút với vị trí và kích thước điều chỉnh lại cho phù hợp với màn hình lớn hơn
    buttons.emplace_back("ADD NEW PHONE", sf::Vector2f(600, startY + spacing * 0), sf::Vector2f(300, 60), font, theme);
    buttons.emplace_back("DISPLAY PHONE LIST", sf::Vector2f(600, startY + spacing * 1), sf::Vector2f(300, 60), font, theme);
    buttons.emplace_back("SEARCH BY NAME", sf::Vector2f(600, startY + spacing * 2), sf::Vector2f(300, 60), font, theme);
    buttons.emplace_back("DELETE BY ID", sf::Vector2f(600, startY + spacing * 3), sf::Vector2f(300, 60), font, theme);
    buttons.emplace_back("EDIT PHONE", sf::Vector2f(600, startY + spacing * 4), sf::Vector2f(300, 60), font, theme);
    buttons.emplace_back("EXIT", sf::Vector2f(600, startY + spacing * 5), sf::Vector2f(300, 60), font, theme);
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

void MenuScreen::pollEvent(sf::RenderWindow& window, sf::Event& event)
{

}