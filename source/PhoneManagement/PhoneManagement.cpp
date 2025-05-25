#include "PhoneManagement.h"

PhoneManagement::PhoneManagement()
{
    _pHead = _pTail = nullptr;
    _numberOfPhones = 0;
}

PhoneManagement::~PhoneManagement()
{
    while (_pHead)
    {
        Node* tmp = _pHead;
        _pHead = _pHead->_pNext;
        delete tmp;
        _numberOfPhones--;
    }
}

void PhoneManagement::Push_back(const Phone& p)
{
    Node* node = new Node{ p, nullptr };
    if (!_pHead)
    {
        _pHead = _pTail = node;
    }
    else
    {
        _pTail->_pNext = node;
        _pTail = node;
    }
    _numberOfPhones++;
}

void PhoneManagement::RemoveHead()
{
    if (!_pHead) return;
    Node* tmp = _pHead;
    _pHead = _pHead->_pNext;
    delete tmp;
    if (!_pHead)
    {
        _pTail == nullptr;
    }
    _numberOfPhones--;
}

void PhoneManagement::RemoveTail()
{
    if (_pHead == nullptr)
        return;

    if (_pHead == _pTail)
    {
        Node* node = _pHead;
        _pHead = _pTail = nullptr;
        _numberOfPhones--;
        return;
    }

    Node* prev = _pHead;
    while (prev->_pNext != _pTail)
    {
        prev = prev->_pNext;
    }
    Node* node = _pTail;
    _pTail = prev;
    _pTail->_pNext = nullptr;
    _numberOfPhones--;
    return;
}

void PhoneManagement::Remove(const Phone& dt)
{
    if (!_pHead) return;
    if (_pHead->info == dt) RemoveHead();
    else if (_pTail->info == dt) RemoveTail();
    else
    {
        Node* tmp = _pHead;
        while (tmp->info != dt)
        {
            tmp = tmp->_pNext;
        }
        Node* del = tmp;
        tmp = tmp->_pNext;
        delete del;
    }
    _numberOfPhones--;
}

void PhoneManagement::Clear()
{
    while (_pHead)
    {
        Node* tmp = _pHead;
        _pHead = _pHead->_pNext;
        delete tmp;
        _numberOfPhones--;
    }
}

// DienThoai QuanLyDienThoai::TimKiemTheoID(const int& id)
// {
//     Node* tmp = _pHead;
//     while(tmp)
//     {
//         if(tmp->info.getID() == id) return tmp->info;
//         tmp = tmp->_pNext;
//     }
//     return DienThoai();
// }

// DienThoai QuanLyDienThoai::TimKiemTheoTen(const string& ten)
// {
//     Node* tmp = _pHead;
//     while(tmp)
//     {
//         if(tmp->info.getTen() == ten) return tmp->info;
//         tmp = tmp->_pNext;
//     }
//     return DienThoai();
// }

/* DienThoai QuanLyDienThoai::TimKiem(const string& key)
{
    // Kiểm tra xem key có phải là một dãy số hay không
    bool isNumber = !key.empty() && all_of(key.begin(), key.end(), ::isdigit);

    Node* tmp = _pHead;
    if(isNumber)
    {
        int id = stoi(key);
        while(tmp)
        {
            if(tmp->info.getID() == id) return tmp->info;
            tmp = tmp->_pNext;
        }
    }
    else
    {
        while(tmp)
        {
            if(tmp->info.getTen() == key) return tmp->info;
            tmp = tmp->_pNext;
        }
    }
    return DienThoai(); // Trả về đối tượng rỗng nếu không tìm thấyy
} */

 // Hàm chuyển đổi std::wstring (chuỗi wide) sang std::string (UTF-8)
 std::string wstringToString(const std::wstring& wstr) {
     if (wstr.empty()) return std::string();
     int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), (int)wstr.size(), nullptr, 0, nullptr, nullptr);
     std::string result(size_needed, 0);
     WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), (int)wstr.size(), &result[0], size_needed, nullptr, nullptr);
     return result;
 }

std::wstring stringToWString(const std::string& str) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.from_bytes(str);
}

//#include <boost/locale.hpp>

