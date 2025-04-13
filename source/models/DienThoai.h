#ifndef _DIEN_THOAI_H_
#define _DIEN_THOAI_H_

#include "../lib/lib.cpp"


class DienThoai 
{
    private:
        std::string maSP, tenSP, hang;
        double gia;
    public:
        virtual void nhap();
        virtual void xuat();
        double getGia() const;
        std::string getMaSP() const;
        virtual ~DienThoai() {}
};

class quanlidt : public DienThoai 
{
    private:
        int soluong;
};
#endif