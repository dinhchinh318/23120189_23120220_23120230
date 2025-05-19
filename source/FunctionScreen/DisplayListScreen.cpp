#include "DisplayListScreen.h"

void DisplayListScreen::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseWheelScrolled) {
        scrollOffsetY -= event.mouseWheelScroll.delta * 30;
    }
}

void DisplayListScreen::draw(sf::RenderWindow& window, sf::Font& font)
{
    window.draw(title);
    drawBackButton(window);

    sf::RectangleShape frame;
    frame.setSize(sf::Vector2f(1350, 600));
    frame.setFillColor(sf::Color(255, 255, 255, 200));
    frame.setOutlineColor(sf::Color::Black);
    frame.setOutlineThickness(3);
    frame.setPosition(70, 130);
    window.draw(frame);

    std::vector<float> columnWidths = { 50.f, 240.f, 130.f, 130.f, 100.f, 170.f, 120.f, 120.f, 150.f, 140.f};
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
    for (size_t i = 0; i <= columnWidths.size(); ++i) {
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

    int rowIndex = 1;
    for (const auto& phone : phones) {
        float rowY = adjustedStartY + rowIndex * cellHeight + 15;

        if (rowY + cellHeight < startY || rowY > startY + visibleRows * cellHeight) {
            rowIndex++;
            continue;
        }

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
        for (size_t i = 0; i < data.size(); ++i) {
            line.setString(data[i]);
            line.setPosition(dataX, rowY);
            window.draw(line);
            dataX += columnWidths[i];
        }

        rowIndex++;
    }

}
