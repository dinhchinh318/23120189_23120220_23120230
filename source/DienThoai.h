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
    //int _soLuong;                  // Số lượng điện thoại
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

	void setID(int id)
	{
		_id = id;
	}
	void setTen(string ten)
	{
		_ten = ten;
	}
	void setHang(string hang)
	{
		_hang = hang;
	}
    void setCauHinh(string heDieuHanh, string cpu, int ram, int rom, float kichThuocManHinh, int dungLuongPin) {
		_cauHinh.heDieuHanh = heDieuHanh;
		_cauHinh.cpu = cpu;
		_cauHinh.ram = ram;
		_cauHinh.rom = rom;
		_cauHinh.kichThuocManHinh = kichThuocManHinh;
		_cauHinh.dungLuongPin = dungLuongPin;

    }
	void setCauHinh(CauHinh cauHinh)
	{
		_cauHinh = cauHinh;
            
	}
	void setGia(string gia)
	{
		_gia = gia;
	}

    
	

    /*int getSoLuong() const
    {
        return _soLuong;
    }*/

    void nhapDuLieu();
    void insertToDB(SQLHDBC db); // db là kết nối đến SQL Server

    friend ostream& operator<<(ostream& os, const DienThoai);
    bool operator==(const DienThoai);
    bool operator!=(const DienThoai);
};

#endif