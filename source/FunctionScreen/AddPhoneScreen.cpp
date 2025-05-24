#include "AddPhoneScreen.h"

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

void AddPhoneScreen::pollEvent(sf::RenderWindow& window, sf::Event& event)
{   
    if (event.type == sf::Event::MouseButtonPressed) {
        for (auto& field : fields) {
            field.setSelected(field.contains(mousePos));
        }

        if (addButton.isClicked(mousePos))
        {
            addPhone(hDbc);
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

void AddPhoneScreen::addPhone(SQLHDBC db) 
{
    if (!validateFields()) return; 

    try {
        ConfigPhone cfg;
        int id = std::stoi(fields[0].getText());
        std::string name = fields[1].getText();
        std::string manu = fields[2].getText();
        std::string price = fields[3].getText();
        cfg.operatingSystem = fields[4].getText();
        cfg.cpu = fields[5].getText();
        cfg.ram = std::stoi(fields[6].getText());
        cfg.rom = std::stoi(fields[7].getText());
        cfg.screenSize = std::stof(fields[8].getText());
        cfg.pin = std::stoi(fields[9].getText());

        Phone newPhone(id, name, manu, cfg, price);

        pList.push_back(newPhone);

        SQLHSTMT stmt;

        SQLRETURN ret;

        // Kiểm tra xem ID có tồn tại hay không
        std::wstring checkQuery = L"SELECT COUNT(*) FROM PHONE WHERE ID = " + std::to_wstring(id);
        SQLAllocHandle(SQL_HANDLE_STMT, db, &stmt);

        ret = SQLExecDirectW(stmt, (SQLWCHAR*)checkQuery.c_str(), SQL_NTS);

        if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
            SQLINTEGER count;
            SQLBindCol(stmt, 1, SQL_C_SLONG, &count, 0, nullptr);
            ret = SQLFetch(stmt);
            cout << "Count: " << count << endl; // Debugging line
            if (count > 0) {
                popup.show("ID was existed!", sf::Color::Yellow);
                for (auto& field : fields) {
                    field.setText("");
                    field.setContent("");
                    field.setSelected(false);
                }
                SQLFreeHandle(SQL_HANDLE_STMT, stmt);
                return;
            }
        }

        SQLFreeHandle(SQL_HANDLE_STMT, stmt);

        SQLAllocHandle(SQL_HANDLE_STMT, db, &stmt);

        std::wstring query = L"INSERT INTO PHONE(ID, NamePhone, Manufacturer, Price, OperatingSystem, CPU, RAM, ROM, ScreenSize, Pin) VALUES ("
		+ std::to_wstring(id) + L", N'"
		+ std::wstring(name.begin(), name.end()) + L"', N'"
		+ std::wstring(manu.begin(), manu.end()) + L"', "
		+ std::to_wstring(std::stoi(price)) + L", N'"
		+ std::wstring(cfg.operatingSystem.begin(), cfg.operatingSystem.end()) + L"', N'"
		+ std::wstring(cfg.cpu.begin(), cfg.cpu.end()) + L"', "
		+ std::to_wstring(cfg.ram) + L", "
		+ std::to_wstring(cfg.rom) + L", "
		+ std::to_wstring(cfg.screenSize) + L", "
		+ std::to_wstring(cfg.pin) + L")";
        ret = SQLExecDirectW(stmt, (SQLWCHAR*)query.c_str(), SQL_NTS);

        if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
            popup.show("Save phone into database succesful!", sf::Color::Green);
            for (auto& field : fields) {
                    field.setText("");
                    field.setContent("");
                    field.setSelected(false);
                }
        }
        else {
            popup.show("Error! Can't save into database!", sf::Color::Red);
            for (auto& field : fields) {
                    field.setText("");
                    field.setContent("");
                    field.setSelected(false);
                }
            SQLWCHAR sqlState[6];
            SQLINTEGER nativeError;
            SQLWCHAR messageText[256];
            SQLSMALLINT textLength;

            int i = 1;
            while (SQLGetDiagRecW(SQL_HANDLE_STMT, stmt, i, sqlState, &nativeError, messageText, sizeof(messageText) / sizeof(SQLWCHAR), &textLength) == SQL_SUCCESS) {
                std::wcout << L"[Error " << i << L"] SQLSTATE: " << sqlState << std::endl;
                std::wcout << L"Error Code: " << nativeError << std::endl;
                std::wcout << L"Notice: " << messageText << std::endl;
                i++;
            }

            // Thực thi truy vấn
            if (SQLExecDirectW(stmt, (SQLWCHAR*)query.c_str(), SQL_NTS) == SQL_SUCCESS) {
                popup.show("Save phone into database succesful!", sf::Color::Green);
                for (auto& field : fields) {
                    field.setText("");
                    field.setContent("");
                    field.setSelected(false);
                }
            }
            else {
                popup.show("Error! Can't save into database!", sf::Color::Red);
                for (auto& field : fields) {
                    field.setText("");
                    field.setContent("");
                    field.setSelected(false);
                }
            }

            SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        }
    } catch (const std::invalid_argument&) {
        popup.show("Invalid number format!", sf::Color::Red);
        return;
    } catch (const std::out_of_range&) {
        popup.show("Number out of range!", sf::Color::Red);
        return;
    }
}