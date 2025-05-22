#include "SearchScreen.h"

SearchScreen::SearchScreen(sf::Font& font, UITheme theme) : BaseScreen(font, theme),
        findButton("FIND", sf::Vector2f(1500 / 2.0f - 160.0f, 800 - 100.0f), sf::Vector2f(320, 50), font, theme),
        popup(1500, 800)
{
    float startX = 280, startY = 180, width = 600, height = 40, gap = 50;

    std::vector<std::string> labels = 
    {
        "ID", "Name", "Manufacturer", "Price", "Operating System", "CPU", "RAM", "ROM", "Screen", "Pin"
    };

    for (int i = 0; i < labels.size(); ++i) 
    {
        fields.emplace_back(font, sf::Vector2f(startX, startY + i * gap), sf::Vector2f(width, height));
    }

    for (int i = 0; i < labels.size(); i++)
    {
        fields[i].setlabel(labels[i]);
    }

    if (!connectToSQL(hEnv, hDbc)) 
    {
        return;
    }
}

void SearchScreen::draw(sf::RenderWindow& window, sf::Font& font, AppScreen& screen)
{
    if (buttons[0].isClicked(mousePos))
    {
        for (auto& field : fields) {
            field.setText("");
            field.setContent("");
            field.setSelected(false);
        }
    }
    if (buttons[1].isClicked(mousePos))
    {
        for (auto& field : fields) {
            field.setText("");
            field.setContent("");
            field.setSelected(false);
        }
    }
    if (buttons[2].isClicked(mousePos))
    {
        for (auto& field : fields) {
            field.setText("");
            field.setContent("");
            field.setSelected(false);
        }
    }
    if (buttons[3].isClicked(mousePos))
    {
        for (auto& field : fields) {
            field.setText("");
            field.setContent("");
            field.setSelected(false);
        }
    }
    if (buttons[4].isClicked(mousePos))
    {
        for (auto& field : fields) {
            field.setText("");
            field.setContent("");
            field.setSelected(false);
        }
    }
    drawDefaultScreen(window, screen);
    findButton.draw(window);

    mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
    for (auto& field : fields) field.draw(window);

    popup.draw(window); 
}

