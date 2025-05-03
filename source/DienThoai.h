#ifndef _DIEN_THOAI_H_
#define _DIEN_THOAI_H_

#include "lib.h"

struct CauHinh
{
    string heDieuHanh;          // Hệ điều hành
    string cpu;                 // Chip xử lý
    int ram;                    // Dung lượng RAM (GB)
    int rom;                    // Bộ nhớ trong (GB)
    float kichThuocManHinh;     // Kích thước màn hình (inch)
    int dungLuongPin;           // Dung lượng pin (mAh)
};

class DienThoai {
private:
    int _id;                        // ID điện thoại
    string _ten;                    // Tên điện thoại
    string _hang;                   // Hãng sản xuất
    CauHinh _cauHinh;               // Cấu hình điện thoại
    string _gia;                    // Giá tiền (triệu VND)

public:
    DienThoai();
    DienThoai(const DienThoai&);
    DienThoai(const int, const string, const string, const CauHinh, const string);
    ~DienThoai();

    ///// --- Getter ---
    int getID() const 
    {
        return _id;
    }

    string getTen() const 
    {
        return _ten;
    }

    string getHang() const 
    {
        return _hang;
    }

    CauHinh getCauHinh() const 
    {
        return _cauHinh;
    }

    string getGia() const 
    {
        return _gia;
    }

    void nhapDuLieu();
    //void insertToDB(SQLHDBC db); // db là kết nối đến SQL Server

    friend ostream& operator<<(ostream& os, const DienThoai);
    bool operator==(const DienThoai);
    bool operator!=(const DienThoai);
};

#endif