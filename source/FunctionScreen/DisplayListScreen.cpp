#include "DisplayListScreen.h"
#include <sstream>
#include <iomanip>
#include <algorithm> // đảm bảo có dòng này
#undef max
#undef min


// Constructor của lớp DisplayListScreen
DisplayListScreen::DisplayListScreen(sf::Font& font, UITheme theme)
    : BaseScreen(font, theme),
    manufacturerInput(font, sf::Vector2f(400.f, 250.f), sf::Vector2f(200.f, 40.f), "Enter manufacturer"),
    orderInput(font, sf::Vector2f(400.f, 300.f), sf::Vector2f(100.f, 40.f), "asc/desc"),
    priceInput(font, sf::Vector2f(400.f, 250.f), sf::Vector2f(200.f, 40.f), "Enter max price"),
    allButton("All", sf::Vector2f(300.f, 150.f), sf::Vector2f(180.f, 40.f), font, theme),
    byManufacturerButton("By Manufacturer", sf::Vector2f(600.f, 150.f), sf::Vector2f(200.f, 40.f), font, theme),
    byPriceButton("By Price", sf::Vector2f(900.f, 150.f), sf::Vector2f(180.f, 40.f), font, theme),
    findButton("FIND", sf::Vector2f(700.f, 250.f), sf::Vector2f(100.f, 40.f), font, theme),
    backButton("BACK", sf::Vector2f(70.f, 20.f), sf::Vector2f(80.f, 30.f), font, theme) 
{
    if (!connectToSQL(hEnv, hDbc)) return;

    phones = getPhonesFromDatabase();

    // Cài đặt mặc định ban đầu
    showManufacturerInputs = false; // không hiển thị ô nhập hãng
    showPriceInput = false;         // không hiển thị ô nhập giá
    mode = DisplayMode::None;        // chế độ mặc định là chưa chọn
    currentPage = 0;                // bắt đầu từ trang đầu tiên
    rowsPerPage = 10;               // số dòng mỗi trang
    scrollOffsetY = 0.f;            // không cuộn
}

