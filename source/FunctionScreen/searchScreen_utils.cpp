#include "searchScreen_utils.h"
#include "addScreen_utils.h" // Thêm dòng này để dùng lại hàm
#include <algorithm>
#include <sstream>

bool validateSearchFields(const std::vector<std::string>& fields, std::string& errorMsg) {
    if (fields.empty()) {
        errorMsg = "No search fields provided!";
        return false;
    }
    for (const auto& f : fields) {
        if (f.empty()) {
            errorMsg = "Please fill in all search fields!";
            return false;
        }
    }
    errorMsg.clear();
    return true;
}

bool searchInVector(const std::vector<std::string>& data, const std::string& keyword) {
    for (const auto& item : data) {
        if (item.find(keyword) != std::string::npos) {
            return true; // Found substring
        }
    }
    return false; // Substring not found
}

// Example function, adjust according to your actual database structure
bool searchPhoneInDB(SQLHDBC db, const std::vector<std::string>& fields, std::vector<std::vector<std::string>>& results, std::string& errorMsg) {
    if (fields.empty()) {
        errorMsg = "No search fields provided!";
        return false;
    }
    std::wstring whereClause = L"";
    bool hasCondition = false;

    auto appendCondition = [&](const std::wstring& cond) {
        if (hasCondition) whereClause += L" AND ";
        whereClause += cond;
        hasCondition = true;
    };

    if (fields.size() > 0 && !fields[0].empty() && isValidInteger(fields[0])) {
        appendCondition(L"ID = " + std::to_wstring(std::stoi(fields[0])));
    }
    if (fields.size() > 1 && !fields[1].empty()) {
        appendCondition(L"NAMEPHONE LIKE N'%" + std::wstring(fields[1].begin(), fields[1].end()) + L"%'");
    }
    if (fields.size() > 2 && !fields[2].empty()) {
        appendCondition(L"MANUFACTURER LIKE N'%" + std::wstring(fields[2].begin(), fields[2].end()) + L"%'");
    }
    if (fields.size() > 3 && !fields[3].empty()) {
        appendCondition(L"PRICE = '" + std::wstring(fields[3].begin(), fields[3].end()) + L"'");
    }
    if (fields.size() > 4 && !fields[4].empty()) {
        appendCondition(L"OPERATINGSYSTEM LIKE N'%" + std::wstring(fields[4].begin(), fields[4].end()) + L"%'");
    }
    if (fields.size() > 5 && !fields[5].empty()) {
        appendCondition(L"CPU LIKE N'%" + std::wstring(fields[5].begin(), fields[5].end()) + L"%'");
    }
    if (fields.size() > 6 && !fields[6].empty() && isValidInteger(fields[6])) {
        appendCondition(L"RAM = " + std::to_wstring(std::stoi(fields[6])));
    }
    if (fields.size() > 7 && !fields[7].empty() && isValidInteger(fields[7])) {
        appendCondition(L"ROM = " + std::to_wstring(std::stoi(fields[7])));
    }
    if (fields.size() > 8 && !fields[8].empty() && isValidFloat(fields[8])) {
        appendCondition(L"SCREENSIZE = " + std::to_wstring(std::stof(fields[8])));
    }
    if (fields.size() > 9 && !fields[9].empty() && isValidInteger(fields[9])) {
        appendCondition(L"PIN = " + std::to_wstring(std::stoi(fields[9])));
    }

    if (!hasCondition) {
        errorMsg = "Please fill in at least one field!";
        return false;
    }

    std::wstring query = L"SELECT * FROM PHONE WHERE " + whereClause;
    SQLHSTMT stmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db, &stmt);
    SQLRETURN ret = SQLExecDirectW(stmt, (SQLWCHAR*)query.c_str(), SQL_NTS);

    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        SQLCHAR buffer[256];
        while (SQLFetch(stmt) == SQL_SUCCESS) {
            std::vector<std::string> row;
            for (int i = 1; i <= 10; ++i) {
                SQLGetData(stmt, i, SQL_C_CHAR, buffer, sizeof(buffer), NULL);
                row.push_back(reinterpret_cast<char*>(buffer));
            }
            results.push_back(row);
        }
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        errorMsg.clear();
        return !results.empty();
    } else {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        errorMsg = "No result found or query error!";
        return false;
    }
}

