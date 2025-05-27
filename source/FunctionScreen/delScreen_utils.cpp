#include "delScreen_utils.h"

bool isValidDeleteID(const std::string& id) {
    if (id.empty()) return false;
    for (char c : id) if (!isdigit(c)) return false;
    return true;
}

bool validateDeleteFields(const std::string& id, std::string& errorMsg) {
    if (id.empty()) {
        errorMsg = "Please enter ID!";
        return false;
    }
    if (!isValidDeleteID(id)) {
        errorMsg = "ID must be a number!";
        return false;
    }
    return true;
}

bool deletePhoneFromDB(SQLHDBC db, int id) {
    std::wstring query = L"DELETE FROM PHONE WHERE ID = " + std::to_wstring(id);
    SQLHSTMT stmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db, &stmt);
    SQLRETURN ret = SQLExecDirectW(stmt, (SQLWCHAR*)query.c_str(), SQL_NTS);
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    return (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO);
}

bool connectToSQLTest(SQLHENV& hEnv, SQLHDBC& hDbc) {
    SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
    SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
    SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);
    
    SQLRETURN ret = SQLDriverConnectA(hDbc, NULL, connStr, SQL_NTS, NULL, 0, NULL, SQL_DRIVER_COMPLETE);
    return (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO);
}

bool handleFindButton(SQLHDBC db, const std::string& id, std::wstring& message) {
    if (id.empty()) {
        message = L"Please input ID!";
        return false;
    }
    int intID = 0;
    try {
        intID = std::stoi(id);
    } catch (...) {
        message = L"ID must be a number!";
        return false;
    }

    std::wstring query = L"SELECT * FROM PHONE WHERE ID = " + std::to_wstring(intID);
    SQLHSTMT stmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db, &stmt);

    SQLRETURN ret = SQLExecDirectW(stmt, (SQLWCHAR*)query.c_str(), SQL_NTS);
    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        if (SQLFetch(stmt) == SQL_SUCCESS) {
            message = L"Found successfully!";
            SQLFreeHandle(SQL_HANDLE_STMT, stmt);
            return true;
        } else {
            message = L"Not found!";
            SQLFreeHandle(SQL_HANDLE_STMT, stmt);
            return false;
        }
    } else {
        message = L"Query failed!";
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        return false;
    }
}