//std::string PhoneManagement::wstringToString(const std::wstring& wstr) {
//    return boost::locale::conv::utf_to_utf<char>(wstr);
//}


// Tìm điện thoại theo ID trong cơ sở dữ liệu và trả về con trỏ đối tượng DienThoai
Phone* PhoneManagement::findByID(SQLHDBC db, const int& id) {
    SQLHSTMT stmt;

    // Cấp phát handle cho câu lệnh SQL
    SQLAllocHandle(SQL_HANDLE_STMT, db, &stmt);

    // Tạo câu lệnh SQL bằng chuỗi wide (Unicode)
    std::wstring query = L"SELECT * FROM PHONE WHERE ID = " + std::to_wstring(id);

    // Thực thi câu lệnh truy vấn
    SQLRETURN ret = SQLExecDirectW(stmt, (SQLWCHAR*)query.c_str(), SQL_NTS);

    // Nếu thực thi thành công
    if (ret == SQL_SUCCESS) {
        // Nếu có bản ghi trả về
        if (SQLFetch(stmt) == SQL_SUCCESS) {
            // Cấp phát đối tượng điện thoại mới
            Phone* p = new Phone();

            // Khai báo biến để chứa dữ liệu truy vấn
            char idStr[20];
            wchar_t name[100], manu[50], price[50], operatingSys[50], cpu[50];
            int ram, rom, screenSize, pin;

            // Lấy dữ liệu từ từng cột (theo thứ tự cột trong bảng)
            SQLGetData(stmt, 1, SQL_C_CHAR, idStr, sizeof(idStr), NULL);                        // ID
            SQLGetData(stmt, 2, SQL_C_WCHAR, name, sizeof(name), NULL);                         // Tên
            SQLGetData(stmt, 3, SQL_C_WCHAR, manu, sizeof(manu), NULL);                         // Hãng
            SQLGetData(stmt, 4, SQL_C_WCHAR, price, sizeof(price), NULL);                       // Giá
            SQLGetData(stmt, 5, SQL_C_WCHAR, operatingSys, sizeof(operatingSys), NULL);         // Hệ điều hành
            SQLGetData(stmt, 6, SQL_C_WCHAR, cpu, sizeof(cpu), NULL);                           // CPU
            SQLGetData(stmt, 7, SQL_C_SLONG, &ram, 0, NULL);                                    // RAM
            SQLGetData(stmt, 8, SQL_C_SLONG, &rom, 0, NULL);                                    // ROM
            SQLGetData(stmt, 9, SQL_C_SLONG, &screenSize, 0, NULL);                             // Kích thước màn hình
            SQLGetData(stmt, 10, SQL_C_SLONG, &pin, 0, NULL);                                   // Dung lượng pin

            // Gán dữ liệu vào đối tượng điện thoại
            p->setID(std::stoi(idStr));
            p->setName(wstringToString(name));
            p->setManu(wstringToString(manu));
            p->setPrice(wstringToString(price));
            p->setConfig(
                wstringToString(operatingSys),
                wstringToString(cpu),
                ram,
                rom,
                static_cast<float>(screenSize), // ép kiểu vì kích thước là float
                pin
            );

            // Giải phóng handle truy vấn
            SQLFreeHandle(SQL_HANDLE_STMT, stmt);

            // Trả về đối tượng kết quả
            return p;
        }
    }

    // Nếu không tìm thấy hoặc lỗi, giải phóng và trả về nullptr
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    return nullptr;
}

