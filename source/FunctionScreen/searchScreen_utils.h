#ifndef _SEARCHSCREEN_UTILS_H_
#define _SEARCHSCREEN_UTILS_H_
#include <windows.h>
#include <sqlext.h>
#include <string>
#include <vector>

// Hàm kiểm tra chuỗi là số nguyên
bool isValidInteger(const std::string& str);

// Hàm kiểm tra chuỗi là số thực
bool isValidFloat(const std::string& str);

// Hàm kiểm tra dữ liệu đầu vào cho tìm kiếm
bool validateSearchFields(const std::vector<std::string>& fields, std::string& errorMsg);

// Hàm tìm kiếm chuỗi trong vector, trả về true nếu tìm thấy
bool searchInVector(const std::vector<std::string>& data, const std::string& keyword);

// Hàm tìm kiếm trong database, trả về true nếu tìm thấy
bool searchPhoneInDB(SQLHDBC db, const std::vector<std::string>& fields, std::vector<std::vector<std::string>>& results, std::string& errorMsg);

#endif