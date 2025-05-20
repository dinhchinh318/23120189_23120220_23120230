#include "DeleteScreen.h"

DeleteScreen::DeleteScreen(sf::Font& font, UITheme theme) : BaseScreen(font, theme),
        deleteButton("DELETE", sf::Vector2f(1500 / 2.0f - 160.0f, 800 - 100.0f), sf::Vector2f(320, 50), font, theme),
        findButton("FIND", sf::Vector2f(1500 - 400.0f, 800 / 2.0f), sf::Vector2f(320, 50), font, theme),
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

bool DeleteScreen::validateFields() 
{
    if (fields[0].getText().empty()) 
    {
        popup.show("Please input ID! ID is not exists!", sf::Color::Red);
        
        return false;
    }
    return true;
}

void DeleteScreen::draw(sf::RenderWindow& window, sf::Font& font) 
{
    sf::Text t("DELETE PHONE", font, 28);
    t.setFillColor(sf::Color::Red);

    sf::FloatRect textRect = t.getLocalBounds();
    t.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    t.setPosition(1500 / 2.0f, 800 / 7.0f);
    window.draw(t);
    drawBackButton(window);
    deleteButton.draw(window);
    findButton.draw(window);

    mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
    for (auto& field : fields) field.draw(window);

    popup.draw(window);
}

void DeleteScreen::update(sf::Vector2f mousePos) 
{
    deleteButton.update(mousePos);
    findButton.update(mousePos);
    popup.update();
}

void DeleteScreen::handleFindButton(SQLHDBC db)
{
    if (!validateFields()) return;

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

        // ID
        if (!fields[0].getText().empty()) {
            int id = std::stoi(fields[0].getText());
            appendCondition(L"ID = " + std::to_wstring(id));
        }

        // NAMEPHONE
        if (!fields[1].getText().empty()) {
            std::wstring name = stringToWString(fields[1].getText());
            appendCondition(L"NAMEPHONE = N'" + name + L"'");
        }

        // MANUFACTURER
        if (!fields[2].getText().empty()) {
            std::wstring manu = stringToWString(fields[2].getText());
            appendCondition(L"MANUFACTURER = N'" + manu + L"'");
        }

        // PRICE
        if (!fields[3].getText().empty()) {
            float price = std::stoi(fields[3].getText());
            appendCondition(L"PRICE = " + std::to_wstring(price));
        }

        // OPERATINGSYSTEM
        if (!fields[4].getText().empty()) {
            std::wstring os = stringToWString(fields[4].getText());
            appendCondition(L"OPERATINGSYSTEM = N'" + os + L"'");
        }

        // CPU
        if (!fields[5].getText().empty()) {
            std::wstring cpu = stringToWString(fields[5].getText());
            appendCondition(L"CPU = N'" + cpu + L"'");
        }

        // RAM
        if (!fields[6].getText().empty()) {
            int ram = std::stoi(fields[6].getText());
            appendCondition(L"RAM = " + std::to_wstring(ram));
        }

        // ROM
        if (!fields[7].getText().empty()) {
            int rom = std::stoi(fields[7].getText());
            appendCondition(L"ROM = " + std::to_wstring(rom));
        }

        // SCREENSIZE
        if (!fields[8].getText().empty()) {
            float screenSize = std::stof(fields[8].getText());
            appendCondition(L"SCREENSIZE = " + std::to_wstring(screenSize));
        }

        // PIN
        if (!fields[9].getText().empty()) {
            int pin = std::stoi(fields[9].getText());
            appendCondition(L"PIN = " + std::to_wstring(pin));
        }

        if (!hasCondition) {
            popup.show("Please enter at least one field.", sf::Color::Red);
            SQLFreeHandle(SQL_HANDLE_STMT, stmt);
            return;
        }

        std::wstring query = L"SELECT * FROM PHONE WHERE " + whereClause;

        SQLRETURN ret = SQLExecDirectW(stmt, (SQLWCHAR*)query.c_str(), SQL_NTS);
        if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
            if (SQLFetch(stmt) == SQL_SUCCESS) {
                popup.show("Found successfully!", sf::Color::Green);
            } else {
                popup.show("Not found!", sf::Color::Red);
            }
        } else {
            popup.show("Query failed!", sf::Color::Red);
        }

        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    } 
    catch (const std::invalid_argument&) {
        popup.show("Invalid number format!", sf::Color::Red);
    } 
    catch (const std::out_of_range&) {
        popup.show("Number out of range!", sf::Color::Red);
    }
}


void DeleteScreen::pollEvent(sf::RenderWindow& window, sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed) {
        for (auto& field : fields) {
            field.setSelected(field.contains(mousePos));
        }

        if (deleteButton.isClicked(mousePos))
        {
            if (!validateFields()) return;
            deletePhone(hDbc, std::stoi(fields[0].getText()));
        }

        if (findButton.isClicked(mousePos))
        {
            handleFindButton(hDbc);
        }

        if (backButton.isClicked(mousePos))
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

void DeleteScreen::deletePhone(SQLHDBC db, const int& id) 
{
    if (!validateFields()) return;

    try 
    {
        SQLHSTMT stmt;
        SQLAllocHandle(SQL_HANDLE_STMT, db, &stmt);

        std::wstring query = L"DELETE FROM PHONE WHERE ID = " + std::to_wstring(id);

        SQLRETURN ret = SQLExecDirectW(stmt, (SQLWCHAR*)query.c_str(), SQL_NTS);

        if (ret == SQL_SUCCESS)
        {
            popup.show("Delete phone by ID succesful!", sf::Color::Green);
            for (auto& field : fields) {
                field.setText("");
                field.setContent("");
                field.setSelected(false);
            }
        }
        else 
        {
            for (auto& field : fields) {
                field.setText("");
                field.setContent("");
                field.setSelected(false);
            }
            popup.show("Can't delete Phone with ID. Please check again", sf::Color::Red);
        }

        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    } catch (const std::invalid_argument&) {
        popup.show("Invalid number format!", sf::Color::Red);
        return;
    } catch (const std::out_of_range&) {
        popup.show("Number out of range!", sf::Color::Red);
        return;
    }
    
}