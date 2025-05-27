#ifndef _ADDSCREEN_UTILS_H_
#define _ADDSCREEN_UTILS_H_
#include <windows.h>
#include <sqlext.h>
#include <string>
#include <vector>
#include "delScreen_utils.h"

bool isValidInteger(const std::string& str);
bool isValidFloat(const std::string& str);
bool validatePhoneFields(const std::vector<std::string>& fields, std::string& errorMsg);
bool addPhoneToDB(SQLHDBC db, const std::vector<std::string>& fields, std::string& errorMsg);



#endif