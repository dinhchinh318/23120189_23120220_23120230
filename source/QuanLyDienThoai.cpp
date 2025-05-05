#include "QuanLyDienThoai.h"

#ifdef _WIN32
#include <windows.h>
#endif

QuanLyDienThoai::QuanLyDienThoai()
{
    _pHead = _pTail = nullptr;
    _soLuong = 0;
}

QuanLyDienThoai::~QuanLyDienThoai()
{
    while(_pHead)
    {
        Node* tmp = _pHead;
        _pHead = _pHead->_pNext;
        delete tmp;
        _soLuong--;
    }
}

void QuanLyDienThoai::Push_back(const DienThoai& dt)
{
    Node* node = new Node {dt, nullptr};
    if(!_pHead)
    {
        _pHead = _pTail = node;
    }
    else
    {
        _pTail->_pNext = node;
        _pTail = node;
    }
    _soLuong++;
}

void QuanLyDienThoai::RemoveHead()
{
    if(!_pHead) return;
    Node* tmp = _pHead;
    _pHead = _pHead->_pNext;
    delete tmp;
    if(!_pHead)
    {
        _pTail == nullptr;
    }
    _soLuong--;
}

void QuanLyDienThoai::RemoveTail()
{
    if (_pHead == nullptr)
    return;

    if (_pHead == _pTail)
    {
        Node* node = _pHead;
        _pHead = _pTail = nullptr;
        _soLuong--;
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
    _soLuong--;
    return;
}

void QuanLyDienThoai::Remove(const DienThoai& dt)
{
    if(!_pHead) return;
    if(_pHead->info == dt) RemoveHead();
    else if(_pTail->info == dt) RemoveTail();
    else 
    {
        Node* tmp = _pHead;
        while(tmp->info != dt)
        {
            tmp = tmp->_pNext;
        }
        Node* del = tmp;
        tmp = tmp->_pNext;
        delete del;
    }
    _soLuong--;
}

void QuanLyDienThoai::Clear()
{
    while(_pHead)
    {
        Node* tmp = _pHead;
        _pHead = _pHead->_pNext;
        delete tmp;
        _soLuong--;
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
    return DienThoai(); // Trả về đối tượng rỗng nếu không tìm thấy
} */

// Hàm chuyển đổi std::wstring (chuỗi wide) sang std::string (UTF-8)
std::string QuanLyDienThoai::wstringToString(const std::wstring& wstr) {
    if (wstr.empty()) return std::string();
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), (int)wstr.size(), nullptr, 0, nullptr, nullptr);
    std::string result(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), (int)wstr.size(), &result[0], size_needed, nullptr, nullptr);
    return result;
}


// Tìm điện thoại theo ID trong cơ sở dữ liệu và trả về con trỏ đối tượng DienThoai
DienThoai* QuanLyDienThoai::TimKiemTheoID(SQLHDBC db, const int& id) {
    SQLHSTMT stmt;

    // Cấp phát handle cho câu lệnh SQL
    SQLAllocHandle(SQL_HANDLE_STMT, db, &stmt);

    // Tạo câu lệnh SQL bằng chuỗi wide (Unicode)
    std::wstring query = L"SELECT * FROM DIENTHOAI WHERE ID = " + std::to_wstring(id);

    // Thực thi câu lệnh truy vấn
    SQLRETURN ret = SQLExecDirectW(stmt, (SQLWCHAR*)query.c_str(), SQL_NTS);

    // Nếu thực thi thành công
    if (ret == SQL_SUCCESS) {
        // Nếu có bản ghi trả về
        if (SQLFetch(stmt) == SQL_SUCCESS) {
            // Cấp phát đối tượng điện thoại mới
            DienThoai* dt = new DienThoai();

            // Khai báo biến để chứa dữ liệu truy vấn
            char idStr[20];
            wchar_t ten[100], hang[50], gia[50], heDieuHanh[50], cpu[50];
            int ram, rom, kichThuocManHinh, dungLuongPin;

            // Lấy dữ liệu từ từng cột (theo thứ tự cột trong bảng)
            SQLGetData(stmt, 1, SQL_C_CHAR, idStr, sizeof(idStr), NULL);                    // ID
            SQLGetData(stmt, 2, SQL_C_WCHAR, ten, sizeof(ten), NULL);                       // Tên
            SQLGetData(stmt, 3, SQL_C_WCHAR, hang, sizeof(hang), NULL);                     // Hãng
            SQLGetData(stmt, 4, SQL_C_WCHAR, gia, sizeof(gia), NULL);                       // Giá
            SQLGetData(stmt, 5, SQL_C_WCHAR, heDieuHanh, sizeof(heDieuHanh), NULL);         // Hệ điều hành
            SQLGetData(stmt, 6, SQL_C_WCHAR, cpu, sizeof(cpu), NULL);                       // CPU
            SQLGetData(stmt, 7, SQL_C_SLONG, &ram, 0, NULL);                                // RAM
            SQLGetData(stmt, 8, SQL_C_SLONG, &rom, 0, NULL);                                // ROM
            SQLGetData(stmt, 9, SQL_C_SLONG, &kichThuocManHinh, 0, NULL);                   // Kích thước màn hình
            SQLGetData(stmt, 10, SQL_C_SLONG, &dungLuongPin, 0, NULL);                      // Dung lượng pin

            // Gán dữ liệu vào đối tượng điện thoại
            dt->setID(std::stoi(idStr));
            dt->setTen(wstringToString(ten));
            dt->setHang(wstringToString(hang));
            dt->setGia(wstringToString(gia));
            dt->setCauHinh(
                wstringToString(heDieuHanh),
                wstringToString(cpu),
                ram,
                rom,
                static_cast<float>(kichThuocManHinh), // ép kiểu vì kích thước là float
                dungLuongPin
            );

            // Giải phóng handle truy vấn
            SQLFreeHandle(SQL_HANDLE_STMT, stmt);

            // Trả về đối tượng kết quả
            return dt;
        }
    }

    // Nếu không tìm thấy hoặc lỗi, giải phóng và trả về nullptr
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    return nullptr;
}

