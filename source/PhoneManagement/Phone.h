#ifndef _PHONE_H_
#define _PHONE_H_

// ===============================
// Includes & Dependencies
// ===============================

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <algorithm>
#include <exception>
#include <sstream>
#include <stdexcept>
#include <thread>
#include <windows.h>
#include <sqlext.h> // SQL Server ODBC header

#include <locale>
#include <codecvt>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// ===============================
// Standard Namespace
// ===============================

using std::cin;
using std::cout;
using std::endl;
using std::string, std::wstring_convert, std::wstring;
using std::vector;
using std::ostream;
using std::out_of_range;
using std::forward_iterator_tag;

// ===============================
// Utility Function
// ===============================

// Round a float value to a fixed number of decimal places
float round_to_decimal(float var, int decimal_places);

// ===============================
// ConfigPhone Struct
// -------------------------------
// Represents hardware specs of a phone
// ===============================
struct ConfigPhone {
    string operatingSystem;   // OS name (e.g., Android, iOS)
    string cpu;               // CPU chip
    int ram;                  // RAM in GB
    int rom;                  // Internal storage in GB
    float screenSize;         // Display size in inches
    int pin;                  // Battery capacity in mAh
};

// ===============================
// Phone Class
// -------------------------------
// Encapsulates all phone attributes, DB operations, and comparisons
// ===============================
class Phone {
private:
    int _id;                  // Unique ID
    string _name;             // Phone name
    string _manufacturer;     // Manufacturer
    ConfigPhone _config;      // Hardware configuration
    string _price;            // Price (e.g. "15.5") as string for flexibility

public:
    // Constructors and destructor
    Phone();
    Phone(const Phone&);
    Phone(const int, const string, const string, const ConfigPhone, const string);
    ~Phone();

    // ---------- Getters ----------
    int getID() const;
    string getName() const;
    string getManu() const;
    ConfigPhone getConfig() const;
    string getPrice() const;

    // ---------- Setters ----------
    void setID(int id);
    void setName(string name);
    void setManu(string manufacturer);
    void setConfig(string operatingSys, string cpu, int ram, int rom, float screenSize, int pin);
    void setConfig(ConfigPhone config);
    void setPrice(string price);

    // ---------- User / DB I/O ----------
    void insertValue();               // Input from console (manual mode)
    void insertToDB(SQLHDBC db);      // Insert to database using ODBC connection

    // ---------- Operators ----------
    friend ostream& operator<<(ostream& os, const Phone);  // Stream output
    bool operator==(const Phone);      // Compare phones by attributes
    bool operator!=(const Phone);      // Inverse of operator==
};

// ===============================
// Utility Functions
// ===============================

// Format the price input string
string priceStandardize(const string& price);

// Prompt for integer input with validation
int inputIntegerNumber(const string& notice);

#endif
