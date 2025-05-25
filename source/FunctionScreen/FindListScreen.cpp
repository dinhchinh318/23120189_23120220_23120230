#include "FindListScreen.h"

// Hàm khởi tạo màn hình tìm kiếm, gọi constructor của BaseScreen
FindListScreen::FindListScreen(sf::Font& font, UITheme theme) : BaseScreen(font, theme)
{
    // Có thể khởi tạo thêm ở đây nếu cần
}  

// Xử lý sự kiện người dùng (chuột, bàn phím, cuộn)
void FindListScreen::pollEvent(sf::RenderWindow& window, sf::Event& event)
{
    // Nếu nhấn chuột trái vào các nút chức năng
    if (event.type == sf::Event::MouseButtonPressed) 
    {
        // Kiểm tra từng nút, nếu được nhấn thì chuyển về trang đầu tiên
        if (buttons[0].isClicked(mousePos)) { currentPage = 0; }
        if (buttons[1].isClicked(mousePos)) { currentPage = 0; }
        if (buttons[2].isClicked(mousePos)) { currentPage = 0; }
        if (buttons[3].isClicked(mousePos)) { currentPage = 0; }
        if (buttons[4].isClicked(mousePos)) { currentPage = 0; }       
    }
    
    // Xử lý sự kiện cuộn chuột để chuyển trang
    if (event.type == sf::Event::MouseWheelScrolled) {
        int totalPages = (phones.size() + rowsPerPage - 1) / rowsPerPage;
        // Cuộn xuống: sang trang tiếp theo nếu chưa phải trang cuối
        if (event.mouseWheelScroll.delta < 0) {
            if (currentPage < totalPages - 1)
                currentPage++;
        // Cuộn lên: về trang trước nếu chưa phải trang đầu
        } else if (event.mouseWheelScroll.delta > 0) {
            if (currentPage > 0)
                currentPage--;
        }
    }

    // Xử lý phím mũi tên trái/phải để chuyển trang
    if (event.type == sf::Event::KeyPressed) {
        int totalPages = (phones.size() + rowsPerPage - 1) / rowsPerPage;
        if (event.key.code == sf::Keyboard::Right) {
            if (currentPage < totalPages - 1) {
                currentPage++;
            }
        } else if (event.key.code == sf::Keyboard::Left) {
            if (currentPage > 0) {
                currentPage--;
            }
        }
    }
}

// Vẽ giao diện màn hình tìm kiếm danh sách điện thoại
void FindListScreen::draw(sf::RenderWindow& window, sf::Font& font, AppScreen& screen)
{
    drawDefaultScreen(window, screen, font); // Vẽ nền mặc định

    mousePos = sf::Vector2f(sf::Mouse::getPosition(window)); // Lấy vị trí chuột

    // Vẽ khung bảng
    sf::RectangleShape frame;
    frame.setSize(sf::Vector2f(1350, 600));
    frame.setFillColor(sf::Color(255, 255, 255, 200));
    frame.setOutlineColor(sf::Color::Black);
    frame.setOutlineThickness(3);
    frame.setPosition(70, 130);
    window.draw(frame);

    // Thiết lập thông số bảng
    std::vector<float> columnWidths = { 50.f, 240.f, 130.f, 130.f, 100.f, 200.f, 120.f, 110.f, 140.f, 130.f};
    float tableWidth = 1350.0f;
    float cellHeight = 50.0f;
    float startX = 70.0f;
    float startY = 130.0f;

    int visibleRows = 11;
    int totalRows = phones.size() + 1 + 3;
    float maxScroll = max(0.f, (totalRows - visibleRows) * cellHeight);
    scrollOffsetY = std::clamp(scrollOffsetY, 0.f, maxScroll);

    float adjustedStartY = startY - scrollOffsetY;

    // Vẽ các đường ngang (ngăn hàng)
    for (int i = 1; i <= visibleRows; ++i) {
        sf::RectangleShape hLine(sf::Vector2f(tableWidth, 2));
        hLine.setFillColor(sf::Color::Black);
        hLine.setPosition(startX, startY + i * cellHeight);
        window.draw(hLine);
    }

    // Vẽ các đường dọc (ngăn cột)
    float x = startX;
    for (size_t i = 0; i < columnWidths.size(); ++i) {
        sf::RectangleShape vLine(sf::Vector2f(2, cellHeight * (visibleRows + 1)));
        vLine.setFillColor(sf::Color::Black);
        vLine.setPosition(x, startY);
        window.draw(vLine);
        if (i < columnWidths.size())
            x += columnWidths[i];
    }

    // Vẽ tiêu đề các cột
    std::vector<std::string> headers = {"ID", "Name", "Manufacturer", "Price", "OS", "CPU", "RAM", "ROM", "Screen Size", "Battery"};
    float textX = startX + 15;
    for (size_t i = 0; i < headers.size(); ++i) {
        sf::Text header(headers[i], font, 15);
        header.setFillColor(sf::Color::Black);
        header.setPosition(textX, adjustedStartY + 20);
        window.draw(header);
        textX += columnWidths[i];
    }

    // Xác định dòng bắt đầu và kết thúc để hiển thị theo trang
    int startRow = currentPage * rowsPerPage;
    int endRow = min(static_cast<int>(phones.size()), startRow + rowsPerPage);

    int rowIndex = 0;
    // Vẽ từng dòng dữ liệu điện thoại
    for (int i = startRow; i < endRow; ++i) {
        const auto& phone = phones[i];
        float rowY = adjustedStartY + (rowIndex + 1) * cellHeight + 15;

        sf::Text line;
        line.setFont(font);
        line.setCharacterSize(15);
        line.setFillColor(sf::Color::Black);

        std::vector<std::string> data = {
            std::to_string(phone.getID()),
            phone.getName(),
            phone.getManu(),
            phone.getPrice(),
            phone.getConfig().operatingSystem,
            phone.getConfig().cpu,
            std::to_string(phone.getConfig().ram) + "GB",
            std::to_string(phone.getConfig().rom) + "GB",
            std::to_string(phone.getConfig().screenSize) + " inch",
            std::to_string(phone.getConfig().pin) + " mAh"
        };

        float dataX = startX + 15;
        for (size_t j = 0; j < data.size(); ++j) {
            line.setString(data[j]);
            line.setPosition(dataX, rowY);
            window.draw(line);
            dataX += columnWidths[j];
        }

        rowIndex++;
    }

    // Vẽ thông tin số trang ở dưới bảng
    int totalPages = (phones.size() + rowsPerPage - 1) / rowsPerPage;
    sf::Text pageInfo;
    pageInfo.setFont(font);
    pageInfo.setCharacterSize(16);
    pageInfo.setFillColor(sf::Color::Black);
    pageInfo.setString("Page " + std::to_string(currentPage + 1) + " / " + std::to_string(totalPages));

    // Căn giữa dưới bảng
    float pageInfoX = startX + tableWidth / 2 - pageInfo.getLocalBounds().width / 2;
    float pageInfoY = startY + (rowsPerPage + 1) * cellHeight + 10;
    pageInfo.setPosition(pageInfoX, pageInfoY);
    window.draw(pageInfo);
}