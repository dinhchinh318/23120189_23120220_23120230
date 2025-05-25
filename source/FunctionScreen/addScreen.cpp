#include "addScreen.h"

AddPhoneScreen::AddPhoneScreen(sf::Font& font, UITheme theme) : 
    BaseScreen(font, theme), 
    addButton("ADD +", sf::Vector2f(1500 / 2.0f - 160.0f, 800 - 100.0f), sf::Vector2f(320, 50), font, theme), 
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

    pList = getPhonesFromDatabase();
}

void AddPhoneScreen::draw(sf::RenderWindow& window, sf::Font& font, AppScreen& screen)
{
    drawDefaultScreen(window, screen, font);
    addButton.draw(window);

    mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
    for (auto& field : fields) field.draw(window);

    popup.draw(window);
}

void AddPhoneScreen::pollEvent(sf::RenderWindow& window, sf::Event& event, AppScreen& screen)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        mousePos = sf::Vector2f(sf::Mouse::getPosition(window));

        // Xác định ô nào đang được chọn
        for (auto& field : fields)
            field.setSelected(field.contains(mousePos));

        // Xử lý nút "ADD +"
        if (addButton.isClicked(mousePos)) {
            addPhone(hDbc);
        }

        // Xử lý các nút menu
        for (auto& btn : buttons) {
            if (btn.isClicked(mousePos)) {
                resetAllFields();
                break;
            }
        }
    }

    // Xử lý nhập liệu khi gõ ký tự
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

    // Cập nhật từng ô nhập và kiểm tra giới hạn
    for (auto& field : fields) {
        field.handleEvent(event);

        if (event.type == sf::Event::TextEntered && field.getLength()) {
            popup.show("Can't input", sf::Color::Red);
        }
    }
}


void AddPhoneScreen::resetAllFields() {
    for (auto& field : fields) {
        field.setText("");
        field.setContent("");
        field.setSelected(false);
    }
}

bool AddPhoneScreen::validateFields() {
    for (int i = 0; i < fields.size(); ++i) {
        if (fields[i].getText().empty()) {
            popup.show("Please fill in all fields!", sf::Color::Red);
            for (int i = 0; i < fields.size(); ++i)
            {
                if (fields[i].getText() == "")
                {
                    sf::Color color = sf::Color::Red;
                    fields[i].setOutlineBox(color);
                }
            }
            return false;
        }
    }
    return true;
}

bool AddPhoneScreen::isPhoneIDExisted(SQLHDBC db, int id) {
    SQLHSTMT stmt;
    std::wstring query = L"SELECT COUNT(*) FROM PHONE WHERE ID = " + std::to_wstring(id);

    SQLAllocHandle(SQL_HANDLE_STMT, db, &stmt);
    SQLRETURN ret = SQLExecDirectW(stmt, (SQLWCHAR*)query.c_str(), SQL_NTS);

    bool exists = false;
    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        SQLINTEGER count;
        SQLBindCol(stmt, 1, SQL_C_SLONG, &count, 0, nullptr);
        if (SQLFetch(stmt) == SQL_SUCCESS) {
            exists = count > 0;
        }
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    return exists;
}


void AddPhoneScreen::addPhone(SQLHDBC db) {
    if (!validateFields()) return;

    try {
        // Lấy dữ liệu
        int id = std::stoi(fields[0].getText());
        std::string name = fields[1].getText();
        std::string manu = fields[2].getText();
        std::string price = fields[3].getText();
        ConfigPhone cfg = {
            fields[4].getText(),
            fields[5].getText(),
            std::stoi(fields[6].getText()),
            std::stoi(fields[7].getText()),
            std::stof(fields[8].getText()),
            std::stoi(fields[9].getText())
        };

        // Kiểm tra ID
        if (isPhoneIDExisted(db, id)) {
            popup.show("ID was existed!", sf::Color::Yellow);
            resetAllFields();
            return;
        }

        // Thực hiện insert
        std::wstring query = L"INSERT INTO PHONE(ID, NamePhone, Manufacturer, Price, OperatingSystem, CPU, RAM, ROM, ScreenSize, Pin) VALUES ("
            + std::to_wstring(id) + L", N'" + std::wstring(name.begin(), name.end()) + L"', N'"
            + std::wstring(manu.begin(), manu.end()) + L"', "
            + std::to_wstring(std::stoi(price)) + L", N'" + std::wstring(cfg.operatingSystem.begin(), cfg.operatingSystem.end()) + L"', N'"
            + std::wstring(cfg.cpu.begin(), cfg.cpu.end()) + L"', "
            + std::to_wstring(cfg.ram) + L", "
            + std::to_wstring(cfg.rom) + L", "
            + std::to_wstring(cfg.screenSize) + L", "
            + std::to_wstring(cfg.pin) + L")";

        SQLHSTMT stmt;
        SQLAllocHandle(SQL_HANDLE_STMT, db, &stmt);
        SQLRETURN ret = SQLExecDirectW(stmt, (SQLWCHAR*)query.c_str(), SQL_NTS);

        if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
            popup.show("Save phone into database successful!", sf::Color::Green);
            pList.emplace_back(id, name, manu, cfg, price);
        } else {
            popup.show("Error! Can't save into database!", sf::Color::Red);
        }

        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        resetAllFields();

    } catch (const std::invalid_argument&) {
        popup.show("Invalid number format!", sf::Color::Red);
    } catch (const std::out_of_range&) {
        popup.show("Number out of range!", sf::Color::Red);
    }
}
