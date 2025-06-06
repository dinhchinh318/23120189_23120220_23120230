#ifndef _DIS_SCREEN_H_
#define _DIS_SCREEN_H_

#include "../Screen/BaseScreen.h"
#include "InputBox.h"
#include "Dropdown.h"
#include "InputField.h"
#include "Popup.h"

// class DisplayListScreen : public BaseScreen 
// {
// private:
//     std::vector<Phone> phones;
//     float scrollOffsetY = 0;
//     int currentPage = 0;
//     int rowsPerPage = 11;

//     sf::Vector2f mousePos;
// public:
//     DisplayListScreen(sf::Font& font, UITheme theme);

//     void draw(sf::RenderWindow& window, sf::Font& font, AppScreen& screen) override;
//     void pollEvent(sf::RenderWindow& window, sf::Event& event, AppScreen& screen) override;
    
//     void update(sf::Vector2f mousePos) override
//     {
//         for (auto& btn : buttons)
//             btn.update(mousePos);
//     }
// };

enum class DisplayMode {
    None,       
    All,
    ByManufacturer,
    ByPrice
};

// Lớp DisplayListScreen kế thừa từ BaseScreen và hiển thị danh sách điện thoại
class DisplayListScreen : public BaseScreen 
{
private:
    // Dữ liệu danh sách điện thoại
    std::vector<Phone> phones;

    // Cấu hình phân trang và cuộn
    float scrollOffsetY = 0;
    int currentPage = 0;
    int rowsPerPage = 11;

    // Vị trí chuột hiện tại
    sf::Vector2f mousePos;

    // Chế độ hiển thị hiện tại: All / ByManufacturer / ByPrice
    DisplayMode mode = DisplayMode::All;

    // Các input box dùng để lọc theo hãng hoặc theo giá
    InputBox manufacturerInput;
    InputBox orderInput;     // asc hoặc desc
    InputBox priceInput;

    // InputField manufacturerInput;
    // InputField orderInput;     // asc hoặc desc
    // InputField priceInput;

    // Nút chọn chế độ lọc
    Button allButton;
    Button byManufacturerButton;
    Button byPriceButton;
    Button findButton;
    Button backButton;

    // Trạng thái hiển thị input tương ứng với chế độ lọc
    bool showManufacturerInputs = false;
    bool showPriceInput = false;
    bool showResultTable = false;

    //InputField* selectedInput = nullptr; 

public:
    // Hàm khởi tạo
    DisplayListScreen(sf::Font& font, UITheme theme);

    // Xử lý sự kiện người dùng
    void pollEvent(sf::RenderWindow& window, sf::Event& event, AppScreen&) override;

    // Cập nhật các thành phần UI dựa theo vị trí chuột
    void update(sf::Vector2f mousePos) override;

    // Vẽ toàn bộ nội dung lên cửa sổ
    void draw(sf::RenderWindow& window, sf::Font& font, AppScreen& screen) override;

    // Cập nhật danh sách theo chế độ lọc hiện tại
    //void updatePhones(sf::Vector2f mousePos);
};

#endif