Phone* PhoneManagement::findByName(SQLHDBC db, const std::string& name) {
    SQLHSTMT stmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db, &stmt);

    // Chuyển chuỗi tên từ std::string sang std::wstring để truy vấn SQL Unicode
    std::wstring tenWStr(name.begin(), name.end());

    // Câu lệnh SQL tìm kiếm theo tên (dùng N trước chuỗi để hỗ trợ Unicode)
    std::wstring query = L"SELECT * FROM PHONE WHERE NamePhone = N'" + tenWStr + L"'";
    SQLRETURN ret = SQLExecDirectW(stmt, (SQLWCHAR*)query.c_str(), SQL_NTS);

    if (ret == SQL_SUCCESS) {
        if (SQLFetch(stmt) == SQL_SUCCESS) {
            Phone* p = new Phone();

            // Khai báo biến để chứa dữ liệu truy vấn
            char idStr[20];
            wchar_t name[100], manu[50], price[50], operatingSys[50], cpu[50];
            int ram, rom, screenSize, pin;

            // Lấy dữ liệu từ từng cột (theo thứ tự cột trong bảng)
            SQLGetData(stmt, 1, SQL_C_CHAR, idStr, sizeof(idStr), NULL);                        // ID
            SQLGetData(stmt, 2, SQL_C_WCHAR, name, sizeof(name), NULL);                         // Tên
            SQLGetData(stmt, 3, SQL_C_WCHAR, manu, sizeof(manu), NULL);                         // Hãng
            SQLGetData(stmt, 4, SQL_C_WCHAR, price, sizeof(price), NULL);                       // Giá
            SQLGetData(stmt, 5, SQL_C_WCHAR, operatingSys, sizeof(operatingSys), NULL);         // Hệ điều hành
            SQLGetData(stmt, 6, SQL_C_WCHAR, cpu, sizeof(cpu), NULL);                           // CPU
            SQLGetData(stmt, 7, SQL_C_SLONG, &ram, 0, NULL);                                    // RAM
            SQLGetData(stmt, 8, SQL_C_SLONG, &rom, 0, NULL);                                    // ROM
            SQLGetData(stmt, 9, SQL_C_SLONG, &screenSize, 0, NULL);                             // Kích thước màn hình
            SQLGetData(stmt, 10, SQL_C_SLONG, &pin, 0, NULL);                                   // Dung lượng pin

            // Gán dữ liệu vào đối tượng điện thoại
            p->setID(std::stoi(idStr));
            p->setName(wstringToString(name));
            p->setManu(wstringToString(manu));
            p->setPrice(wstringToString(price));
            p->setConfig(
                wstringToString(operatingSys),
                wstringToString(cpu),
                ram,
                rom,
                static_cast<float>(screenSize), // ép kiểu vì kích thước là float
                pin
            );

            SQLFreeHandle(SQL_HANDLE_STMT, stmt);
            return p;
        }
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    return nullptr;
}

void PhoneManagement::removePhoneByID(SQLHDBC db, const int& id) {
    SQLHSTMT stmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db, &stmt);

    // Câu lệnh SQL để xóa điện thoại theo ID
    std::wstring query = L"DELETE FROM PHONE WHERE ID = " + std::to_wstring(id);

    // Thực thi câu lệnh SQL
    SQLRETURN ret = SQLExecDirectW(stmt, (SQLWCHAR*)query.c_str(), SQL_NTS);

    // Kiểm tra kết quả của câu lệnh SQL
    if (ret == SQL_SUCCESS) {
        // Nếu xóa thành công, thông báo cho người dùng
        cout << "Delete phone by ID succesful: " << id << std::endl;
        //std::wcout.flush();  // Đảm bảo rằng dòng thông báo được in ngay lập tức

    }
    else {
        // Nếu xóa không thành công, thông báo cho người dùng
        cout << "Can't delete Phone with ID = " << id << ". Please check again" << endl;
    }

    // Giải phóng tài nguyên
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

