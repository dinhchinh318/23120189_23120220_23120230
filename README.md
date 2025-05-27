<div align="center">

<img src="Pictures/hcmuslogo.png" alt="HCMUS logo" width="110" style="margin-bottom:20px;" />

# 🏫<span style="color:#1363DF;"> <b>TRƯỜNG ĐẠI HỌC KHOA HỌC TỰ NHIÊN - ĐHQG TP.HCM</b> </span>
## 🖥️ <span style="color:#47B5FF;"> <b>KHOA CÔNG NGHỆ THÔNG TIN</b> </span>

<hr style="border: 1.5px solid #47B5FF; width:60%;" />

# 📄 <span style="color:#0A2647"> <b>BÁO CÁO ĐỒ ÁN</b> </span>
## 📱 <span style="color:#0A2647"> <b>Đề tài: Quản Lý Điện Thoại (OOP - C++)</b> </span>

<hr style="border: 1.5px solid #47B5FF; width:60%;" />

### <span style="color:#F86F03;"> <b>Môn học:</b> </span> Lập Trình Hướng Đối Tượng (OOP)  
### <span style="color:#F86F03;"> <b>Giảng viên hướng dẫn:</b> </span> TRẦN DUY QUANG

---

#### <span style="color:#00DFA2;"> <b>Nhóm sinh viên thực hiện:</b> </span>

<table align="center" border="1" cellpadding="8" cellspacing="0" style="border-collapse: collapse; min-width: 400px; font-size: 18px;">
  <tr bgcolor="#DFF6FF" style="color:#1363DF;">
    <th>STT</th>
    <th>MSSV</th>
    <th>Họ và tên</th>
    <th>Chức vụ</th>
  </tr>
  <tr align="center">
    <td>1</td>
    <td><b>23120189</b></td>
    <td>Hoàng Quốc Việt</td>
    <td>Thành viên</td>
  </tr>
  <tr align="center">
    <td>2</td>
    <td><b>23120220</b></td>
    <td><b>Trần Vũ Đình Chính</b></td>
    <td><b>Nhóm trưởng</b></td>
  </tr>
  <tr align="center">
    <td>3</td>
    <td><b>23120230</b></td>
    <td>Nguyễn Thế Đạt</td>
    <td>Thành viên</td>
  </tr>
</table>

---

<br>

**TP. Hồ Chí Minh, ngày 31 tháng 05 năm 2024**
</div>

## **I. Giới thiệu chung về đồ án**

### 1. 📱 Tên project:  **`Phone Management`**
#### 🎯 Mục tiêu của phần mềm

**Phone Management** là phần mềm quản lý điện thoại, cho phép người dùng:

- **Thêm, xóa, sửa** thông tin điện thoại
- **Tìm kiếm, lọc, sắp xếp** danh sách điện thoại
- **Hiển thị danh sách** điện thoại với giao diện trực quan, thân thiện
- **Kết nối và thao tác dữ liệu** với cơ sở dữ liệu SQL Server, đảm bảo lưu trữ và truy xuất hiệu quả

> Phần mềm hướng tới việc hỗ trợ các cửa hàng/cá nhân quản lý danh mục sản phẩm điện thoại một cách dễ dàng, hiện đại và chuyên nghiệp.

---
### 2. Thư mục `source/` – Cấu trúc & Vai trò các thành phần

Thư mục **source** chứa toàn bộ mã nguồn của project, được tổ chức thành các thư mục con theo chức năng như sau:

---

#### 2.1. Thư mục `App/`
**Vai trò:**  
Điều phối ứng dụng, quản lý vòng đời, chuyển đổi giữa các màn hình.

**Các lớp chính:**

- **App** (`App/app.h`, `App/app.cpp`):  
  Quản lý các màn hình chức năng (add, display, search, edit, delete, ...).  
  - Vòng lặp chính: nhận sự kiện, cập nhật, vẽ giao diện.
  - Chuyển đổi trạng thái màn hình qua enum `AppScreen`.