DienThoai* QuanLyDienThoai::TimKiemTheoTen(SQLHDBC db, const std::string& tenStr) {
    SQLHSTMT stmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db, &stmt);

    // Chuyển chuỗi tên từ std::string sang std::wstring để truy vấn SQL Unicode
    std::wstring tenWStr(tenStr.begin(), tenStr.end());

    // Câu lệnh SQL tìm kiếm theo tên (dùng N trước chuỗi để hỗ trợ Unicode)
    std::wstring query = L"SELECT * FROM DIENTHOAI WHERE TEN = N'" + tenWStr + L"'";
    SQLRETURN ret = SQLExecDirectW(stmt, (SQLWCHAR*)query.c_str(), SQL_NTS);

    if (ret == SQL_SUCCESS) {
        if (SQLFetch(stmt) == SQL_SUCCESS) {
            DienThoai* dt = new DienThoai();

            char idStr[20];
            wchar_t ten[100], hang[50], gia[50], heDieuHanh[50], cpu[50];
            int ram, rom, kichThuocManHinh, dungLuongPin;

            SQLGetData(stmt, 1, SQL_C_CHAR, idStr, sizeof(idStr), NULL);
            SQLGetData(stmt, 2, SQL_C_WCHAR, ten, sizeof(ten), NULL);
            SQLGetData(stmt, 3, SQL_C_WCHAR, hang, sizeof(hang), NULL);
            SQLGetData(stmt, 4, SQL_C_WCHAR, gia, sizeof(gia), NULL);
            SQLGetData(stmt, 5, SQL_C_WCHAR, heDieuHanh, sizeof(heDieuHanh), NULL);
            SQLGetData(stmt, 6, SQL_C_WCHAR, cpu, sizeof(cpu), NULL);
            SQLGetData(stmt, 7, SQL_C_SLONG, &ram, 0, NULL);
            SQLGetData(stmt, 8, SQL_C_SLONG, &rom, 0, NULL);
            SQLGetData(stmt, 9, SQL_C_SLONG, &kichThuocManHinh, 0, NULL);
            SQLGetData(stmt, 10, SQL_C_SLONG, &dungLuongPin, 0, NULL);

            dt->setID(std::stoi(idStr));
            dt->setTen(wstringToString(ten));
            dt->setHang(wstringToString(hang));
            dt->setGia(wstringToString(gia));
            dt->setCauHinh(
                wstringToString(heDieuHanh),
                wstringToString(cpu),
                ram,
                rom,
                static_cast<float>(kichThuocManHinh),
                dungLuongPin
            );

            SQLFreeHandle(SQL_HANDLE_STMT, stmt);
            return dt;
        }
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    return nullptr;
}

void QuanLyDienThoai::XoaDienThoaiTheoID(SQLHDBC db,const int& id) {
    SQLHSTMT stmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db, &stmt);

    // Câu lệnh SQL để xóa điện thoại theo ID
    std::wstring query = L"DELETE FROM DIENTHOAI WHERE ID = " + std::to_wstring(id);

    // Thực thi câu lệnh SQL
    SQLRETURN ret = SQLExecDirectW(stmt, (SQLWCHAR*)query.c_str(), SQL_NTS);

    // Kiểm tra kết quả của câu lệnh SQL
    if (ret == SQL_SUCCESS) {
		// Nếu xóa thành công, thông báo cho người dùng
        cout << "Xóa thành công điện thoại với ID: " << id << std::endl;
        //std::wcout.flush();  // Đảm bảo rằng dòng thông báo được in ngay lập tức

    }
    else {
		// Nếu xóa không thành công, thông báo cho người dùng
		cout << "Không thể xóa điện thoại với ID: " << id <<" Vui long kiem tra lai"<< endl;
    }

    // Giải phóng tài nguyên
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

