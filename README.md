# 📱 Đồ án OOP: Quản Lý Điện Thoại (C++)

## 👥 Thành viên nhóm

| MSSV        | Họ và tên                 | Chức vụ
|-------------|---------------------------|-----------
| **23120189** | *Hoàng Quốc Việt*         |Thành viên
| **23120220** | *Trần Vũ Đình Chính*      |Nhóm trưởng
| **23120230** | *Nguyễn Thế Đạt*          |Thành viên

# Dự Án Quản Lý Điện Thoại
## Link GitHub
```bash
https://github.com/dinhchinh318/23120189_23120220_23120230.git
```

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

## Tiến độ hoàn thành
---

### Teamwork: Phân công và theo dõi tiến độ công việc,  biên bản họp nhóm
### UI/UX: Chính là điểm chức năng cũng như giao diện của chương trình.
✅ Đã hoàn thành giao diện cơ bản menu khi vào ứng dụng  
✅ Đã hoàn thành giao diện của các phần riêng biệt  
🔄 Đang nâng cấp phát triển hoàn thiện giao diện  
❌ Sắp phát triển các tiện ích trên ứng dụng bằng SFML

### Kiến trúc phần mềm + design pattern: 
✅ Đã hoàn thành các thao tác Thêm/Xoá/Cập nhật điện thoại  
✅ Đã hoàn thành tìm kiếm điện thoại theo ID  
🔄 Đang hoàn thiện chức năng sắp xếp theo giá, tên  
❌ Sắp phát triển chức năng sắp xếp theo tên, theo giá  
✅ Đã hoàn thanh lưu danh sách sản phẩm  
✅ Đã hoàn thành đọc dữ liệu từ database khi khởi động  
❌ Sắp phát triển thêm chức năng hoàn thiện Database
### Đảm bảo chất lượng: test / coding convention
🔄 Đang nghiên cứu thực hiện và kiểm thử
### Tài liệu mô tả kiến trúc phần mềm và các module:  
✅ Đã thực hiện mở port mới bằng file index.html tren docs của file doxygen
### Các chủ đề nâng cao: 
✅ Đã và đang nghiên cứu thêm về thư viện SFML cho UI-UX  
✅ Đã và đang phát triển thêm về SQL để lưu trữ và truy xuất

## 🛠️ Công cụ sử dụng
- Ngôn ngữ: **C++**
- Môi trường phát triển: **GitHub Codespaces**, **Visual Studio Code**
- Quản lý mã nguồn: **Git**, **GitHub**  
- Các thư viện ngoài: **SFML**  
- Cơ sở dữ liệu: **SQL Server**  
- Tools: **SSMS**  
---

## 🎯 Dự định thực hiện tiếp theo
### Dự đoán đã thực hiện được 40% yêu cầu và chức năng

- [ ] Thiết kế phát triển thêm nhiều chức năng hơn   
- [ ] Hoàn thiện thêm các chức năng chưa có  
- [ ] Nâng cấp giao diện người dùng console  
- [ ] Nâng cấp cơ sở dữ liệu   

---
