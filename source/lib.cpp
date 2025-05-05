#include "lib.h"

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
// Hàm nhập số nguyên từ bàn phím với thông báo
int nhapSoNguyen(const std::string& thongBao) {
    int so;
    while (true) {
        std::cout << thongBao;
        std::cin >> so;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "❌ Loi: Vui long nhap so nguyen hop le!\n";
        }
        else {
            std::cin.ignore(1000, '\n');
            return so;
        }
    }
}


// Hàm kết nối đến database
bool connectToSQL(SQLHENV& hEnv, SQLHDBC& hDbc) {
    SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
    SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
    SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);

    std::wstring connStr = L"Driver={ODBC Driver 17 for SQL Server};Server=localhost;Database=QLDienThoai;UID=sa;PWD=123;";
    SQLRETURN ret = SQLDriverConnectW(hDbc, nullptr, (SQLWCHAR*)connStr.c_str(), SQL_NTS, nullptr, 0, nullptr, SQL_DRIVER_COMPLETE);

    //SQLWCHAR connStr[] = L"Driver={ODBC Driver 17 for SQL Server};Server=localhost;Database=QLDienThoai;UID=sa;PWD=123;";
    //SQLRETURN ret = SQLDriverConnectW(hDbc, NULL, connStr, SQL_NTS, NULL, 0, NULL, SQL_DRIVER_COMPLETE);

    if (SQL_SUCCEEDED(ret)) {
        std::wcout << L"Ket noi SQL Server thanh cong.\n";
        return true;
    }
    else {
        std::wcout << L"Ket noi that bai.\n";
        return false;
    }
} 