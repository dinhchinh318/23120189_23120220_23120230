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
    text.setPosition(position.x + size.x / 2.f, position.y / 2.f);

    window.draw(text);
}


void BaseScreen::drawDefaultScreen(sf::RenderWindow& window, AppScreen& screen, sf::Font& font) {
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

    if(screen == AppScreen::INIT_SCREEN){
        sf::Image image;
        if (!image.loadFromFile("Pictures/decorBackground2.png")) 
        {
            std::cerr << "Can't load file decorBackground2.png" << std::endl;
            return;
        }

        sf::Vector2u size = image.getSize();
        for (unsigned int x = 0; x < size.x; ++x) {
            for (unsigned int y = 0; y < size.y; ++y) {
                if (image.getPixel(x, y) == sf::Color::White) {
                    image.setPixel(x, y, sf::Color(255, 255, 255, 0)); // trắng, alpha = 0
                }
            }
        }

        sf::Texture texture;
        texture.loadFromImage(image);

        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprite.setPosition(200.f, 130.f);

        window.draw(sprite);


        sf::Text welcome;
        welcome.setFont(font);  // Đảm bảo font đã load
        welcome.setString("WELCOME TO PHONE MANAGEMENT");
        welcome.setCharacterSize(36);
        welcome.setFillColor(sf::Color::Black);
        welcome.setPosition(570, 200);  // Tùy vị trí

        window.draw(welcome);

        
        welcome.setString("PROJECT PHONE MANAGEMENT");
        welcome.setCharacterSize(26);
        welcome.setFillColor(sf::Color::Black);
        welcome.setPosition(570, 280);  // Tùy vị trí
        window.draw(welcome);

        welcome.setString("THANH VIEN:");
        welcome.setCharacterSize(26);
        welcome.setFillColor(sf::Color::Black);
        welcome.setPosition(570, 330);  // Tùy vị trí
        window.draw(welcome);

        welcome.setString("TRAN VU DINH CHINH");
        welcome.setCharacterSize(26);
        welcome.setFillColor(sf::Color::Black);
        welcome.setPosition(570, 380);  // Tùy vị trí
        window.draw(welcome);

        welcome.setString("HOANG QUOC VIET");
        welcome.setCharacterSize(26);
        welcome.setFillColor(sf::Color::Black);
        welcome.setPosition(570, 430);  // Tùy vị trí
        window.draw(welcome);

        welcome.setString("NGUYEN THE DAT");
        welcome.setCharacterSize(26);
        welcome.setFillColor(sf::Color::Black);
        welcome.setPosition(570, 480);  // Tùy vị trí
        window.draw(welcome);

        welcome.setString("GIAO VIEN HUONG DAN: TRAN DUY QUANG");
        welcome.setCharacterSize(26);
        welcome.setFillColor(sf::Color::Black);
        welcome.setPosition(570, 530);  // Tùy vị trí
        window.draw(welcome);
    }


    /* if (screen == AppScreen::INIT_SCREEN) {
        sf::Text welcome;
        welcome.setFont(font);  // Đảm bảo font đã load
        welcome.setString("WELCOME TO PHONE MANAGEMENT");
        welcome.setCharacterSize(36);
        welcome.setFillColor(sf::Color::Red);
        welcome.setPosition(450, 200);  // Tùy vị trí

        window.draw(welcome);

        
        welcome.setString("PROJECT PHONE MANAGEMENT");
        welcome.setCharacterSize(26);
        welcome.setFillColor(sf::Color::Red);
        welcome.setPosition(550, 300);  // Tùy vị trí
        window.draw(welcome);

        welcome.setString("THANH VIEN:");
        welcome.setCharacterSize(26);
        welcome.setFillColor(sf::Color::Red);
        welcome.setPosition(660, 350);  // Tùy vị trí
        window.draw(welcome);

        welcome.setString("TRAN VU DINH CHINH");
        welcome.setCharacterSize(26);
        welcome.setFillColor(sf::Color::Red);
        welcome.setPosition(613, 400);  // Tùy vị trí
        window.draw(welcome);

        welcome.setString("HOANG QUOC VIET");
        welcome.setCharacterSize(26);
        welcome.setFillColor(sf::Color::Red);
        welcome.setPosition(613, 450);  // Tùy vị trí
        window.draw(welcome);

        welcome.setString("NGUYEN THE DAT");
        welcome.setCharacterSize(26);
        welcome.setFillColor(sf::Color::Red);
        welcome.setPosition(613, 500);  // Tùy vị trí
        window.draw(welcome);

        welcome.setString("GIAO VIEN HUONG DAN: TRAN DUY QUANG");
        welcome.setCharacterSize(26);
        welcome.setFillColor(sf::Color::Red);
        welcome.setPosition(490, 550);  // Tùy vị trí
        window.draw(welcome);
    } */

}
