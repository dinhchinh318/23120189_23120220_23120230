#ifndef _DISPLAY_LIST_SCREEN_H_
#define _DISPLAY_LIST_SCREEN_H_

#include "../Screen/BaseScreen.h"

class DisplayListScreen : public BaseScreen 
{
private:
    std::vector<Phone> phones;  // Danh sách điện thoại
    sf::Text title;

public:
    DisplayListScreen(sf::Font& font, UITheme theme) : BaseScreen(font, theme) {
        title.setFont(font);
        title.setString("DISPLAY PHONE LIST");
        title.setCharacterSize(28);
        title.setFillColor(sf::Color::Red);
        title.setPosition(430, 65);

        // Đọc dữ liệu từ DB (bạn phải gọi hàm tải trước đó)
        SQLHENV hEnv;
        SQLHDBC hDbc;
        phones = getPhonesFromDatabase();
    }

    void draw(sf::RenderWindow& window, sf::Font& font) override;
};

#endif