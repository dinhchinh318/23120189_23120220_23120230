#include "app.h"

void runApp()
{
    SQLHENV hEnv;
    SQLHDBC hDbc;

    if (!connectToSQL(hEnv, hDbc)) {
        //return -1;
        return;
    }

    QuanLyDienThoai ql;
    int choice;
    do {
        cout << "\n=== PHONE MANAGEMENT MENU ===\n";
        cout << "1. Add phone\n";
        cout << "2. Display phone list\n";
        cout << "3. Search by name\n";
        cout << "4. Delete by ID\n";
        cout << "5. Edit phone information\n";
        cout << "0. Exit\n";
        cout << "Select an option: ";
        cin >> choice;

        if (choice == 1)
        {
            DienThoai dtTemp;

            /*int id = nhapSoNguyen("Nhap ID dien thoai: ");
            dtTemp.setID(id);*/

            dtTemp.nhapDuLieu();       // Nhập các thông tin còn lại
            dtTemp.insertToDB(hDbc);   // Lưu vào CSDL
        }
        else if (choice == 2)
        {
            // cout << ql << endl;

             ql.LayDanhSachDienThoai(hDbc);  // Gọi hàm lấy danh sách điện thoại từ CSDL
             cout << ql << endl;

            //ql.XuatDanhSachDienThoai(hDbc);  // Gọi hàm xuất danh sách điện thoại
            // cout << "helooo";

            // cout << ql << endl;
            // ql.XuatDanhSachDienThoai(hDbc);  // Gọi hàm xuất danh sách điện thoại
        }
        else if (choice == 3)
        {
            string key;
            cout << "Enter name or ID to search: ";
            cin.ignore(); // Loại bỏ ký tự '\n' còn lại trong bộ đệm
            getline(cin, key);  // Nhập tên hoặc ID cần tìm

            // Kiểm tra xem key có phải là một số không (ID)
            bool isNumber = !key.empty() && all_of(key.begin(), key.end(), ::isdigit);

            DienThoai* dt = nullptr;  // Khởi tạo con trỏ

            // Nếu key là số, tìm theo ID
            if (isNumber) {
                int id = stoi(key);  // Chuyển key sang số nguyên (ID)
                dt = ql.TimKiemTheoID(hDbc, id);  // Gọi hàm tìm kiếm theo ID
            }
            else {
                // Nếu key không phải số, tìm theo tên
                dt = ql.TimKiemTheoTen(hDbc, key);  // Gọi hàm tìm kiếm theo tên
            }

            if (dt != nullptr && dt->getID() != 0) {  // Kiểm tra nếu điện thoại tìm thấy
                cout << "Phone found:\n" << *dt << endl;  // In đối tượng DienThoai
            }
            else {
                cout << "No phone found with name or ID: " << key << endl;
            }
        }
        else if (choice == 4)
        {
            int id;
            cout << "Enter ID to delete: ";
            cin >> id;
            ql.XoaDienThoaiTheoID(hDbc, id);  // Gọi hàm xóa theo ID
        }
        else if (choice == 5)
        {
            int id;
            cout << "Enter ID to edit: ";
            cin >> id;
            DienThoai* dt = ql.TimKiemTheoID(hDbc, id);  // Tìm điện thoại theo ID
            if (dt != nullptr && dt->getID() != 0) {  // Kiểm tra nếu điện thoại tìm thấy
                cout << "Phone found:\n" << *dt << endl;  // In đối tượng DienThoai
                // Nhập thông tin mới
                cout << "Enter new information:\n";
                /*dt->nhapDuLieu();*/
                // Chỉnh sửa thông tin trong CSDL
                ql.ChinhSuaThongTinDienThoai(hDbc, id);  // Gọi hàm chỉnh sửa thông tin
            }
            else {
                cout << "No phone found with ID: " << id << endl;
            }
        }
    } while (choice != 0);


}