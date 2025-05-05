# 📱 Đồ án OOP: Quản Lý Điện Thoại (C++)

## 👥 Thành viên nhóm

| MSSV        | Họ và tên                 | Chức vụ
|-------------|---------------------------|-----------
| **23120189** | *Hoàng Quốc Việt*         |Thành viên
| **23120220** | *Trần Vũ Đình Chính*      |Nhóm trưởng
| **23120230** | *Nguyễn Thế Đạt*          |Thành viên

# Dự Án Quản Lý Điện Thoại

## Công Việc Đã Thực Hiện
- **Trần Vũ Đình Chính**:  
  - Thiết kế các class chính  
  - Nghiên cứu xây dựng cấu trúc thư mục và lớp hợp lí  
  - Phát triển chức năng ứng dụng
  - Tạo báo cáo    
  - Kiểm thử và sửa lỗi phần mềm  

- **Hoàng Quốc Việt**:  
  - Nghiên cứu phát triển giao diện  
  - Phát triển chức năng ứng dụng  
  - Phát triển chức năng tìm kiếm, hiển thị danh sách điện thoại, thêm, xóa , sửa điện thoại  
  - Tạo file CMAKE  

- **Nguyễn Thế Đạt**:  
  - Phát triển chức năng thêm, sửa, xoá, tìm kiếm điện thoại
  - Phát triển chức năng kết nối cơ sở dữ liệu  
  - Xây dựng các lớp xử lý dữ liệu  
  - Kiểm thử và tối ưu hóa mã nguồn  
  - Quay demo  

## Tỉ Lệ Đóng Góp

| Thành Viên       | Tỉ Lệ Đóng Góp (%) |
|------------------|---------------------|
| Trần Vũ Đình Chính    | 100%           |
| Hoàng Quốc Việt       | 100%           |
| Nguyễn Thế Đạt        | 100%           |

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
│ ├── *.h  
│ ├── *.cpp  
├── release/  
├── Makefile  
├── SFML  
├── UI-UX  
├── Demo  
└── README.md  
```
> **Lưu ý:** Tất cả các file `.cpp` của bạn phải nằm trong `source`.

## ⚙️ Cách biên dịch

Mở terminal (cmd hoặc bash) và di chuyển đến thư mục gốc của project:

```bash
$ cd 23120189-23120220-23120230
$ g++-13 -g source/*.cpp -lboost_locale -lodbc -o release/out
```
**Hoặc**
```bash
$ cd 23120189-23120220-23120230
$ make
$ release/out
$ make clean
```
---

## 📝 Mô tả dự án

Dự án xây dựng chương trình **quản lý điện thoại** bằng ngôn ngữ C++, áp dụng lập trình hướng đối tượng (OOP).  
Hệ thống mô phỏng hoạt động cơ bản trong một cửa hàng điện thoại:

- Quản lý danh sách điện thoại đang bán

---

## 💡 Các chức năng chính

### 📦 Quản lý sản phẩm (Điện thoại)
- Thêm/Xoá/Cập nhật điện thoại
- Tìm kiếm điện thoại theo tên, hãng
- Sắp xếp theo giá, tên

### 💾 File và lưu trữ
- Lưu danh sách sản phẩm
- Đọc dữ liệu từ file khi khởi động

---

## 🎯 Dự định thực hiện

- [x] Thiết kế lớp `DienThoai` cơ bản   
- [x] Lớp `QuanLyDienThoai`
- [x] Giao diện người dùng console  
- [x] Lưu và đọc dữ liệu từ file  
- [x] Viết báo cáo và hướng dẫn sử dụng  

---

## Tiến độ hoàn thành

### 📦 Quản lý sản phẩm (Điện thoại)
✅ Đã hoàn thành các thao tác Thêm/Xoá/Cập nhật điện thoại  
✅ Đã hoàn thành tìm kiếm điện thoại theo ID  
🔄 Đang hoàn thiện chức năng sắp xếp theo giá, tên  
❌ Sắp phát triển chức năng sắp xếp theo tên, theo giá  

### 💾 File và lưu trữ
✅ Đã hoàn thanh lưu danh sách sản phẩm  
✅ Đã hoàn thành đọc dữ liệu từ database khi khởi động  
❌ Sắp phát triển thêm chức năng hoàn thiện Database

### Giao diện
✅ Đã hoàn thành giao diện cơ bản menu khi vào ứng dụng  
✅ Đã hoàn thành giao diện của các phần riêng biệt  
🔄 Đang nâng cấp phát triển hoàn thiện giao diện  
❌ Sắp phát triển các tiện ích trên ứng dụng bằng SFML

## 🛠️ Công cụ sử dụng
- Ngôn ngữ: **C++**
- Môi trường phát triển: **GitHub Codespaces**, **Visual Studio Code**
- Quản lý mã nguồn: **Git**, **GitHub**
- Các thư viện ngoài: **SFML**
- Cơ sở dữ liệu: **SQL Server**
- Tools: **SSMS**
---

## 🎯 Dự định thực hiện tiếp theo

- [ ] Thiết kế phát triển thêm nhiều chức năng hơn   
- [ ] Hoàn thiện thêm các chức năng chưa có  
- [ ] Nâng cấp giao diện người dùng console  
- [ ] Nâng cấp cơ sở dữ liệu   

---
