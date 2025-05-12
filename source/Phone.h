#ifndef _PHONE_H_
#define _PHONE_H_

#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <cstdlib>
#include <stdlib.h>
#include <thread>
#include <algorithm>
#include <exception>
#include <stdexcept>
#include <windows.h>
#include <sqlext.h>// SQL Server ODBC header

// #include <SFML/Graphics/RenderWindow.hpp>
// #include <SFML/Graphics/Shape.hpp>
// #include <SFML/Graphics/RectangleShape.hpp>
// #include <SFML/Graphics/Texture.hpp>
// #include <SFML/Graphics/Text.hpp>
// #include <SFML/Graphics/Color.hpp>
// #include <SFML/System/Vector2.hpp>
// #include <SFML/Window/Event.hpp>
// #include <SFML/Graphics.hpp>
// #include <SFML/Audio.hpp>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ostream;
using std::out_of_range;
using std::forward_iterator_tag;

struct ConfigPhone
{
    string operatingSystem;         // Hệ điều hành
    string cpu;                     // Chip xử lý
    int ram;                        // Dung lượng RAM (GB)
    int rom;                        // Bộ nhớ trong (GB)
    float screenSize;               // Kích thước màn hình (inch)
    int pin;                        // Dung lượng pin (mAh)
};

class Phone {
private:
    int _id;                            // ID điện thoại
    string _name;                       // Tên điện thoại
    string _manufacturer;               // Hãng sản xuất
    ConfigPhone _config;                // Cấu hình điện thoại
    string _price;                      // Giá tiền (triệu VND)
public:
    Phone();
    Phone(const Phone&);
    Phone(const int, const string, const string, const ConfigPhone, const string);
    ~Phone();

    ///// --- Getter ---
    int getID() const
    {
        return _id;
    }

    string getName() const
    {
        return _name;
    }

    string getManu() const
    {
        return _manufacturer;
    }

    ConfigPhone getConfig() const
    {
        return _config;
    }

    string getPrice() const
    {
        return _price;
    }

    void setID(int id)
    {
        _id = id;
    }
    void setName(string name)
    {
        _name = name;
    }
    void setManu(string manufacturer)
    {
        _manufacturer = manufacturer;
    }
    void setConfig(string operatingSys, string cpu, int ram, int rom, float screenSize, int pin) {
        _config.operatingSystem = operatingSys;
        _config.cpu = cpu;
        _config.ram = ram;
        _config.rom = rom;
        _config.screenSize = screenSize;
        _config.pin = pin;

    }
    void setConfig(ConfigPhone config)
    {
        _config = config;

    }
    void setPrice(string price)
    {
        _price = price;
    }

    void insertValue();
    void insertToDB(SQLHDBC db); // db là kết nối đến SQL Server

    friend ostream& operator<<(ostream& os, const Phone);

    bool operator==(const Phone);
    bool operator!=(const Phone);
};

string priceStandardize(const string& price);
int inputIntegerNumber(const string& notice);
bool connectToSQL(SQLHENV& hEnv, SQLHDBC& hDbc);

#endif