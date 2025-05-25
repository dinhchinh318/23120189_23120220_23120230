#include "edit-exec.h"

EditExecute::EditExecute(sf::Font& font, UITheme theme)
    : BaseScreen(font, theme),
      saveButton("SAVE", sf::Vector2f(1500 / 2.0f - 160.0f, 800 - 100.0f), sf::Vector2f(320, 50), font, theme),
      popup(1500, 800)
{
    float startX = 280, startY = 180, width = 600, height = 40, gap = 50;
    std::vector<std::string> labels = { "ID", "Name", "Manufacturer", "Price", "Operating System", "CPU", "RAM", "ROM", "Screen", "Pin" };

    for (int i = 0; i < labels.size(); ++i)
        fields.emplace_back(font, sf::Vector2f(startX, startY + i * gap), sf::Vector2f(width, height));

    for (size_t i = 0; i < fields.size(); ++i)
        fields[i].setlabel(labels[i]);

    if (!connectToSQL(hEnv, hDbc)) 
    {
        return;
    }
}

void EditExecute::setPhoneToEdit(const Phone& phone)
{
    editingPhone = phone;

    auto setField = [&](int index, const std::string& value) {
        fields[index].setText(value);
        fields[index].setContent(value);
    };

    setField(0, std::to_string(phone.getID()));
    setField(1, phone.getName());
    setField(2, phone.getManu());
    setField(3, phone.getPrice());
    setField(4, phone.getConfig().operatingSystem);
    setField(5, phone.getConfig().cpu);
    setField(6, std::to_string(phone.getConfig().ram));
    setField(7, std::to_string(phone.getConfig().rom));
    setField(8, std::to_string(phone.getConfig().screenSize));
    setField(9, std::to_string(phone.getConfig().pin));
}

void EditExecute::draw(sf::RenderWindow& window, sf::Font& font, AppScreen& screen)
{
    mousePos = sf::Vector2f(sf::Mouse::getPosition(window));

    drawDefaultScreen(window, screen, font);
    drawBack(window);
    for (auto& field : fields) field.draw(window);
    saveButton.draw(window);
    popup.draw(window);
}

void EditExecute::pollEvent(sf::RenderWindow& window, sf::Event& event, AppScreen& screen)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        for (auto& field : fields) {
            field.setSelected(field.contains(mousePos));
        }

        if (saveButton.isClicked(mousePos))
        {
            updatePhoneInDatabase(hDbc, screen);
        }

        if (buttons[0].isClicked(mousePos) ||
            buttons[1].isClicked(mousePos) ||
            buttons[2].isClicked(mousePos) ||
            buttons[3].isClicked(mousePos) ||
            buttons[4].isClicked(mousePos))
        {
            resetAllFields();
        }

        if (backButton.isClicked(mousePos))
        {
            screen = AppScreen::EDIT_LIST;
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

void EditExecute::updatePhoneInDatabase(SQLHDBC db, AppScreen& screen)
{
    try {
        std::string idStr = fields[0].getText();

        if (idStr.empty() || !std::all_of(idStr.begin(), idStr.end(), ::isdigit)) {
            popup.show("Invalid ID!", sf::Color::Red);
            return;
        }

        int id = std::stoi(idStr);

        std::wstring query = L"UPDATE PHONE SET ";
        bool hasField = false;

        auto appendFieldIfChanged = [&](const std::wstring& column, const std::string& newValue, const std::string& oldValue, bool isText) {
            if (newValue != oldValue) {
                if (hasField) query += L", ";
                query += column + L" = ";
                if (isText)
                    query += L"N'" + std::wstring(newValue.begin(), newValue.end()) + L"'";
                else
                    query += std::wstring(newValue.begin(), newValue.end());
                hasField = true;
            }
        };

        Phone& p = editingPhone;
        const ConfigPhone& cfg = p.getConfig();

        appendFieldIfChanged(L"NamePhone", fields[1].getText(), p.getName(), true);
        appendFieldIfChanged(L"Manufacturer", fields[2].getText(), p.getManu(), true);
        appendFieldIfChanged(L"Price", fields[3].getText(), p.getPrice(), false);
        appendFieldIfChanged(L"OperatingSystem", fields[4].getText(), cfg.operatingSystem, true);
        appendFieldIfChanged(L"CPU", fields[5].getText(), cfg.cpu, true);
        appendFieldIfChanged(L"RAM", fields[6].getText(), std::to_string(cfg.ram), false);
        appendFieldIfChanged(L"ROM", fields[7].getText(), std::to_string(cfg.rom), false);
        appendFieldIfChanged(L"ScreenSize", fields[8].getText(), std::to_string(cfg.screenSize), false);
        appendFieldIfChanged(L"Pin", fields[9].getText(), std::to_string(cfg.pin), false);

        if (!hasField) {
            popup.show("No changes detected!", sf::Color::Yellow);
            return;
        }

        query += L" WHERE ID = " + std::to_wstring(id);

        SQLHSTMT stmt;
        SQLAllocHandle(SQL_HANDLE_STMT, db, &stmt);
        SQLRETURN ret = SQLExecDirectW(stmt, (SQLWCHAR*)query.c_str(), SQL_NTS);

        if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
            popup.show("Update successful!", sf::Color::Green);
        } else {
            SQLWCHAR sqlState[6];
            SQLINTEGER nativeError;
            SQLWCHAR messageText[256];
            SQLSMALLINT textLength;

            SQLGetDiagRecW(SQL_HANDLE_STMT, stmt, 1, sqlState, &nativeError, messageText,
                           sizeof(messageText) / sizeof(SQLWCHAR), &textLength);

            std::wcout << L"[ERROR] SQLSTATE: " << sqlState << L"\n";
            std::wcout << L"Code: " << nativeError << L"\n";
            std::wcout << L"Message: " << messageText << L"\n";

            popup.show("Update failed!", sf::Color::Red);
        }

        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    }
    catch (const std::exception& e) {
        popup.show("Exception: " + std::string(e.what()), sf::Color::Red);
    }

    
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    resetAllFields();
    screen = AppScreen::EDIT_LIST;
}



