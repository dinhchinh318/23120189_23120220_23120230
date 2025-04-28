#include "DienThoai.h"

void DienThoai::nhapDuLieu() {
    cout << "Nhap ID dien thoai: ";
    cin >> _id;
    cin.ignore(); // Xoá newline

    cout << "Nhap ten dien thoai: ";
    getline(cin, _ten);

    cout << "Nhap hang san xuat: ";
    getline(cin, _hang);

    cout << "Nhap he dieu hanh: ";
    getline(cin, _cauHinh.heDieuHanh);

    cout << "Nhap CPU: ";
    getline(cin, _cauHinh.cpu);

    cout << "Nhap RAM (GB): ";
    cin >> _cauHinh.ram;

    cout << "Nhap ROM (GB): ";
    cin >> _cauHinh.rom;

    cout << "Nhap kich thuoc man hinh (inch): ";
    cin >> _cauHinh.kichThuocManHinh;

    cout << "Nhap dung luong pin (mAh): ";
    cin >> _cauHinh.dungLuongPin;

    cin.ignore();

    cout << "Nhap gia tien (trieu VND): ";
    getline(cin, _gia);

    _gia = ChuanHoaGia(_gia);
}


// Định nghĩa operator<< để xuất thông tin cấu hình
ostream& operator<<(ostream& os, const CauHinh& ch) 
{
    os << "He dieu hanh    : " << ch.heDieuHanh << "\n"
       << "CPU             : " << ch.cpu << "\n"
       << "RAM             : " << ch.ram << " GB\n"
       << "ROM             : " << ch.rom << " GB\n"
       << "Man hinh        : " << ch.kichThuocManHinh << " inch\n"
       << "Pin             : " << ch.dungLuongPin << " mAh";
    return os;
}

DienThoai::DienThoai(const DienThoai& dt) 
{
    _id = dt._id;
    _ten = dt._ten;
    _hang = dt._hang;
    _cauHinh = dt._cauHinh;
    _gia = dt._gia;
}

DienThoai::DienThoai() 
                    : _id(0), _ten(""), _hang(""), _cauHinh(), _gia("0") {}

DienThoai::DienThoai(const int id, const string ten, const string hang, const CauHinh cauHinh, string gia) 
                    : _id(0), _ten(ten), _hang(hang), _cauHinh(cauHinh), _gia(gia) {}

DienThoai::~DienThoai() 
{
    // Destructor
}


ostream& operator<<(ostream& os, const DienThoai dt)
{
    os  << "ID              : " << dt._id << "\n"
        << "Hang            : " << dt._hang << "\n"
        << "Ten             : " << dt._ten << "\n"
        << dt._cauHinh << "\n"
        << "Gia             : " << dt._gia << " VND";
    return os;
}

bool DienThoai::operator==(const DienThoai dt)
{
    if(_id == dt.getID()) return true;
    return false;
}

bool DienThoai::operator!=(const DienThoai dt)
{
    if(_id != dt.getID()) return true;
    return false;
}