- **Button** (`App/Button.h`, `App/Button.cpp`):  
  Thành phần giao diện dùng chung cho các màn hình.  
  - Hỗ trợ theme, sự kiện nhấn, vẽ nút.

---

#### 2.2. Thư mục `FunctionScreen/`
**Vai trò:**  
Chứa các màn hình chức năng cụ thể, mỗi màn hình là một lớp riêng biệt.

**Các lớp chính:**

- `InitScreen`: Màn hình khởi động.
- `AddPhoneScreen`: Thêm điện thoại mới (`addScreen.h/cpp`).
- `DisplayListScreen`: Hiển thị danh sách điện thoại (`disScreen.h/cpp`).
- `DeleteScreen`: Xóa điện thoại (`delScreen.h/cpp`).
- `EditScreen`, `EditListScreen`, `EditExec`: Tìm, chọn, chỉnh sửa điện thoại (`editScreen.h/cpp`, ...).
- `SearchScreen`, `FindListScreen`: Tìm kiếm điện thoại (`searchScreen.h/cpp`, ...).

**Thành phần UI phụ trợ:**
- `InputBox`, `InputField`: Ô nhập liệu.
- `Dropdown`: Danh sách chọn.
- `Popup`: Thông báo nhanh.

**Đặc điểm:**
- Mỗi màn hình kế thừa từ `BaseScreen` (trong thư mục `Screen`).
- Mỗi màn hình tự quản lý thành phần UI, sự kiện, dữ liệu hiển thị.

---

#### 2.3. Thư mục `PhoneManagement/`
**Vai trò:**  
Quản lý dữ liệu, nghiệp vụ, truy xuất cơ sở dữ liệu.

**Các lớp/chức năng chính:**

- `Phone`: Đối tượng điện thoại (model).
- `PhoneManagement` (`PhoneManagement.h`):  
  - Quản lý danh sách điện thoại bằng danh sách liên kết.
  - Cung cấp các thao tác: thêm, xóa, sửa, tìm kiếm, lấy danh sách, duyệt iterator.
  - Kết nối và thao tác với SQL Server qua ODBC.
  - Hàm tiện ích: chuyển đổi chuỗi, lấy danh sách từ DB, lọc theo giá/hãng.
- `Iterator`: Cho phép duyệt danh sách như container STL.

---

#### 2.4. Thư mục `Screen/`
**Vai trò:**  
Định nghĩa các lớp giao diện nền tảng, dùng chung cho các màn hình chức năng.

**Các lớp chính:**
- `BaseScreen`: Lớp cơ sở cho tất cả các màn hình chức năng, định nghĩa interface chung (`pollEvent`, `update`, `draw`).
- `AppScreen` (`Screen/AppScreen.h`): Enum quản lý trạng thái/màn hình hiện tại của ứng dụng.

---


## **II. Phân công công việc**

<table>
  <tr>
    <th align="center" width="180">👤 Thành viên</th>
    <th align="center">📝 Đóng góp phần trăm</th>
  </tr>
  <tr>
    <td align="center" bgcolor="#DFF6FF"><b>Hoàng Quốc Việt</b><br><i>Thành viên</i></td>
    <td>
      <ul>
        <li>Thiết kế, phát triển giao diện chương trình (UI/UX)</li>
        <li>Xây dựng chức năng hiển thị, tìm kiếm, thêm, xóa, sửa điện thoại</li>
        <li>Tạo file <b>MakeFile</b> cho dự án</li>
        <li> Thiết kế Unit Test, Test Plan, Test Case, Test Report </li>
        <li> Thiết kế coding convention </li>
      </ul>
    </td>
  </tr>
  <tr>
    <td align="center" bgcolor="#F9F871"><b>Trần Vũ Đình Chính</b><br><i>Nhóm trưởng</i></td>
    <td>
      <ul>
        <li>Thiết kế các class chính, xây dựng kiến trúc phần mềm</li>
        <li>Thiết kế, phát triển giao diện chương trình (UI/UX)</li>
        <li>Định hướng, kiểm soát tiến độ phát triển</li>
        <li>Viết báo cáo, tài liệu dự án</li>
        <li>Kiểm thử, sửa lỗi tổng thể</li>
      </ul>
    </td>
  </tr>
  <tr>
    <td align="center" bgcolor="#FFD6EC"><b>Nguyễn Thế Đạt</b><br><i>Thành viên</i></td>
    <td>
      <ul>
        <li>Xây dựng, kết nối cơ sở dữ liệu (SQL Server/ODBC)</li>
        <li>Xử lý lưu trữ, truy xuất dữ liệu</li>
        <li>Tối ưu mã nguồn, kiểm thử chức năng</li>
        <li>Vẽ class diagram</li>
        <li>Quay video demo</li>
      </ul>
    </td>
  </tr>
