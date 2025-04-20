#include "lib/lib.h"

int main() {
    QuanLyDienThoai ql;
    int luaChon;

    do {
        cout << "\n=== MENU QUẢN LÝ ĐIỆN THOẠI ===\n";
        cout << "1. Thêm điện thoại\n";
        cout << "2. Hiển thị danh sách\n";
        cout << "3. Tìm kiếm theo tên\n";
        cout << "4. Xóa theo ID\n";
        cout << "0. Thoát\n";
        cout << "Chọn: ";
        cin >> luaChon;

        if (luaChon == 1) 
        {
            DienThoai dtTemp;
            dtTemp.nhapDuLieu();
            ql.Push_back(dtTemp);
        } 
        else if (luaChon == 2) 
        {
            cout << ql << endl;
        } 
        // else if (luaChon == 3) 
        // {
        //     string tuKhoa;
        //     cin.ignore();
        //     cout << "Nhập từ khóa tìm kiếm: ";
        //     getline(cin, tuKhoa);
        //     ql.timKiemTheoTen(tuKhoa);
        // } 
        // else if (luaChon == 4) 
        // {
        //     int id;
        //     cout << "Nhập ID cần xóa: ";
        //     cin >> id;
        //     ql.xoaTheoID(id);
        // }
    } while (luaChon != 0);

    cout << "👋 Tạm biệt!\n";

    exitProgram();

    return 0;
}
