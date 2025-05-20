#include "FindListScreen.h"

FindListScreen::FindListScreen(sf::Font& font, UITheme theme) : BaseScreen(font, theme)
{
    
}  

void FindListScreen::pollEvent(sf::RenderWindow& window, sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed) 
    {
        if (backButton.isClicked(mousePos))
        {
            currentPage = 0;
        }
    }
    
    if (event.type == sf::Event::MouseWheelScrolled) {
        int totalPages = (phones.size() + rowsPerPage - 1) / rowsPerPage;

        if (event.mouseWheelScroll.delta < 0) { // Scroll xuống
            if (currentPage < totalPages - 1)
                currentPage++;
        } else if (event.mouseWheelScroll.delta > 0) { // Scroll lên
            if (currentPage > 0)
                currentPage--;
        }
    }

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

void FindListScreen::draw(sf::RenderWindow& window, sf::Font& font)
{
    sf::Text t("PHONE LIST", font, 28);
    t.setFillColor(sf::Color::Red);

    sf::FloatRect textRect = t.getLocalBounds();
    t.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    t.setPosition(1500 / 2.0f, 800 / 7.9f);
    window.draw(t);
    drawBackButton(window);

    mousePos = sf::Vector2f(sf::Mouse::getPosition(window));

    sf::RectangleShape frame;
    frame.setSize(sf::Vector2f(1350, 600));
    frame.setFillColor(sf::Color(255, 255, 255, 200));
    frame.setOutlineColor(sf::Color::Black);
    frame.setOutlineThickness(3);
    frame.setPosition(70, 130);
    window.draw(frame);

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

    // Draw horizontal lines
    for (int i = 1; i <= visibleRows; ++i) {
        sf::RectangleShape hLine(sf::Vector2f(tableWidth, 2));
        hLine.setFillColor(sf::Color::Black);
        hLine.setPosition(startX, startY + i * cellHeight);
        window.draw(hLine);
    }

    // Draw vertical lines
    float x = startX;
    for (size_t i = 0; i < columnWidths.size(); ++i) {
        sf::RectangleShape vLine(sf::Vector2f(2, cellHeight * (visibleRows + 1)));
        vLine.setFillColor(sf::Color::Black);
        vLine.setPosition(x, startY);
        window.draw(vLine);
        if (i < columnWidths.size())
            x += columnWidths[i];
    }

    // Draw headers
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
    int endRow = min(static_cast<int>(phones.size()), startRow + rowsPerPage);

    int rowIndex = 0;
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