#ifndef DELSCREEN_UTILS_H
#define DELSCREEN_UTILS_H
#include <windows.h>
#include <string>
#include <sqlext.h>

extern SQLCHAR connStr[];

bool isValidDeleteID(const std::string& id);
bool validateDeleteFields(const std::string& id, std::string& errorMsg);
bool deletePhoneFromDB(SQLHDBC db, int id);
bool handleFindButton(SQLHDBC db, const std::string& id, std::wstring& message);
bool connectToSQLTest(SQLHENV& hEnv, SQLHDBC& hDbc);

#endif