</table>

---
## **III. Tỉ lệ đóng góp (%) của các thành viên**

<table>
  <tr>
    <th align="center" width="180">👤 Thành viên</th>
    <th align="center" width="180">📝 Đóng góp phần trăm</th>
    <th align="center" width="180"> Tỉ lệ điểm </th>
  </tr>
  <tr>
    <td align="center" bgcolor="#DFF6FF"><b>Hoàng Quốc Việt</b><br><i>Thành viên</i></td>
    <td>
      <ul>
        <li>100 %</li>
      </ul>
    </td>
    <td>
      <ul>
        <li>100 %</li>
      </ul>
    </td>
  </tr>
  <tr>
    <td align="center" bgcolor="#F9F871"><b>Trần Vũ Đình Chính</b><br><i>Nhóm trưởng</i></td>
    <td>
      <ul>
        <li>100 %</li>
      </ul>
    </td>
    <td>
      <ul>
        <li>100 %</li>
      </ul>
    </td>
  </tr>
  <tr>
    <td align="center" bgcolor="#FFD6EC"><b>Nguyễn Thế Đạt</b><br><i>Thành viên</i></td>
    <td>
      <ul>
        <li>100 %</li>
      </ul>
    </td>
    <td>
      <ul>
        <li>100 %</li>
      </ul>
    </td>
  </tr>
</table>

---

## **IV. 🚀 Hướng dẫn cài đặt môi trường & chạy chương trình**

### 1. Yêu cầu hệ thống

- **Hệ điều hành:** Windows / Linux / macOS
- **Trình biên dịch C++:** `g++` phiên bản 13 trở lên
- **Cơ sở dữ liệu:** SQL Server  
  - Đã tạo sẵn **database**: `PhoneManagement`
  - **Tài khoản đăng nhập:**  
    - Username: `sa`  
    - Password: `123`