std::vector<Phone> SearchScreen::handleFindButton(SQLHDBC db, std::vector<Phone>& phones)
{
    pList.clear();

    try 
    {
        SQLHSTMT stmt;
        SQLAllocHandle(SQL_HANDLE_STMT, db, &stmt);

        std::wstring whereClause = L"";
        bool hasCondition = false;

        auto appendCondition = [&](const std::wstring& condition) {
            if (hasCondition) whereClause += L" AND ";
            whereClause += condition;
            hasCondition = true;
        };

        // Các điều kiện tìm kiếm
        if (!fields[0].getText().empty()) {
            int id = std::stoi(fields[0].getText());
            appendCondition(L"ID = " + std::to_wstring(id));
        }
        if (!fields[1].getText().empty()) {
            appendCondition(L"NAMEPHONE LIKE N'%" + stringToWString(fields[1].getText()) + L"%'");
        }
        if (!fields[2].getText().empty()) {
            appendCondition(L"MANUFACTURER LIKE N'%" + stringToWString(fields[2].getText()) + L"%'");
        }
        if (!fields[3].getText().empty()) {
            appendCondition(L"PRICE = '" + stringToWString(fields[3].getText())+ L"'");
        }
        if (!fields[4].getText().empty()) {
            appendCondition(L"OPERATINGSYSTEM LIKE N'%" + stringToWString(fields[4].getText()) + L"%'");
        }
        if (!fields[5].getText().empty()) {
            appendCondition(L"CPU LIKE N'%" + stringToWString(fields[5].getText()) + L"%'");
        }
        if (!fields[6].getText().empty()) {
            int ram = std::stoi(fields[6].getText());
            appendCondition(L"RAM = " + std::to_wstring(ram));
        }
        if (!fields[7].getText().empty()) {
            int rom = std::stoi(fields[7].getText());
            appendCondition(L"ROM = " + std::to_wstring(rom));
        }
        if (!fields[8].getText().empty()) {
            float screenSize = std::stof(fields[8].getText());
            appendCondition(L"SCREENSIZE = " + std::to_wstring(screenSize));
        }
        if (!fields[9].getText().empty()) {
            int pin = std::stoi(fields[9].getText());
            appendCondition(L"PIN = " + std::to_wstring(pin));
        }

        if (!hasCondition) {
            popup.show("Please fill in at least one field!", sf::Color::Red);
            SQLFreeHandle(SQL_HANDLE_STMT, stmt);
            return phones;
        }

        std::wstring query = L"SELECT * FROM PHONE WHERE " + whereClause;

        SQLRETURN ret = SQLExecDirectW(stmt, (SQLWCHAR*)query.c_str(), SQL_NTS);
        if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
            while (SQLFetch(stmt) == SQL_SUCCESS)
            {
                int id, ram, rom, pin;
                float screenSize;
                char name[101], manu[101], price[101], os[101], cpu[101];

                SQLGetData(stmt, 1, SQL_C_LONG, &id, 0, NULL);
                SQLGetData(stmt, 2, SQL_C_CHAR, name, sizeof(name), NULL);
                SQLGetData(stmt, 3, SQL_C_CHAR, manu, sizeof(manu), NULL);
                SQLGetData(stmt, 4, SQL_C_CHAR, price, sizeof(price), NULL);
                SQLGetData(stmt, 5, SQL_C_CHAR, os, sizeof(os), NULL);
                SQLGetData(stmt, 6, SQL_C_CHAR, cpu, sizeof(cpu), NULL);
                SQLGetData(stmt, 7, SQL_C_LONG, &ram, 0, NULL);
                SQLGetData(stmt, 8, SQL_C_LONG, &rom, 0, NULL);
                SQLGetData(stmt, 9, SQL_C_FLOAT, &screenSize, 0, NULL);
                SQLGetData(stmt, 10, SQL_C_LONG, &pin, 0, NULL);

                ConfigPhone config = {os, cpu, ram, rom, screenSize, pin};
                Phone newPhone(id, name, manu, config, price);
                phones.push_back(newPhone);
            }
            if (phones.empty()) {
                popup.show("Not Found!", sf::Color::Red);
            } 
            else {
                popup.show("Found Successfully!", sf::Color::Green);
            }
        } 
        else {
            popup.show("Failed query!", sf::Color::Red);
        }

        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    } 
    catch (const std::invalid_argument&) {
        popup.show("Invalid number format!!", sf::Color::Red);
    } 
    catch (const std::out_of_range&) {
        popup.show("Number out of range!", sf::Color::Red);
    }

    pList = phones;

    return phones;
}

vector<Phone> SearchScreen::getPhone()
{
    return pList;
}

void SearchScreen::pollEvent(sf::RenderWindow& window, sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed) {
        for (auto& field : fields) {
            field.setSelected(field.contains(mousePos));
        }

        if (findButton.isClicked(mousePos))
        {
            pList = handleFindButton(hDbc, pList);
        }

        if (buttons[0].isClicked(mousePos))
        {
            for (auto& field : fields) {
                field.setText("");
                field.setContent("");
                field.setSelected(false);
            }
        }
        if (buttons[1].isClicked(mousePos))
        {
            for (auto& field : fields) {
                field.setText("");
                field.setContent("");
                field.setSelected(false);
            }
        }
        if (buttons[2].isClicked(mousePos))
        {
            for (auto& field : fields) {
                field.setText("");
                field.setContent("");
                field.setSelected(false);
            }
        }
        if (buttons[3].isClicked(mousePos))
        {
            for (auto& field : fields) {
                field.setText("");
                field.setContent("");
                field.setSelected(false);
            }
        }
        if (buttons[4].isClicked(mousePos))
        {
            for (auto& field : fields) {
                field.setText("");
                field.setContent("");
                field.setSelected(false);
            }
        }
    }

    if (event.type == sf::Event::TextEntered) {
        if (inputClock.getElapsedTime().asMilliseconds() > 50) {
            for (auto& field : fields) {
                if (field.getSelected()) {
                    field.typedOn(event);
                    inputClock.restart();
                    break;
                }
            }
        }
    }

    for (auto& field : fields) {
        field.handleEvent(event);
        if (field.getLength() == true && event.type == sf::Event::TextEntered)
        {
            popup.show("Can't input", sf::Color::Red);
        }
    }
}

void SearchScreen::handleClick(sf::Vector2f mousePos, AppScreen& screen, sf::RenderWindow& window) {
    if (findButton.isClicked(mousePos) && pList.size() != 0)
    {      
        screen = AppScreen::FIND_LIST;
    }
}