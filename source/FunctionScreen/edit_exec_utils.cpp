#include "edit_exec_utils.h"
#include <algorithm>

bool validateEditFields(const std::vector<std::string>& fields, std::string& errorMsg) {
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
    if (!std::all_of(fields[0].begin(), fields[0].end(), ::isdigit)) {
        errorMsg = "ID must be a valid number!";
        return false;
    }
    // Có thể kiểm tra thêm các trường số khác nếu muốn
    return true;
}

bool updatePhoneInDB(SQLHDBC db, int id, const std::vector<std::string>& fields, std::string& errorMsg) {
    std::wstring query = L"UPDATE PHONE SET "
        L"NamePhone = N'" + std::wstring(fields[1].begin(), fields[1].end()) + L"', "
        L"Manufacturer = N'" + std::wstring(fields[2].begin(), fields[2].end()) + L"', "
        L"Price = N'" + std::wstring(fields[3].begin(), fields[3].end()) + L"', "
        L"OperatingSystem = N'" + std::wstring(fields[4].begin(), fields[4].end()) + L"', "
        L"CPU = N'" + std::wstring(fields[5].begin(), fields[5].end()) + L"', "
        L"RAM = " + std::wstring(fields[6].begin(), fields[6].end()) + L", "
        L"ROM = " + std::wstring(fields[7].begin(), fields[7].end()) + L", "
        L"ScreenSize = " + std::wstring(fields[8].begin(), fields[8].end()) + L", "
        L"Pin = " + std::wstring(fields[9].begin(), fields[9].end()) +
        L" WHERE ID = " + std::to_wstring(id);

    SQLHSTMT stmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db, &stmt);
    SQLRETURN ret = SQLExecDirectW(stmt, (SQLWCHAR*)query.c_str(), SQL_NTS);
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        return true;
    } else {
        errorMsg = "Update failed!";
        return false;
    }
}