void DisplayListScreen::pollEvent(sf::RenderWindow& window, sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        if (allButton.isClicked(mousePos)) {
            mode = DisplayMode::All;
            showManufacturerInputs = false;
            showPriceInput = false;
            currentPage = 0;
            showResultTable = false; // Reset
        }
        if (byManufacturerButton.isClicked(mousePos)) {
            mode = DisplayMode::ByManufacturer;
            showManufacturerInputs = true;
            showPriceInput = false;
            currentPage = 0;
            showResultTable = false; // Reset
        }
        if (byPriceButton.isClicked(mousePos)) {
            mode = DisplayMode::ByPrice;
            showManufacturerInputs = false;
            showPriceInput = true;
            currentPage = 0;
            showResultTable = false; // Reset
        }

        // Xử lý kích hoạt input box
        if (showManufacturerInputs) {
            if (manufacturerInput.isClicked(mousePos)) manufacturerInput.activate();
            else manufacturerInput.deactivate();
            if (orderInput.isClicked(mousePos)) orderInput.activate();
            else orderInput.deactivate();
        }
        if (showPriceInput) {
            if (priceInput.isClicked(mousePos)) priceInput.activate();
            else priceInput.deactivate();
        }

        // Xử lý nút FIND
        if ((showManufacturerInputs || showPriceInput) && findButton.isClicked(mousePos)) {
            std::cout << "FIND button clicked!\n";
            update(mousePos);
            showResultTable = true; // Đánh dấu đã tìm kiếm
        }

        // Xử lý nút Back
        if ((mode == DisplayMode::All || showResultTable) && backButton.isClicked(mousePos)) {
            // Reset về giao diện chọn chức năng
            mode = DisplayMode::None;
            showManufacturerInputs = false;
            showPriceInput = false;
            showResultTable = false;
            currentPage = 0;
        }
    }

    // Xử lý sự kiện nhập liệu cho input box
    if (showManufacturerInputs) {
        manufacturerInput.handleEvent(event);
        orderInput.handleEvent(event);
    }
    if (showPriceInput) {
        priceInput.handleEvent(event);
    }

    // Scroll để chuyển trang
    if (event.type == sf::Event::MouseWheelScrolled) {
        int totalPages = (phones.size() + rowsPerPage - 1) / rowsPerPage;
        if (event.mouseWheelScroll.delta < 0 && currentPage < totalPages - 1)
            currentPage++;
        else if (event.mouseWheelScroll.delta > 0 && currentPage > 0)
            currentPage--;
    }

    // Phím chuyển trang
    if (event.type == sf::Event::KeyPressed) {
        int totalPages = (phones.size() + rowsPerPage - 1) / rowsPerPage;
        if (event.key.code == sf::Keyboard::Right && currentPage < totalPages - 1)
            currentPage++;
        else if (event.key.code == sf::Keyboard::Left && currentPage > 0)
            currentPage--;
    }
}
// Cập nhật giao diện và dữ liệu dựa trên chế độ
void DisplayListScreen::update(sf::Vector2f mousePos)
{
    this->mousePos = mousePos;

    // Cập nhật giao diện người dùng
    allButton.update(mousePos);
    byManufacturerButton.update(mousePos);
    byPriceButton.update(mousePos);

    if (showManufacturerInputs) {
        manufacturerInput.update(mousePos);
        orderInput.update(mousePos);
    }
    if (showPriceInput) {
        priceInput.update(mousePos);
    }

    // Lọc danh sách theo chế độ
    if (mode == DisplayMode::All) {
        phones = getPhonesFromDatabase();
    } else if (mode == DisplayMode::ByManufacturer) {
        std::string manu = manufacturerInput.getText();
        std::string order = orderInput.getText();
        phones = getPhonesByManuAndPriceOrder(order,manu);
    } else if (mode == DisplayMode::ByPrice) {
        std::string priceStr = priceInput.getText();
        try {
            float maxPrice = std::stof(priceStr);
            phones = getPhonesByMaxPriceDesc(maxPrice);
        } catch (...) {
            phones.clear(); // nếu nhập sai giá
        }
    }
}

