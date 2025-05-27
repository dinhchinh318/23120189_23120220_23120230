#include "addScreen_utils.h"
#include <algorithm>
#include <sstream>

bool isValidInteger(const std::string& str) {
    if (str.empty()) return false;
    return std::all_of(str.begin(), str.end(), ::isdigit);
}

bool isValidFloat(const std::string& str) {
    std::istringstream iss(str);
    float f;
    return (iss >> f) && iss.eof();
}

bool validatePhoneFields(const std::vector<std::string>& fields, std::string& errorMsg) {
    if (fields.size() < 10) {
        errorMsg = "Not enough fields!";
        return false;
    }
    for (const auto& f : fields) {
        if (f.empty()) {
            errorMsg = "Please fill in all fields!";
            return false;
        }
    }
    if (!isValidInteger(fields[0])) {
        errorMsg = "ID must be a valid number!";
        return false;
    }
    if (!isValidInteger(fields[6]) || !isValidInteger(fields[7]) || !isValidFloat(fields[8]) || !isValidInteger(fields[9])) {
        errorMsg = "RAM, ROM, Pin must be integer. Screen must be float!";
        return false;
    }
    return true;
}

bool addPhoneToDB(SQLHDBC db, const std::vector<std::string>& fields, std::string& errorMsg) {
    if (!validatePhoneFields(fields, errorMsg)) {
        return false;
    }

    std::wstring query = L"INSERT INTO PHONE(ID, NamePhone, Manufacturer, Price, OperatingSystem, CPU, RAM, ROM, ScreenSize, Pin) VALUES ("
        + std::to_wstring(std::stoi(fields[0])) + L", N'"
        + std::wstring(fields[1].begin(), fields[1].end()) + L"', N'"
        + std::wstring(fields[2].begin(), fields[2].end()) + L"', N'"
        + std::wstring(fields[3].begin(), fields[3].end()) + L"', N'"
        + std::wstring(fields[4].begin(), fields[4].end()) + L"', N'"
        + std::wstring(fields[5].begin(), fields[5].end()) + L"', "
        + std::to_wstring(std::stoi(fields[6])) + L", "
        + std::to_wstring(std::stoi(fields[7])) + L", "
        + std::wstring(fields[8].begin(), fields[8].end()) + L", "
        + std::to_wstring(std::stoi(fields[9])) + L")";

    SQLHSTMT stmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db, &stmt);
    SQLRETURN ret = SQLExecDirectW(stmt, (SQLWCHAR*)query.c_str(), SQL_NTS);
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        errorMsg.clear();
        return true;
    } else {
        errorMsg = "Add failed! ID may be existed or invalid data.";
        return false;
    }
}