void QuanLyDienThoai::XuatDanhSachDienThoai(SQLHDBC db) {
    SQLHSTMT stmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db, &stmt);

    std::wstring query = L"SELECT * FROM DIENTHOAI";
    SQLRETURN ret = SQLExecDirectW(stmt, (SQLWCHAR*)query.c_str(), SQL_NTS);

    if (ret == SQL_SUCCESS) {
        int id;
        wchar_t ten[100], hang[50], heDieuHanh[50], cpu[50];
        float gia, kichThuocManHinh;
        int ram, rom, dungLuongPin;

        while (SQLFetch(stmt) == SQL_SUCCESS) {
            SQLGetData(stmt, 1, SQL_C_SLONG, &id, 0, NULL);
            SQLGetData(stmt, 2, SQL_C_WCHAR, ten, sizeof(ten), NULL);
            SQLGetData(stmt, 3, SQL_C_WCHAR, hang, sizeof(hang), NULL);
            SQLGetData(stmt, 4, SQL_C_FLOAT, &gia, 0, NULL);
            SQLGetData(stmt, 5, SQL_C_WCHAR, heDieuHanh, sizeof(heDieuHanh), NULL);
            SQLGetData(stmt, 6, SQL_C_WCHAR, cpu, sizeof(cpu), NULL);
            SQLGetData(stmt, 7, SQL_C_SLONG, &ram, 0, NULL);
            SQLGetData(stmt, 8, SQL_C_SLONG, &rom, 0, NULL);
            SQLGetData(stmt, 9, SQL_C_FLOAT, &kichThuocManHinh, 0, NULL);
            SQLGetData(stmt, 10, SQL_C_SLONG, &dungLuongPin, 0, NULL);

            // Tạo đối tượng DienThoai mới
            DienThoai dt;
            dt.setID(id);
            dt.setTen(wstringToString(ten));
            dt.setHang(wstringToString(hang));
            dt.setGia(std::to_string(gia));  // nếu setGia() nhận string, cần chuyển float sang string
            dt.setCauHinh(
                wstringToString(heDieuHanh),
                wstringToString(cpu),
                ram,
                rom,
                kichThuocManHinh,
                dungLuongPin
            );

            // Đưa vào danh sách
            cout << dt << endl;
            cout<< "-----------------------------" << std::endl;
        }
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

void QuanLyDienThoai::LayDanhSachDienThoai(SQLHDBC db) {
    SQLHSTMT stmt;
    SQLRETURN ret;

    // Cấp phát handle cho câu lệnh SQL
    SQLAllocHandle(SQL_HANDLE_STMT, db, &stmt);

    // Câu lệnh lấy tất cả điện thoại
    std::wstring query = L"SELECT * FROM DIENTHOAI";

    // Thực thi câu lệnh
    ret = SQLExecDirectW(stmt, (SQLWCHAR*)query.c_str(), SQL_NTS);

    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        while (SQLFetch(stmt) == SQL_SUCCESS) {
            char idStr[20] = {};
            wchar_t ten[100] = {}, hang[50] = {}, gia[50] = {}, heDieuHanh[50] = {}, cpu[50] = {};
            int ram = 0, rom = 0, dungLuongPin = 0;
            float kichThuocManHinh = 0;

            SQLGetData(stmt, 1, SQL_C_CHAR, idStr, sizeof(idStr), NULL);                    
            SQLGetData(stmt, 2, SQL_C_WCHAR, ten, sizeof(ten), NULL);                       
            SQLGetData(stmt, 3, SQL_C_WCHAR, hang, sizeof(hang), NULL);                     
            SQLGetData(stmt, 4, SQL_C_WCHAR, gia, sizeof(gia), NULL);                       
            SQLGetData(stmt, 5, SQL_C_WCHAR, heDieuHanh, sizeof(heDieuHanh), NULL);         
            SQLGetData(stmt, 6, SQL_C_WCHAR, cpu, sizeof(cpu), NULL);                       
            SQLGetData(stmt, 7, SQL_C_SLONG, &ram, 0, NULL);                                
            SQLGetData(stmt, 8, SQL_C_SLONG, &rom, 0, NULL);                                
            SQLGetData(stmt, 9, SQL_C_FLOAT, &kichThuocManHinh, 0, NULL);                   
            SQLGetData(stmt, 10, SQL_C_SLONG, &dungLuongPin, 0, NULL);                      

            DienThoai dt;
            dt.setID(std::stoi(idStr));
            dt.setTen(wstringToString(ten));
            dt.setHang(wstringToString(hang));
            dt.setGia(wstringToString(gia));
            dt.setCauHinh(
                wstringToString(heDieuHanh),
                wstringToString(cpu),
                ram,
                rom,
                kichThuocManHinh,
                dungLuongPin
            );

            this->Push_back(dt);
        }
    } else {
        std::wcerr << L"Không thể thực thi truy vấn SQL. Mã lỗi: " << ret << std::endl;
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}



void QuanLyDienThoai::ChinhSuaThongTinDienThoai(SQLHDBC db, int id) {
    SQLHSTMT stmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db, &stmt);

    // Tìm kiếm xem điện thoại có tồn tại không
    std::wstring checkQuery = L"SELECT COUNT(*) FROM DIENTHOAI WHERE ID = " + std::to_wstring(id);
    SQLINTEGER count = 0;

    if (SQLExecDirectW(stmt, (SQLWCHAR*)checkQuery.c_str(), SQL_NTS) == SQL_SUCCESS &&
        SQLFetch(stmt) == SQL_SUCCESS) {
        SQLGetData(stmt, 1, SQL_C_SLONG, &count, 0, NULL);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    if (count == 0) {
        std::wcout << L"⚠ Khong tim thay dien thoai co ID = " << id << L"\n";
        return;
    }

    // Nhap thong tin moi tu nguoi dung
    std::string ten, hang, heDieuHanh, cpu, giaStr;
    int ram, rom, dungLuongPin;
    float kichThuocManHinh;

    std::cin.ignore();
    std::cout << "Nhap ten dien thoai moi: ";
    std::getline(std::cin, ten);

    std::cout << "Nhap hang san xuat moi: ";
    std::getline(std::cin, hang);

    std::cout << "Nhap he dieu hanh moi: ";
    std::getline(std::cin, heDieuHanh);

    std::cout << "Nhap CPU moi: ";
    std::getline(std::cin, cpu);

    std::cout << "Nhap RAM (GB) moi: ";
    std::cin >> ram;

    std::cout << "Nhap ROM (GB) moi: ";
    std::cin >> rom;

    std::cout << "Nhap kich thuoc man hinh (inch) moi: ";
    std::cin >> kichThuocManHinh;

    std::cout << "Nhap dung luong pin (mAh) moi: ";
    std::cin >> dungLuongPin;

    std::cout << "Nhap gia tien (trieu VND) moi: ";
    std::cin >> giaStr;
    std::cin.ignore(); // Clear newline character

    float giaFloat = 0.0;
    try {
        giaFloat = std::stof(giaStr);
    }
    catch (...) {
        std::cout << "❌ Loi: Gia tien nhap vao khong hop le!\n";
        return;
    }

    // Tao cau truy van UPDATE
    std::wstring query = L"UPDATE DIENTHOAI SET Ten = N'" + std::wstring(ten.begin(), ten.end()) +
        L"', Hang = N'" + std::wstring(hang.begin(), hang.end()) +
        L"', HeDieuHanh = N'" + std::wstring(heDieuHanh.begin(), heDieuHanh.end()) +
        L"', CPU = N'" + std::wstring(cpu.begin(), cpu.end()) +
        L"', RAM = " + std::to_wstring(ram) +
        L", ROM = " + std::to_wstring(rom) +
        L", KichThuocManHinh = " + std::to_wstring(kichThuocManHinh) +
        L", DungLuongPin = " + std::to_wstring(dungLuongPin) +
        L", Gia = " + std::to_wstring(giaFloat) +
        L" WHERE ID = " + std::to_wstring(id);

    SQLAllocHandle(SQL_HANDLE_STMT, db, &stmt);
    if (SQLExecDirectW(stmt, (SQLWCHAR*)query.c_str(), SQL_NTS) == SQL_SUCCESS) {
        std::wcout << L"✅ Da cap nhat thong tin dien thoai thanh cong!\n";
    }
    else {
        SQLWCHAR sqlState[6];
        SQLINTEGER nativeError;
        SQLWCHAR messageText[256];
        SQLSMALLINT textLength;

        SQLGetDiagRecW(SQL_HANDLE_STMT, stmt, 1, sqlState, &nativeError, messageText, sizeof(messageText) / sizeof(SQLWCHAR), &textLength);

        std::wcout << L"Loi khi cap nhat thong tin dien thoai!\n";
        std::wcout << L"SQLSTATE: " << sqlState << L"\n";
        std::wcout << L"Error code: " << nativeError << L"\n";
        std::wcout << L"Message: " << messageText << L"\n";
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