void PhoneManagement::printPhoneList(SQLHDBC db) {
    SQLHSTMT stmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db, &stmt);

    std::wstring query = L"SELECT * FROM PHONE";
    SQLRETURN ret = SQLExecDirectW(stmt, (SQLWCHAR*)query.c_str(), SQL_NTS);

    if (ret == SQL_SUCCESS) {
        int id;
        wchar_t name[100], manu[50], operatingSys[50], cpu[50];
        float price, screenSize;
        int ram, rom, pin;

        while (SQLFetch(stmt) == SQL_SUCCESS) {
            SQLGetData(stmt, 1, SQL_C_SLONG, &id, 0, NULL);
            SQLGetData(stmt, 2, SQL_C_WCHAR, name, sizeof(name), NULL);
            SQLGetData(stmt, 3, SQL_C_WCHAR, manu, sizeof(manu), NULL);
            SQLGetData(stmt, 4, SQL_C_FLOAT, &price, 0, NULL);
            SQLGetData(stmt, 5, SQL_C_WCHAR, operatingSys, sizeof(operatingSys), NULL);
            SQLGetData(stmt, 6, SQL_C_WCHAR, cpu, sizeof(cpu), NULL);
            SQLGetData(stmt, 7, SQL_C_SLONG, &ram, 0, NULL);
            SQLGetData(stmt, 8, SQL_C_SLONG, &rom, 0, NULL);
            SQLGetData(stmt, 9, SQL_C_FLOAT, &screenSize, 0, NULL);
            SQLGetData(stmt, 10, SQL_C_SLONG, &pin, 0, NULL);

            // Tạo đối tượng DienThoai mới
            Phone p;
            p.setID(id);
            p.setName(wstringToString(name));
            p.setManu(wstringToString(manu));
            p.setPrice(std::to_string(price));  // nếu setGia() nhận string, cần chuyển float sang string
            p.setConfig(
                wstringToString(operatingSys),
                wstringToString(cpu),
                ram,
                rom,
                screenSize,
                pin
            );

            // Đưa vào danh sách
            cout << p << endl;
            cout << "-----------------------------" << std::endl;
        }
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

void PhoneManagement::getPhoneList(SQLHDBC db) {
    SQLHSTMT stmt;
    SQLRETURN ret;

    // Cấp phát handle cho câu lệnh SQL
    SQLAllocHandle(SQL_HANDLE_STMT, db, &stmt);

    // Câu lệnh lấy tất cả điện thoại
    std::wstring query = L"SELECT * FROM PHONE";

    // Thực thi câu lệnh
    ret = SQLExecDirectW(stmt, (SQLWCHAR*)query.c_str(), SQL_NTS);

    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        while (SQLFetch(stmt) == SQL_SUCCESS) {
            char idStr[20] = {};
            wchar_t name[100] = {}, manu[50] = {}, price[50] = {}, operatingSys[50] = {}, cpu[50] = {};
            int ram = 0, rom = 0, pin = 0;
            float screenSize = 0;

            SQLGetData(stmt, 1, SQL_C_CHAR, idStr, sizeof(idStr), NULL);
            SQLGetData(stmt, 2, SQL_C_WCHAR, name, sizeof(name), NULL);
            SQLGetData(stmt, 3, SQL_C_WCHAR, manu, sizeof(manu), NULL);
            SQLGetData(stmt, 4, SQL_C_WCHAR, price, sizeof(price), NULL);
            SQLGetData(stmt, 5, SQL_C_WCHAR, operatingSys, sizeof(operatingSys), NULL);
            SQLGetData(stmt, 6, SQL_C_WCHAR, cpu, sizeof(cpu), NULL);
            SQLGetData(stmt, 7, SQL_C_SLONG, &ram, 0, NULL);
            SQLGetData(stmt, 8, SQL_C_SLONG, &rom, 0, NULL);
            SQLGetData(stmt, 9, SQL_C_FLOAT, &screenSize, 0, NULL);
            SQLGetData(stmt, 10, SQL_C_SLONG, &pin, 0, NULL);

            round_to_decimal(screenSize, 2); // Làm tròn kích th
            Phone p;
            p.setID(std::stoi(idStr));
            p.setName(wstringToString(name));
            p.setManu(wstringToString(manu));
            p.setPrice(wstringToString(price));
            p.setConfig(
                wstringToString(operatingSys),
                wstringToString(cpu),
                ram,
                rom,
                screenSize,
                pin
            );

            this->Push_back(p);
        }
    }
    else {
        std::wcerr << L"Can't execute SQL query. Error code: " << ret << std::endl;
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}



void PhoneManagement::editPhoneInfor(SQLHDBC db, int id) {
    SQLHSTMT stmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db, &stmt);

    // Tìm kiếm xem điện thoại có tồn tại không
    std::wstring checkQuery = L"SELECT COUNT(*) FROM PHONE WHERE ID = " + std::to_wstring(id);
    SQLINTEGER count = 0;

    if (SQLExecDirectW(stmt, (SQLWCHAR*)checkQuery.c_str(), SQL_NTS) == SQL_SUCCESS &&
        SQLFetch(stmt) == SQL_SUCCESS) {
        SQLGetData(stmt, 1, SQL_C_SLONG, &count, 0, NULL);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    if (count == 0) {
        std::wcout << L"Can't find phone with ID = " << id << L"\n";
        return;
    }

    // Nhap thong tin moi tu nguoi dung
    std::string name, manu, operatingSys, cpu, price;
    int ram, rom, pin;
    float screenSize;

    std::cin.ignore();
    std::cout << "Input new phone name: ";
    std::getline(std::cin, name);

    std::cout << "Input new phone manufacturer: ";
    std::getline(std::cin, manu);

    std::cout << "Input new Phone operating system: ";
    std::getline(std::cin, operatingSys);

    std::cout << "Input new phone CPU: ";
    std::getline(std::cin, cpu);

    std::cout << "Input RAM (GB): ";
    std::cin >> ram;

    std::cout << "Input ROM ROM (GB): ";
    std::cin >> rom;

    std::cout << "Input new screen size (inch): ";
    std::cin >> screenSize;

    std::cout << "Input new pin (mAh): ";
    std::cin >> pin;

    std::cout << "Input new price (million VND): ";
    std::cin >> price;
    std::cin.ignore(); // Clear newline character

    float fPrice = 0.0;
    try {
        fPrice = std::stoi(price);
    }
    catch (...) {
        std::cout << "Error: Price value invalid!\n";
        return;
    }

    // Tao cau truy van UPDATE
    std::wstring query = L"UPDATE PHONE SET NamePhone = N'" + std::wstring(name.begin(), name.end()) +
        L"', Manufacturer = N'" + std::wstring(manu.begin(), manu.end()) +
        L"', OperatingSystem = N'" + std::wstring(operatingSys.begin(), operatingSys.end()) +
        L"', CPU = N'" + std::wstring(cpu.begin(), cpu.end()) +
        L"', RAM = " + std::to_wstring(ram) +
        L", ROM = " + std::to_wstring(rom) +
        L", ScreenSize = " + std::to_wstring(screenSize) +
        L", Pin = " + std::to_wstring(pin) +
        L", Price = " + std::to_wstring(fPrice) +
        L" WHERE ID = " + std::to_wstring(id);

    SQLAllocHandle(SQL_HANDLE_STMT, db, &stmt);
    if (SQLExecDirectW(stmt, (SQLWCHAR*)query.c_str(), SQL_NTS) == SQL_SUCCESS) {
        std::wcout << L"Update phone information succesful!\n";
    }
    else {
        SQLWCHAR sqlState[6];
        SQLINTEGER nativeError;
        SQLWCHAR messageText[256];
        SQLSMALLINT textLength;

        SQLGetDiagRecW(SQL_HANDLE_STMT, stmt, 1, sqlState, &nativeError, messageText, sizeof(messageText) / sizeof(SQLWCHAR), &textLength);

        std::wcout << L"Error when update phone information!\n";
        std::wcout << L"SQLSTATE: " << sqlState << L"\n";
        std::wcout << L"Error code: " << nativeError << L"\n";
        std::wcout << L"Message: " << messageText << L"\n";
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

std::vector<Phone> getPhonesFromDatabase() {
    std::vector<Phone> phones;

    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLRETURN ret;
    SQLCHAR connStr[] = "Driver={ODBC Driver 17 for SQL Server};Server=localhost\\SQLEXPRESS;Database=PhoneManagement;UID=sa;PWD=123;";
    //SQLCHAR connStr[] = "Driver={ODBC Driver 17 for SQL Server};Server=localhost;Database=PhoneManagement;UID=sa;PWD=123;";
    // SQLCHAR connStr[] = "Driver={SQL Server};Server=localhost;Database=PhoneManagement;Trusted_Connection=yes;";
    
    SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env);
    SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
    SQLAllocHandle(SQL_HANDLE_DBC, env, &dbc);

    ret = SQLDriverConnectA(dbc, NULL, connStr, SQL_NTS, NULL, 0, NULL, SQL_DRIVER_COMPLETE);

    if (SQL_SUCCEEDED(ret)) {
        SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
        SQLExecDirectA(stmt, (SQLCHAR*)"SELECT * FROM PHONE", SQL_NTS);

        int id, ram, rom, pin;
        float screenSize;
        char name[101], manu[101], price[101], os[101], cpu[101];

        while (SQLFetch(stmt) == SQL_SUCCESS) {
            SQLGetData(stmt, 1, SQL_C_LONG, &id, 0, NULL);
            SQLGetData(stmt, 2, SQL_C_CHAR, name, sizeof(name), NULL);
            SQLGetData(stmt, 3, SQL_C_CHAR, manu, sizeof(manu), NULL);
            SQLGetData(stmt, 4, SQL_C_CHAR, price, sizeof(price), NULL);
            SQLGetData(stmt, 5, SQL_C_CHAR, os, sizeof(os), NULL);
            SQLGetData(stmt, 6, SQL_C_CHAR, cpu, sizeof(cpu), NULL);
            SQLGetData(stmt, 7, SQL_C_LONG, &ram, 0, NULL);
            SQLGetData(stmt, 8, SQL_C_LONG, &rom, 0, NULL);
            SQLGetData(stmt, 9, SQL_C_FLOAT, &screenSize, 0, NULL);
            SQLGetData(stmt, 10, SQL_C_LONG, &pin, 0, NULL);
            
            screenSize = round_to_decimal(screenSize, 2);
            ConfigPhone config = {os, cpu, ram, rom, screenSize, pin};
            phones.push_back(Phone(id, name, manu, config, price));
        }

        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    }

    SQLDisconnect(dbc);
    SQLFreeHandle(SQL_HANDLE_DBC, dbc);
    SQLFreeHandle(SQL_HANDLE_ENV, env);

    return phones;
}

std::vector<Phone> getPhonesByManuAndPriceOrder(const std::string& order, const std::string& manufacturer) {
    std::vector<Phone> phones;

    // Tạo môi trường và kết nối ODBC
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLRETURN ret;

    SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env);
    SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
    SQLAllocHandle(SQL_HANDLE_DBC, env, &dbc);
    SQLCHAR connStr[] = "Driver={ODBC Driver 17 for SQL Server};Server=localhost\\SQLEXPRESS;Database=PhoneManagement;UID=sa;PWD=123;";
    //SQLCHAR connStr[] = "Driver={ODBC Driver 17 for SQL Server};Server=localhost;Database=PhoneManagement;UID=sa;PWD=123;";
    ret = SQLDriverConnectA(dbc, NULL, connStr, SQL_NTS, NULL, 0, NULL, SQL_DRIVER_COMPLETE);

    if (!SQL_SUCCEEDED(ret)) {
        // Xử lý lỗi kết nối (nếu cần)
        SQLFreeHandle(SQL_HANDLE_DBC, dbc);
        SQLFreeHandle(SQL_HANDLE_ENV, env);
        return phones; // trả về rỗng
    }

    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    std::wstring wOrder = (order == "desc" || order == "DESC") ? L"DESC" : L"ASC";
    std::wstring manuWStr(manufacturer.begin(), manufacturer.end());

    std::wstring query = L"SELECT * FROM PHONE WHERE Manufacturer = N'" + manuWStr + L"' ORDER BY Price " + wOrder;

    ret = SQLExecDirectW(stmt, (SQLWCHAR*)query.c_str(), SQL_NTS);

    if (SQL_SUCCEEDED(ret)) {
        int id;
        wchar_t name[100], manu[50], operatingSys[50], cpu[50];
        float price, screenSize;
        int ram, rom, pin;

        while (SQLFetch(stmt) == SQL_SUCCESS) {
            SQLGetData(stmt, 1, SQL_C_SLONG, &id, 0, NULL);
            SQLGetData(stmt, 2, SQL_C_WCHAR, name, sizeof(name), NULL);
            SQLGetData(stmt, 3, SQL_C_WCHAR, manu, sizeof(manu), NULL);
            SQLGetData(stmt, 4, SQL_C_FLOAT, &price, 0, NULL);
            SQLGetData(stmt, 5, SQL_C_WCHAR, operatingSys, sizeof(operatingSys), NULL);
            SQLGetData(stmt, 6, SQL_C_WCHAR, cpu, sizeof(cpu), NULL);
            SQLGetData(stmt, 7, SQL_C_SLONG, &ram, 0, NULL);
            SQLGetData(stmt, 8, SQL_C_SLONG, &rom, 0, NULL);
            SQLGetData(stmt, 9, SQL_C_FLOAT, &screenSize, 0, NULL);
            SQLGetData(stmt, 10, SQL_C_SLONG, &pin, 0, NULL);

            Phone p;
            p.setID(id);
            p.setName(wstringToString(name));
            p.setManu(wstringToString(manu));
            p.setPrice(priceStandardize(std::to_string(static_cast<long long>(price))));
            p.setConfig(
                wstringToString(operatingSys),
                wstringToString(cpu),
                ram,
                rom,
                screenSize,
                pin
            );

            phones.push_back(p);
        }
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    SQLDisconnect(dbc);
    SQLFreeHandle(SQL_HANDLE_DBC, dbc);
    SQLFreeHandle(SQL_HANDLE_ENV, env);

    return phones;
}

std::vector<Phone> getPhonesByMaxPriceDesc(float maxPrice) {
    std::vector<Phone> phones;

    // Tạo môi trường và kết nối ODBC
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLRETURN ret;

    SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env);
    SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
    SQLAllocHandle(SQL_HANDLE_DBC, env, &dbc);

    //SQLCHAR connStr[] = "Driver={ODBC Driver 17 for SQL Server};Server=localhost;Database=PhoneManagement;UID=sa;PWD=123;";
    SQLCHAR connStr[] = "Driver={ODBC Driver 17 for SQL Server};Server=localhost\\SQLEXPRESS;Database=PhoneManagement;UID=sa;PWD=123;";
    ret = SQLDriverConnectA(dbc, NULL, connStr, SQL_NTS, NULL, 0, NULL, SQL_DRIVER_COMPLETE);

    if (!SQL_SUCCEEDED(ret)) {
        // Xử lý lỗi kết nối (nếu cần)
        SQLFreeHandle(SQL_HANDLE_DBC, dbc);
        SQLFreeHandle(SQL_HANDLE_ENV, env);
        return phones; // trả về rỗng
    }

    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    std::wstring query = L"SELECT * FROM PHONE WHERE Price < " + std::to_wstring(maxPrice) + L" ORDER BY Price DESC";

    ret = SQLExecDirectW(stmt, (SQLWCHAR*)query.c_str(), SQL_NTS);

    if (SQL_SUCCEEDED(ret)) {
        int id;
        wchar_t name[100], manu[50], operatingSys[50], cpu[50];
        float price, screenSize;
        int ram, rom, pin;

        while (SQLFetch(stmt) == SQL_SUCCESS) {
            SQLGetData(stmt, 1, SQL_C_SLONG, &id, 0, NULL);
            SQLGetData(stmt, 2, SQL_C_WCHAR, name, sizeof(name), NULL);
            SQLGetData(stmt, 3, SQL_C_WCHAR, manu, sizeof(manu), NULL);
            SQLGetData(stmt, 4, SQL_C_FLOAT, &price, 0, NULL);
            SQLGetData(stmt, 5, SQL_C_WCHAR, operatingSys, sizeof(operatingSys), NULL);
            SQLGetData(stmt, 6, SQL_C_WCHAR, cpu, sizeof(cpu), NULL);
            SQLGetData(stmt, 7, SQL_C_SLONG, &ram, 0, NULL);
            SQLGetData(stmt, 8, SQL_C_SLONG, &rom, 0, NULL);
            SQLGetData(stmt, 9, SQL_C_FLOAT, &screenSize, 0, NULL);
            SQLGetData(stmt, 10, SQL_C_SLONG, &pin, 0, NULL);

            Phone p;
            p.setID(id);
            p.setName(wstringToString(name));
            p.setManu(wstringToString(manu));
            p.setPrice(priceStandardize(std::to_string(static_cast<long long>(price))));
            p.setConfig(
                wstringToString(operatingSys),
                wstringToString(cpu),
                ram,
                rom,
                screenSize,
                pin
            );

            phones.push_back(p);
        }
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    SQLDisconnect(dbc);
    SQLFreeHandle(SQL_HANDLE_DBC, dbc);
    SQLFreeHandle(SQL_HANDLE_ENV, env);

    return phones;
}
