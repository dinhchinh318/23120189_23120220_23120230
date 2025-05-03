#include "QuanLyDienThoai.h"

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

/* void QuanLyDienThoai::XoaDienThoaiTheoID(SQLHDBC db,const int& id) {
    SQLHSTMT stmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db, &stmt);

    // Câu lệnh SQL để xóa điện thoại theo ID
    std::wstring query = L"DELETE FROM DIENTHOAI WHERE ID = " + std::to_wstring(id);

    // Thực thi câu lệnh SQL
    SQLRETURN ret = SQLExecDirectW(stmt, (SQLWCHAR*)query.c_str(), SQL_NTS);

    // Kiểm tra kết quả của câu lệnh SQL
    if (ret == SQL_SUCCESS) {
		// Nếu xóa thành công, thông báo cho người dùng
        std::wcout << L"Xóa thành công điện thoại với ID: " << id << std::endl;
        std::wcout.flush();  // Đảm bảo rằng dòng thông báo được in ngay lập tức

    }
    else {
		// Nếu xóa không thành công, thông báo cho người dùng
		cout << "Không thể xóa điện thoại với ID: " << id << endl;
        std::wcout << L"Không thể xóa điện thoại với ID " << id << L". Vui lòng kiểm tra lại.\n";
    }

    // Giải phóng tài nguyên
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

void QuanLyDienThoai::XuatDanhSachDienThoai(SQLHDBC db) {
    SQLHSTMT stmt;
    SQLRETURN ret;

    // Cấp phát handle cho câu lệnh SQL
    SQLAllocHandle(SQL_HANDLE_STMT, db, &stmt);

    // Câu lệnh SQL để truy vấn tất cả các điện thoại trong bảng DIENTHOAI
    std::wstring query = L"SELECT * FROM DIENTHOAI";

    // Thực thi câu lệnh SQL
    ret = SQLExecDirectW(stmt, (SQLWCHAR*)query.c_str(), SQL_NTS);

    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        // Khai báo các biến để lưu dữ liệu truy vấn
        char idStr[20];
        wchar_t ten[100], hang[50], gia[50], heDieuHanh[50], cpu[50];
        int ram, rom, kichThuocManHinh, dungLuongPin;

        // Lấy từng bản ghi trong kết quả
        while (SQLFetch(stmt) == SQL_SUCCESS) {
            // Lấy dữ liệu từ từng cột
            SQLGetData(stmt, 1, SQL_C_CHAR, idStr, sizeof(idStr), NULL);                // ID
            SQLGetData(stmt, 2, SQL_C_WCHAR, ten, sizeof(ten), NULL);                   // Tên
            SQLGetData(stmt, 3, SQL_C_WCHAR, hang, sizeof(hang), NULL);                 // Hãng
            SQLGetData(stmt, 4, SQL_C_WCHAR, gia, sizeof(gia), NULL);                   // Giá
            SQLGetData(stmt, 5, SQL_C_WCHAR, heDieuHanh, sizeof(heDieuHanh), NULL);     // Hệ điều hành
            SQLGetData(stmt, 6, SQL_C_WCHAR, cpu, sizeof(cpu), NULL);                   // CPU
            SQLGetData(stmt, 7, SQL_C_SLONG, &ram, 0, NULL);                            // RAM
            SQLGetData(stmt, 8, SQL_C_SLONG, &rom, 0, NULL);                            // ROM
            SQLGetData(stmt, 9, SQL_C_SLONG, &kichThuocManHinh, 0, NULL);               // Kích thước màn hình
            SQLGetData(stmt, 10, SQL_C_SLONG, &dungLuongPin, 0, NULL);                  // Dung lượng pin

            // In thông tin điện thoại
            std::wcout << L"ID: " << idStr << L"\n"
                << L"Tên: " << ten << L"\n"
                << L"Hãng: " << hang << L"\n"
                << L"Giá: " << gia << L"\n"
                << L"Hệ điều hành: " << heDieuHanh << L"\n"
                << L"CPU: " << cpu << L"\n"
                << L"RAM: " << ram << L"\n"
                << L"ROM: " << rom << L"\n"
                << L"Kích thước màn hình: " << kichThuocManHinh << L"\n"
                << L"Dung lượng pin: " << dungLuongPin << L"\n"
                << L"---------------------------\n";
        }
    }
    else {
        std::wcout << L"Lỗi khi truy vấn dữ liệu!\n";
    }

    // Giải phóng tài nguyên
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
} */