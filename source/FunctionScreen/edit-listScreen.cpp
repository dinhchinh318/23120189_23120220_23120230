#include "edit-listScreen.h"

EditListScreen::EditListScreen(sf::Font& font, UITheme theme) 
    : BaseScreen(font, theme)
{
}

void EditListScreen::pollEvent(sf::RenderWindow& window, sf::Event& event, AppScreen& screen)
{
    mousePos = sf::Vector2f(sf::Mouse::getPosition(window));

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) 
    {
        mousePos = sf::Vector2f(sf::Mouse::getPosition(window));

        float yRelative = mousePos.y - 130.0f; // 130 là vị trí y bắt đầu bảng
        int clickedRow = static_cast<int>((yRelative + scrollOffsetY) / 50.0f) - 1;
        int index = currentPage * rowsPerPage + clickedRow;

        if (clickedRow >= 0 && index >= 0 && index < phones.size()) {
            if (waitingForDoubleClick &&
                clickClock.getElapsedTime().asMilliseconds() < 300 &&
                std::abs(mousePos.x - lastClickPos.x) < 5 &&
                std::abs(mousePos.y - lastClickPos.y) < 5)
            {
                // Đã nhấn đúp hợp lệ
                indexPhone = index; // lưu index để truyền sang EditExec
                screen = AppScreen::EDIT;
                waitingForDoubleClick = false;
            } else {
                waitingForDoubleClick = true;
                clickClock.restart();
                lastClickPos = mousePos;
            }           
        }

        handleMouseClick();
        if (backButton.isClicked(mousePos))
        {
            screen = AppScreen::EDIT_PHONE;
        }
    }
    
    if (event.type == sf::Event::MouseWheelScrolled) 
    {
        handleScroll(event.mouseWheelScroll.delta);
    }

    if (event.type == sf::Event::KeyPressed) 
    {
        handleKeyboard(event.key.code);
    }
}

void EditListScreen::handleMouseClick()
{
    for (int i = 0; i < buttons.size(); ++i) {
        if (buttons[i].isClicked(mousePos)) {
            currentPage = 0;
            break;
        }
    }
}

void EditListScreen::handleScroll(float delta)
{
    int totalPages = (phones.size() + rowsPerPage - 1) / rowsPerPage;
    if (delta < 0 && currentPage < totalPages - 1)
        ++currentPage;
    else if (delta > 0 && currentPage > 0)
        --currentPage;
}

void EditListScreen::handleKeyboard(sf::Keyboard::Key key)
{
    int totalPages = (phones.size() + rowsPerPage - 1) / rowsPerPage;
    if (key == sf::Keyboard::Right && currentPage < totalPages - 1)
        ++currentPage;
    else if (key == sf::Keyboard::Left && currentPage > 0)
        --currentPage;
}

void EditListScreen::setPhones(const std::vector<Phone>& list)
{
    phones = list;
}

void EditListScreen::draw(sf::RenderWindow& window, sf::Font& font, AppScreen& screen)
{
    drawDefaultScreen(window, screen, font);
    drawBack(window);
    drawTableFrame(window);
    drawTableContent(window, font);
    drawPageIndicator(window, font);
}

void EditListScreen::drawTableFrame(sf::RenderWindow& window)
{
    sf::RectangleShape frame(sf::Vector2f(1350, 600));
    frame.setFillColor(sf::Color(255, 255, 255, 200));
    frame.setOutlineColor(sf::Color::Black);
    frame.setOutlineThickness(3);
    frame.setPosition(70, 130);
    window.draw(frame);
}

void EditListScreen::drawTableContent(sf::RenderWindow& window, sf::Font& font)
{
    std::vector<float> colWidths = { 50.f, 240.f, 130.f, 130.f, 100.f, 200.f, 120.f, 110.f, 140.f, 130.f };
    std::vector<std::string> headers = { "ID", "Name", "Manufacturer", "Price", "OS", "CPU", "RAM", "ROM", "Screen Size", "Battery" };
    
    float startX = 70.0f;
    float startY = 130.0f;
    float cellHeight = 50.0f;
    int visibleRows = 11;

    int totalRows = phones.size() + 1 + 3;
    float maxScroll = max(0.f, (totalRows - visibleRows) * cellHeight);
    scrollOffsetY = std::clamp(scrollOffsetY, 0.f, maxScroll);
    float adjustedY = startY - scrollOffsetY;

    // Draw grid lines
    for (int i = 1; i <= visibleRows; ++i) {
        sf::RectangleShape hLine(sf::Vector2f(1350.f, 2));
        hLine.setFillColor(sf::Color::Black);
        hLine.setPosition(startX, startY + i * cellHeight);
        window.draw(hLine);
    }

    float x = startX;
    for (size_t i = 0; i < colWidths.size(); ++i) {
        sf::RectangleShape vLine(sf::Vector2f(2, cellHeight * (visibleRows + 1)));
        vLine.setFillColor(sf::Color::Black);
        vLine.setPosition(x, startY);
        window.draw(vLine);
        x += colWidths[i];
    }

    // Draw headers
    float textX = startX + 15;
    for (size_t i = 0; i < headers.size(); ++i) {
        sf::Text header(headers[i], font, 15);
        header.setFillColor(sf::Color::Black);
        header.setPosition(textX, adjustedY + 20);
        window.draw(header);
        textX += colWidths[i];
    }

    // Draw rows
    int startRow = currentPage * rowsPerPage;
    int endRow = min(static_cast<int>(phones.size()), startRow + rowsPerPage);

    int rowIndex = 0;

    for (int i = startRow; i < endRow; ++i) {
        const Phone& phone = phones[i];
        float rowY = adjustedY + (rowIndex + 1) * cellHeight + 15;

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
        sf::Text line;
        line.setFont(font);
        line.setCharacterSize(15);
        line.setFillColor(sf::Color::Black);

        for (size_t j = 0; j < data.size(); ++j) {
            line.setString(data[j]);
            line.setPosition(dataX, rowY);
            window.draw(line);
            dataX += colWidths[j];
        }

        rowIndex++;
    }
}

void EditListScreen::drawPageIndicator(sf::RenderWindow& window, sf::Font& font)
{
    int totalPages = (phones.size() + rowsPerPage - 1) / rowsPerPage;
    sf::Text pageInfo("Page " + std::to_string(currentPage + 1) + " / " + std::to_string(totalPages), font, 16);
    pageInfo.setFillColor(sf::Color::Black);

    float pageInfoX = 70 + 1350 / 2 - pageInfo.getLocalBounds().width / 2;
    float pageInfoY = 130 + (rowsPerPage + 1) * 50 + 10;
    pageInfo.setPosition(pageInfoX, pageInfoY);
    window.draw(pageInfo);
}

int EditListScreen::getIndex() const
{
    return indexPhone;
}