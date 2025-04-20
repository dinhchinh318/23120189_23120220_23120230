#include "DienThoai.h"

// Định nghĩa operator<< để xuất thông tin cấu hình
ostream& operator<<(ostream& os, const CauHinh& ch) {
    os << "He dieu hanh   : " << ch.heDieuHanh << "\n"
       << "CPU            : " << ch.cpu << "\n"
       << "RAM            : " << ch.ram << " GB\n"
       << "ROM            : " << ch.rom << " GB\n"
       << "Man hinh       : " << ch.kichThuocManHinh << " inch\n"
       << "Pin            : " << ch.dungLuongPin << " mAh";
    return os;
}

ostream& operator<<(ostream& os, const DienThoai dt)
{
    os << dt._id << '\n' << dt._hang << '\n' << dt._ten << '\n'
        << dt._cauHinh << '\n' << dt._gia;
    return os;
}