void DisplayListScreen::draw(sf::RenderWindow& window, sf::Font& font, AppScreen& screen)
{
    drawDefaultScreen(window, screen, font);

    mousePos = sf::Vector2f(sf::Mouse::getPosition(window));

    // Ẩn các nút chức năng khi đã in ra bảng (showResultTable) hoặc đang ở chế độ All
    if (!(mode == DisplayMode::All || showResultTable)) {
        allButton.draw(window);
        byManufacturerButton.draw(window);
        byPriceButton.draw(window);
    }

    // Vẽ input nếu cần (chỉ khi chưa có kết quả)
    if (!showResultTable) {
        if (showManufacturerInputs) {
            window.draw(manufacturerInput);
            window.draw(orderInput);
        }
        if (showPriceInput) {
            window.draw(priceInput);
        }
        // Vẽ nút FIND khi đang nhập điều kiện
        if (showManufacturerInputs || showPriceInput) {
            findButton.draw(window);
        }
    }

    // Vẽ bảng khi:
    // - mode == All
    // - hoặc (showResultTable == true && (mode == ByManufacturer || mode == ByPrice))
    if (
        mode == DisplayMode::All ||
        (showResultTable && (mode == DisplayMode::ByManufacturer || mode == DisplayMode::ByPrice))
    ) {
        // --- Phần vẽ bảng giữ nguyên ---
        sf::RectangleShape frame;
        frame.setSize(sf::Vector2f(1350, 600));
        frame.setFillColor(sf::Color(255, 255, 255, 200));
        frame.setOutlineColor(sf::Color::Black);
        frame.setOutlineThickness(3);
        frame.setPosition(70, 130);
        window.draw(frame);

        std::vector<float> columnWidths = { 50.f, 240.f, 130.f, 130.f, 100.f, 200.f, 120.f, 110.f, 140.f, 130.f };
        float tableWidth = 1350.0f;
        float cellHeight = 50.0f;
        float startX = 70.0f;
        float startY = 130.0f;

        int visibleRows = 11;
        int totalRows = phones.size() + 1 + 3;
        float maxScroll = std::max(0.f, (totalRows - visibleRows) * cellHeight);
        scrollOffsetY = std::clamp(scrollOffsetY, 0.f, maxScroll);

        float adjustedStartY = startY - scrollOffsetY;

        for (int i = 1; i <= visibleRows; ++i) {
            sf::RectangleShape hLine(sf::Vector2f(tableWidth, 2));
            hLine.setFillColor(sf::Color::Black);
            hLine.setPosition(startX, startY + i * cellHeight);
            window.draw(hLine);
        }

        float x = startX;
        for (size_t i = 0; i < columnWidths.size(); ++i) {
            sf::RectangleShape vLine(sf::Vector2f(2, cellHeight * (visibleRows + 1)));
            vLine.setFillColor(sf::Color::Black);
            vLine.setPosition(x, startY);
            window.draw(vLine);
            x += columnWidths[i];
        }

        std::vector<std::string> headers = {"ID", "Name", "Manufacturer", "Price", "OS", "CPU", "RAM", "ROM", "Screen Size", "Battery"};
        float textX = startX + 15;
        for (size_t i = 0; i < headers.size(); ++i) {
            sf::Text header(headers[i], font, 15);
            header.setFillColor(sf::Color::Black);
            header.setPosition(textX, adjustedStartY + 20);
            window.draw(header);
            textX += columnWidths[i];
        }

        int startRow = currentPage * rowsPerPage;
        int endRow = std::min(static_cast<int>(phones.size()), startRow + rowsPerPage);

        int rowIndex = 0;
        for (int i = startRow; i < endRow; ++i) {
            const auto& phone = phones[i];
            float rowY = adjustedStartY + (rowIndex + 1) * cellHeight + 15;

            sf::Text line;
            line.setFont(font);
            line.setCharacterSize(15);
            line.setFillColor(sf::Color::Black);

            std::ostringstream screenSizeStream;
            screenSizeStream << std::fixed << std::setprecision(2) << phone.getConfig().screenSize;
            std::string screenSizeStr = screenSizeStream.str() + " inch";

            std::vector<std::string> data = {
                std::to_string(phone.getID()),
                phone.getName(),
                phone.getManu(),
                phone.getPrice(),
                phone.getConfig().operatingSystem,
                phone.getConfig().cpu,
                std::to_string(phone.getConfig().ram) + "GB",
                std::to_string(phone.getConfig().rom) + "GB",
                screenSizeStr,
                std::to_string(phone.getConfig().pin) + " mAh"
            };

            float dataX = startX + 20;
            for (size_t j = 0; j < data.size(); ++j) {
                line.setString(data[j]);
                line.setPosition(dataX, rowY);
                window.draw(line);
                dataX += columnWidths[j];
            }

            rowIndex++;
        }

        int totalPages = (phones.size() + rowsPerPage - 1) / rowsPerPage;
        sf::Text pageInfo;
        pageInfo.setFont(font);
        pageInfo.setCharacterSize(16);
        pageInfo.setFillColor(sf::Color::Black);
        pageInfo.setString("Page " + std::to_string(currentPage + 1) + " / " + std::to_string(totalPages));

        float pageInfoX = startX + tableWidth / 2 - pageInfo.getLocalBounds().width / 2;
        float pageInfoY = startY + (rowsPerPage + 1) * cellHeight + 60;
        pageInfo.setPosition(pageInfoX, pageInfoY);
        window.draw(pageInfo);

        backButton.draw(window);
    }
}
