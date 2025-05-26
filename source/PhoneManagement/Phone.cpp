#include "Phone.h"

// Round a float value to a specific number of decimal places
float round_to_decimal(float var, int decimal_places) {
    float factor = pow(10.0f, decimal_places);
    return round(var * factor) / factor;
}

// Getters
int Phone::getID() const { return _id; }
string Phone::getName() const { return _name; }
string Phone::getManu() const { return _manufacturer; }
ConfigPhone Phone::getConfig() const { return _config; }
string Phone::getPrice() const { return _price; }

// Setters
void Phone::setID(int id) { _id = id; }
void Phone::setName(string name) { _name = name; }
void Phone::setManu(string manu) { _manufacturer = manu; }
void Phone::setPrice(string price) { _price = price; }

void Phone::setConfig(string operatingSys, string cpu, int ram, int rom, float screenSize, int pin) {
    _config.operatingSystem = operatingSys;
    _config.cpu = cpu;
    _config.ram = ram;
    _config.rom = rom;
    _config.screenSize = round_to_decimal(screenSize, 2);
    _config.pin = pin;
}

// Remove non-digit characters and format price with dot separators
string priceStandardize(const string& price) {
    string digits;
    for (char c : price) {
        if (isdigit(c)) digits += c;
    }

    int len = digits.length();
    if (len == 0) return "0";

    string result;
    int mod = len % 3;
    if (mod > 0) result = digits.substr(0, mod);

    for (int i = mod; i < len; i += 3) {
        if (!result.empty()) result += ".";
        result += digits.substr(i, 3);
    }

    return result;
}

// Input and validate an integer number from user
int inputIntegerNumber(const std::string& notice) {
    int number;
    while (true) {
        std::cout << notice;
        std::cin >> number;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Error: Please input correct value!\n";
        }
        else {
            std::cin.ignore(1000, '\n');
            return number;
        }
    }
}

// Manually input phone attributes from user
void Phone::insertValue() {
    int id = inputIntegerNumber("Please input Phone ID: ");
    _id = id;

    cout << "Please input Phone Name: ";
    getline(cin, _name);

    cout << "Please input Phone manufacturer: ";
    getline(cin, _manufacturer);

    cout << "Please input Phone operating system: ";
    getline(cin, _config.operatingSystem);

    cout << "Please input Phone CPU: ";
    getline(cin, _config.cpu);

    _config.ram = inputIntegerNumber("Input RAM (GB): ");
    _config.rom = inputIntegerNumber("Input ROM (GB): ");
    _config.pin = inputIntegerNumber("Input pin (mAh): ");
    _config.screenSize = inputIntegerNumber("Input screen size (inch): ");

    cout << "Input price (million VND): ";
    getline(cin, _price);
    _price = priceStandardize(_price);
}

// Overload ostream for ConfigPhone
ostream& operator<<(ostream& os, const ConfigPhone& config) {
    os  << "operatingSystem : " << config.operatingSystem << "\n"
        << "CPU             : " << config.cpu << "\n"
        << "RAM             : " << config.ram << " GB\n"
        << "ROM             : " << config.rom << " GB\n"
        << "Man hinh        : " << config.screenSize << " inch\n"
        << "Pin             : " << config.pin << " mAh";
    return os;
}

// Constructors
Phone::Phone()
    : _id(0), _name(""), _manufacturer(""), _config(), _price("0") {}

Phone::Phone(const Phone& p)
    : _id(p._id), _name(p._name), _manufacturer(p._manufacturer), _config(p._config), _price(p._price) {}

Phone::Phone(const int id, const string name, const string manu, const ConfigPhone config, string price)
    : _id(id), _name(name), _manufacturer(manu), _config(config), _price(priceStandardize(price)) {}

Phone::~Phone() {} // Destructor

// Overload ostream for Phone
ostream& operator<<(ostream& os, const Phone p) {
    os  << "ID              : " << p._id << "\n"
        << "Manufacturer    : " << p._manufacturer << "\n"
        << "NamePhone       : " << p._name << "\n"
        << p._config << "\n"
        << "Price           : " << p._price << " VND";
    return os;
}

// Compare phones by ID
bool Phone::operator==(const Phone p) {
    return _id == p.getID();
}

bool Phone::operator!=(const Phone p) {
    return _id != p.getID();
}

// Insert current phone into database (if ID doesn't exist)
void Phone::insertToDB(SQLHDBC db) {
    SQLHSTMT stmt;
    SQLRETURN ret;

    // Check for duplicate ID
    std::wstring checkQuery = L"SELECT COUNT(*) FROM PHONE WHERE ID = " + std::to_wstring(_id);
    SQLAllocHandle(SQL_HANDLE_STMT, db, &stmt);
    ret = SQLExecDirectW(stmt, (SQLWCHAR*)checkQuery.c_str(), SQL_NTS);

    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        SQLINTEGER count;
        SQLBindCol(stmt, 1, SQL_C_SLONG, &count, 0, nullptr);
        if (SQLFetch(stmt) == SQL_SUCCESS && count > 0) {
            cout << "ID is exists.\n";
            SQLFreeHandle(SQL_HANDLE_STMT, stmt);
            return;
        }
    }
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    // Build SQL insert query
    SQLAllocHandle(SQL_HANDLE_STMT, db, &stmt);
    std::wstring query = L"INSERT INTO PHONE(ID, NamePhone, Manufacturer, Price, OperatingSystem, CPU, RAM, ROM, ScreenSize, Pin) VALUES ("
        + std::to_wstring(_id) + L", N'" + std::wstring(_name.begin(), _name.end()) + L"', N'"
        + std::wstring(_manufacturer.begin(), _manufacturer.end()) + L"', "
        + std::to_wstring(std::stoi(_price)) + L", N'" + std::wstring(_config.operatingSystem.begin(), _config.operatingSystem.end()) + L"', N'"
        + std::wstring(_config.cpu.begin(), _config.cpu.end()) + L"', "
        + std::to_wstring(_config.ram) + L", "
        + std::to_wstring(_config.rom) + L", "
        + std::to_wstring(_config.screenSize) + L", "
        + std::to_wstring(_config.pin) + L")";

    ret = SQLExecDirectW(stmt, (SQLWCHAR*)query.c_str(), SQL_NTS);
    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        cout << "Save phone into database successful!\n";
    } else {
        cout << "Error! Can't save into database!\n";

        // Debug error info
        SQLWCHAR sqlState[6];
        SQLINTEGER nativeError;
        SQLWCHAR messageText[256];
        SQLSMALLINT textLength;

        int i = 1;
        while (SQLGetDiagRecW(SQL_HANDLE_STMT, stmt, i, sqlState, &nativeError, messageText, sizeof(messageText) / sizeof(SQLWCHAR), &textLength) == SQL_SUCCESS) {
            std::wcout << L"[Error " << i << L"] SQLSTATE: " << sqlState << std::endl;
            std::wcout << L"Error Code: " << nativeError << std::endl;
            std::wcout << L"Notice: " << messageText << std::endl;
            ++i;
        }

        // Attempt insert again
        if (SQLExecDirectW(stmt, (SQLWCHAR*)query.c_str(), SQL_NTS) == SQL_SUCCESS)
            std::cout << "Retry insert successful.\n";
        else
            std::cout << "Retry failed.\n";
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}
