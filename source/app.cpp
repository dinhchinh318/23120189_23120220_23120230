#include "app.h"
#include "WindowState.hpp"
#include "PhoneManager.h"

void runApp()
{
    PhoneManager game;
    game.initWindow();
            
    while (game.isWindowOpen()) {
        // process state
        game.clearScreen();
        /* game.pollEvents();
        game.update();
        game.draw(); */
        game.getRenderWindow().display();
    }
    // QuanLyDienThoai ql;
    // int luaChon;

    // do {
    //     cout << "\n=== MENU QUẢN LÝ ĐIỆN THOẠI ===\n";
    //     cout << "1. Thêm điện thoại\n";
    //     cout << "2. Hiển thị danh sách\n";
    //     cout << "3. Tìm kiếm theo tên\n";
    //     cout << "4. Xóa theo ID\n";
    //     cout << "0. Thoát\n";
    //     cout << "Chọn: ";
    //     cin >> luaChon;

    //     if (luaChon == 1) 
    //     {
    //         DienThoai dtTemp;
    //         dtTemp.nhapDuLieu();
    //         ql.Push_back(dtTemp);
    //     } 
    //     else if (luaChon == 2) 
    //     {
    //         cout << ql << endl;
    //     } 
    //     else if (luaChon == 3) 
    //     {
    //         string key;
    //         cout << "Nhập tên hoặc ID cần tìm: ";
    //         cin.ignore(); 
    //         getline(cin, key);
    //         DienThoai dt = ql.TimKiem(key);
    //         if (dt.getID() != 0) {
    //             cout << "Điện thoại tìm thấy:\n" << dt << endl;
    //         } else {
    //             cout << "Không tìm thấy điện thoại với tên hoặc ID: " << key << endl;
    //         }
    //     } 
    //     // else if (luaChon == 4) 
    //     // {
    //     //     int id;
    //     //     cout << "Nhập ID cần xóa: ";
    //     //     cin >> id;
    //     //     ql.xoaTheoID(id);
    //     // }
    // } while (luaChon != 0);

}