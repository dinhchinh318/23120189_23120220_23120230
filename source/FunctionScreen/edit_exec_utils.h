#ifndef EDIT_EXEC_UTILS_H
#define EDIT_EXEC_UTILS_H
#include <windows.h>
#include <string>
#include <vector>
#include <sqlext.h>

bool validateEditFields(const std::vector<std::string>& fields, std::string& errorMsg);
bool updatePhoneInDB(SQLHDBC db, int id, const std::vector<std::string>& fields, std::string& errorMsg);


#endif