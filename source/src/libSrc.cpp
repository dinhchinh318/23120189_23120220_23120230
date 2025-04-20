#include "../include/libSrc.h"

string ChuanHoaGia(string& gia) {
    // Bước 1: Lọc chỉ lấy chữ số
    string digits;
    for (char c : gia) {
        if (isdigit(c)) {
            digits += c;
        }
    }

    // Bước 2: Thêm dấu chấm ngăn cách hàng nghìn
    string result;
    int count = 0;

    for (int i = digits.length() - 1; i >= 0; i--) {
        result.push_back(digits[i]);
        count++;
        if (count % 3 == 0 && i != 0) {
            result.push_back('.');
        }
    }

    // Đảo ngược lại chuỗi để có định dạng đúng
    reverse(result.begin(), result.end());

    return result;
}