- **Thư viện ngoài:**
  - [Boost.Locale](https://www.boost.org/doc/libs/release/libs/locale/)
  - [ODBC Driver 17 for SQL Server](https://learn.microsoft.com/en-us/sql/connect/odbc/download-odbc-driver-for-sql-server)
  - [SFML](https://www.sfml-dev.org/download.php) (để chạy giao diện nâng cao)

---

#### 🗄️ **Lưu ý chuẩn bị CSDL**

1. Cài đặt SQL Server, sau đó tạo một **database mới** tên là `PhoneManagement`.
2. Đảm bảo đã tạo tài khoản đăng nhập SQL Server:
   - **User:** `sa`
   - **Password:** `123`
3. (Tuỳ vào thiết kế) Nếu cần, tạo các bảng cần thiết theo hướng dẫn/SQL script đính kèm (hoặc hỏi nhóm trưởng).

#### **Tạo database và bảng**

Dưới đây là script mẫu tạo database và bảng điện thoại (PHONE) dành cho SQL Server:

```sql
-- Tạo database
CREATE DATABASE PhoneManagement;
GO

-- Sử dụng database
USE PhoneManagement;
GO

-- Tạo bảng PHONE
CREATE TABLE PHONE (
    ID INT PRIMARY KEY,
    NamePhone NVARCHAR(100),
    Manufacturer NVARCHAR(100),
    Price NVARCHAR(100),
    OperatingSystem NVARCHAR(100),
    CPU NVARCHAR(100),
    RAM INT,
    ROM INT,
    ScreenSize FLOAT,
    Pin INT
);
```
---
### 2. Các bước cài đặt

#### **Bước 1: Cài đặt trình biên dịch và các thư viện**

#### **A. Trên Windows**

1. **Cài MinGW-w64** để có `g++` 13 trở lên:  
   > [Tải tại đây](https://www.mingw-w64.org/downloads/)

2. **Cài ODBC Driver 17 for SQL Server:**  
   > [Tải tại đây](https://learn.microsoft.com/en-us/sql/connect/odbc/download-odbc-driver-for-sql-server)  
   Sau khi cài, kiểm tra bằng cách mở "ODBC Data Sources (64-bit)" → tab **Drivers** → xem có "ODBC Driver 17 for SQL Server".

   > Hướng dẫn video: [YouTube - ODBC](https://www.youtube.com/watch?v=61BzALfuvLQ)

3. **Cài Boost.Locale:**  
   > Có thể dùng [vcpkg](https://vcpkg.io/en/index.html), hoặc tải trực tiếp tại [boost.org](https://www.boost.org/users/download/).

4. **Cài SFML (nếu dùng giao diện nâng cao):**  
   [Tải tại đây](https://www.sfml-dev.org/download.php)  
   > Hướng dẫn video: [YouTube - Cài đặt SFML](https://www.youtube.com/watch?v=WoVoIhgutMU)

#### **B. Trên Linux (Ubuntu)**

```bash
$ sudo apt update
$ sudo apt install g++-13 libboost-locale-dev unixodbc-dev
$ sudo apt install libsfml-dev
```
---
### 3. Biên dịch chương trình
- **Hướng dẫn chạy chương trình trên Window**
```bash
$ git clone https://github.com/dinhchinh318/23120189_23120220_23120230.git  
$ cd 23120189_23120220_23120230  
$ mingw32-make
$ release/PhoneManagement.exe
```
- **Hướng dẫn chạy trên Linux (Utubun)**
```bash
$ git clone https://github.com/dinhchinh318/23120189_23120220_23120230.git  
$ cd 23120189_23120220_23120230 
$ make
$ ./release/PhoneManagement
```
### 4. Test chương trình
- **Hướng dẫn chạy chương trình trên Window**
```bash
$ git clone https://github.com/dinhchinh318/23120189_23120220_23120230.git  
$ cd 23120189_23120220_23120230  
$ mingw32-make test
```
- **Hướng dẫn chạy trên Linux (Utubun)**
```bash
$ git clone https://github.com/dinhchinh318/23120189_23120220_23120230.git  
$ cd 23120189_23120220_23120230 
$ make test
```
---

## **V. Cách thức đánh giá & mô tả đồ án**

### **1. Teamwork** (**15%**)
- **Phân công, biên bản họp nhóm:**  
  [Xem chi tiết biên bản họp nhóm tại đây](https://drive.google.com/drive/folders/188rYyFNcjnafmdN6ThSB7M4-VffFCYr0?usp=drive_link)  
- **Tiến độ:**  
  Xem chi tiết tại link github: [https://github.com/dinhchinh318/23120189_23120220_23120230.git](https://github.com/dinhchinh318/23120189_23120220_23120230.git)

### **2. UI/UX** (**20%**)
- **Chức năng cài đặt chuẩn OOP:**  
  - (Mô tả các chức năng chính đã dựng: thêm, sửa, xóa, tìm kiếm điện thoại, giao diện menu rõ ràng...)
- **Xem trực tiếp tại video demo** 
  > [Xem video tại đây](https://link-video-demo.com)

### **3. Kiến trúc phần mềm + design pattern** (**20%**)
#### **3.1. Tuân thủ nguyên lý OOP**

- **Đóng gói (Encapsulation):**
  - Dữ liệu và các phương thức xử lý được đóng gói trong từng lớp.
  - *Ví dụ:*  
    Lớp `PhoneManagement` quản lý danh sách điện thoại qua các phương thức như `Push_back`, `Remove`, `findByID`, ...  
    Các thuộc tính như `_pHead`, `_pTail`, `_numberOfPhones` được khai báo `private`, chỉ truy cập qua phương thức công khai.

- **Kế thừa (Inheritance):**
  - Các màn hình chức năng như `DisplayListScreen`, `AddPhoneScreen`, ... kế thừa từ lớp cơ sở `BaseScreen` để tái sử dụng các thuộc tính và phương thức UI chung.

- **Đa hình (Polymorphism):**
  - Sử dụng các phương thức ảo (`virtual`) trong lớp cơ sở để lớp con override hành vi riêng (vd: `draw`, `pollEvent`, `update`).

- **Trừu tượng hóa (Abstraction):**
  - Các lớp chỉ cung cấp các phương thức cần thiết cho bên ngoài, ẩn đi chi tiết cài đặt bên trong.
  - *Ví dụ:*  
    Người dùng chỉ cần gọi `getPhonesFromDatabase()` mà không cần biết chi tiết truy vấn SQL.

---

#### **3.2. Tuân thủ nguyên lý SOLID**

- **S – Single Responsibility Principle:**  
  Mỗi lớp chỉ đảm nhận một nhiệm vụ duy nhất.  
  *Ví dụ:*  
  `PhoneManagement` quản lý dữ liệu điện thoại; các màn hình chỉ lo giao diện và sự kiện từng chức năng; `App` chỉ điều phối màn hình.

- **O – Open/Closed Principle:**  
  Các lớp mở rộng mà không cần sửa mã nguồn cũ.  
  *Ví dụ:*  
  Thêm màn hình chức năng mới chỉ cần kế thừa `BaseScreen`, không cần sửa lớp cũ.

- **L – Liskov Substitution Principle:**  
  Các lớp con có thể thay thế lớp cha mà không làm thay đổi tính đúng đắn chương trình.  
  *Ví dụ:*  
  Các màn hình kế thừa `BaseScreen` đều có thể dùng thay thế nhau trong `App`.

- **I – Interface Segregation Principle:**  
  Các lớp chỉ cần triển khai giao diện chúng thực sự sử dụng.  
  *Ví dụ:*  
  `BaseScreen` định nghĩa phương thức chung (`draw`, `pollEvent`, `update`), các màn hình con chỉ override phương thức phù hợp.

- **D – Dependency Inversion Principle:**  
  Module cấp cao không phụ thuộc trực tiếp module cấp thấp mà qua abstraction.  
  *Ví dụ:*  
  Giao diện gọi các hàm trừu tượng của `PhoneManagement` mà không quan tâm chi tiết DB.

---

#### **3.3. Áp dụng Design Pattern**

- **Iterator Pattern:**  
  Lớp `PhoneManagement` xây dựng lớp lồng `Iterator` giúp duyệt danh sách điện thoại như container STL.

- **MVC Pattern (Model-View-Controller):**  
  - **Model:** `Phone`, `PhoneManagement`
  - **View:** Các màn hình trong `FunctionScreen`, thành phần UI
  - **Controller:** Lớp `App` điều phối chuyển đổi màn hình, nhận sự kiện tổng thể

- **Factory Pattern:**  
  Hàm tĩnh `CreateNode` trong `PhoneManagement` để tạo node mới cho danh sách liên kết.

- **Singleton Pattern:**  
  Biến kết nối CSDL (chuỗi kết nối SQL) dùng chung, đảm bảo chỉ có một kết nối trong chương trình.

---

#### **3.4. Luồng hoạt động của chương trình**

1. **Khởi động chương trình**
    - Tạo đối tượng `App`, kết nối CSDL qua `PhoneManagement`.
2. **Hiển thị màn hình chính**
    - Giao diện menu (SFML), chọn chức năng: Thêm, Xem, Sửa, Xóa, Tìm kiếm.
3. **Chọn chức năng**
    - `App` chuyển sang màn hình tương ứng trong `FunctionScreen`.
4. **Xử lý nghiệp vụ**
    - Nhận dữ liệu người dùng qua UI (InputBox, Button), gửi yêu cầu tới `PhoneManagement`.
5. **Tương tác cơ sở dữ liệu**
    - `PhoneManagement` truy vấn SQL Server, trả kết quả về màn hình chức năng.
6. **Hiển thị kết quả**
    - Giao diện cập nhật danh sách/thông báo.
7. **Chuyển đổi/thoát**
    - Người dùng quay về menu hoặc thoát; chương trình giải phóng tài nguyên, đóng kết nối DB.

---

#### **3.5. Định hướng mở rộng & bảo trì**

- **Dễ mở rộng:**  
  Kiến trúc phân lớp, mỗi chức năng một màn hình. Thêm chức năng mới dễ dàng kế thừa từ `BaseScreen`.

- **Dễ bảo trì:**  
  Lớp đóng gói tốt, thay đổi không ảnh hưởng phần khác. Tập trung thao tác DB tại `PhoneManagement` giúp dễ nâng cấp/đổi DB.

- **Tái sử dụng:**  
  Thành phần UI (Button, InputBox, ...) thiết kế dùng chung, hàm xử lý dữ liệu dùng lại nhiều nơi.

- **Hỗ trợ tài liệu hóa, kiểm thử:**  
  Sử dụng Doxygen sinh tài liệu tự động, có thể bổ sung unit test các hàm nghiệp vụ.

- **Định hướng nâng cấp:**  
  Dễ mở rộng đa nền tảng (Linux, Mac nhờ SFML/C++ chuẩn), tích hợp thêm module xuất báo cáo, đồng bộ dữ liệu, đa ngôn ngữ...

---

### 4. **Đảm bảo chất lượng** (**20%**)
- **Unit Test**  
  > [Bấm vào để theo dõi các unit test](https://drive.google.com/drive/folders/1dqdo7ai-gtDjkHaNJfU6jaNoNwd73Tr8?usp=sharing)
- **Coding Convention**  
  > 

### 5. **Tài liệu mô tả kiến trúc phần mềm và các module** (**10%**)
- **File tài liệu** (Doxygen/Markdown):  
  > [Doxyfile](https://github.com/dinhchinh318/23120189_23120220_23120230/blob/main/Doxyfile)  
  Từ thư mục docs -> index.html (live server)
- Diagram:  
<img src="Pictures/diagram.png" alt="Diagram" width="1500" style="margin-bottom:20px;" />


### 6. **Chủ đề nâng cao** (**15%**)

Dự án đã triển khai và nghiên cứu một số chủ đề nâng cao nhằm tăng tính thực tiễn, khả năng mở rộng, chuyên nghiệp hóa phần mềm, cụ thể:

---

- **1. Kết nối và thao tác với Cơ sở dữ liệu SQL Server qua ODBC**  
  - Ứng dụng sử dụng ODBC driver để kết nối, lưu trữ và truy xuất dữ liệu điện thoại trong SQL Server.
  - Mọi thao tác thêm, xóa, sửa, tìm kiếm, duyệt danh sách đều được thực hiện trực tiếp với cơ sở dữ liệu thay vì file truyền thống.
  - 🔗 **Xem mã nguồn thực tế:**  
    - [source/PhoneManagement/PhoneManagement.h](https://github.com/dinhchinh318/23120189_23120220_23120230/blob/main/source/PhoneManagement/PhoneManagement.h)  
    - [source/PhoneManagement/PhoneManagement.cpp](https://github.com/dinhchinh318/23120189_23120220_23120230/blob/main/source/PhoneManagement/PhoneManagement.cpp)

---

- **2. Xây dựng giao diện người dùng đồ họa với thư viện SFML**  
  - Dự án sử dụng thư viện SFML để xây dựng giao diện trực quan, thân thiện với người dùng: menu chính, nút bấm, ô nhập liệu, bảng dữ liệu…
  - Các thành phần giao diện được tách thành các class riêng biệt (Button, InputBox, Popup, Dropdown...), dễ tái sử dụng.
  - 🔗 **Minh chứng:**  
    - [source/App/Button.h](https://github.com/dinhchinh318/23120189_23120220_23120230/blob/main/source/App/Button.h)  
    - [source/FunctionScreen/addScreen.cpp](https://github.com/dinhchinh318/23120189_23120220_23120230/blob/main/source/FunctionScreen/addScreen.cpp)

---

- **3. Ứng dụng Iterator, Design Pattern hiện đại**  
  - Tự xây dựng Iterator cho danh sách điện thoại, giúp việc duyệt và thao tác dữ liệu linh hoạt, dễ tích hợp với C++ STL.
  - Áp dụng các pattern như Factory (tạo Node), Singleton (kết nối CSDL dùng chung), MVC (phân tầng Model, View, Controller) giúp code dễ bảo trì, dễ mở rộng.
  - 🔗 **Xem ví dụ Iterator:**  
    - [source/PhoneManagement/PhoneManagement.h - class Iterator](https://github.com/dinhchinh318/23120189_23120220_23120230/blob/main/source/PhoneManagement/PhoneManagement.h)

---

- **4. Quản lý, kiểm thử và tài liệu hóa mã nguồn với Doxygen**  
  - Dự án đã bổ sung file cấu hình Doxygen và viết chú thích chuẩn giúp tự động sinh tài liệu phần mềm.
  - Thuận tiện kiểm thử, bảo trì, hỗ trợ thành viên mới dễ tiếp cận hệ thống.
  - 🔗 **Minh chứng:**  
    - [Doxyfile](https://github.com/dinhchinh318/23120189_23120220_23120230/blob/main/Doxyfile)  
    - [README.md](https://github.com/dinhchinh318/23120189_23120220_23120230/blob/main/README.md)

---

- **5. Định hướng nâng cấp**  
  - Kiến trúc project, giao diện và class được tổ chức theo hướng mở (Open/Closed), thuận tiện bổ sung các chức năng mới như: xuất file Excel, thống kê, phân quyền, đa ngôn ngữ, hoặc chuyển sang các DBMS khác (MySQL, SQLite...) mà không ảnh hưởng code cũ.
  - Đã tách biệt rõ module giao diện và xử lý dữ liệu.

---

> **Nhờ các chủ đề nâng cao trên, sản phẩm đáp ứng tốt yêu cầu học thuật, đồng thời có khả năng ứng dụng thực tế, dễ mở rộng và bảo trì.**


---

## **VI. 🎬 Video Demo**

> 📺 **Link video demo:**  
> [Xem video tại đây](https://link-video-demo.com)

**Nội dung video demo:**
- Trình diễn giao diện chính và các chức năng nổi bật của chương trình.
- Các luồng sự kiện tiêu biểu:
  - ➕ Thêm điện thoại mới
  - ✏️ Sửa thông tin điện thoại
  - ❌ Xóa điện thoại
  - 🔍 Tìm kiếm điện thoại
  - 📋 Hiển thị danh sách điện thoại

> 📝 *Video demo giúp giảng viên có cái nhìn trực quan về sản phẩm cũng như khả năng vận hành thực tế của nhóm.*

---