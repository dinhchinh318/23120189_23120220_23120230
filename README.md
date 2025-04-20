# 📱 Đồ án OOP: Quản Lý Bán Hàng Điện Thoại (C++)

## 👥 Thành viên nhóm

| MSSV        | Họ và tên                 | Chức vụ
|-------------|---------------------------|-----------
| **23120189** | *Hoàng Quốc Việt*         |Thành viên
| **23120220** | *Trần Vũ Đình Chính*      |Nhóm trưởng
| **23120230** | *Nguyễn Thế Đạt*          |Thành viên

# 📱 Quản Lý Điện Thoại - Hướng Dẫn Biên Dịch và Chạy Chương Trình

## 📦 Yêu cầu

- Trình biên dịch **g++ version 13** hoặc mới hơn.
- Hệ điều hành: Windows/Linux/macOS.
- Đã cài đặt `g++-13` và có thể gọi từ terminal.

## 🗂️ Cấu trúc thư mục dự án
```bash
project/   
├── source/  
│ ├── main.cpp  
│ ├── src/  
│ │ ├── *.cpp   
│ ├── lib/  
│ │ ├── *.cpp  
├── release/  
└── README.md  
```
> **Lưu ý:** Tất cả các file `.cpp` của bạn phải nằm trong `source/src/` và `source/lib/`.

## ⚙️ Cách biên dịch

Mở terminal (cmd hoặc bash) và di chuyển đến thư mục gốc của project:

```bash
cd đường_dẫn_đến_thư_mục_project
g++-13 -std=c++2b -g source/main.cpp source/src/*.cpp source/lib/*.cpp -o release/out
```
---

## 📝 Mô tả dự án

Dự án xây dựng chương trình **quản lý bán hàng điện thoại** bằng ngôn ngữ C++, áp dụng lập trình hướng đối tượng (OOP).  
Hệ thống mô phỏng hoạt động cơ bản trong một cửa hàng bán điện thoại:

- Quản lý danh sách điện thoại đang bán
- Quản lý khách hàng
- Quản lý đơn hàng và xuất hóa đơn

---

## 💡 Các chức năng chính

### 📦 Quản lý sản phẩm (Điện thoại)
- Thêm/Xoá/Cập nhật điện thoại
- Tìm kiếm điện thoại theo tên, hãng
- Sắp xếp theo giá, tên

### 👤 Quản lý khách hàng
- Thêm khách hàng mới
- Cập nhật, xoá thông tin khách hàng
- Tìm kiếm khách hàng theo tên/SĐT

### 🧾 Quản lý đơn hàng / bán hàng
- Tạo đơn hàng mới (nhiều sản phẩm)
- Tính tổng tiền, xuất hóa đơn
- Quản lý danh sách đơn hàng theo khách hàng

### 💾 File và lưu trữ
- Lưu danh sách sản phẩm, khách hàng, đơn hàng vào file
- Đọc dữ liệu từ file khi khởi động

## 🛠️ Công nghệ sử dụng
- Ngôn ngữ: **C++**
- Môi trường phát triển: **GitHub Codespaces**, **Visual Studio Code**
- Quản lý mã nguồn: **Git**, **GitHub**
---

## 🎯 Dự định thực hiện

- [x] Thiết kế lớp `DienThoai` cơ bản  
- [x] Thiết kế lớp `KhachHang`  
- [ ] Thiết kế lớp `DonHang` + `ChiTietDonHang`  
- [ ] Lớp `QuanLyDienThoai`, `QuanLyKhachHang`, `QuanLyDonHang`  
- [ ] Giao diện người dùng console  
- [ ] Lưu và đọc dữ liệu từ file  
- [ ] Viết báo cáo và hướng dẫn sử dụng  

---
g++-13 -std=c++2b -g source/main.cpp source/models/*.cpp source/managers/*.cpp source/lib/*.cpp -o release/out
