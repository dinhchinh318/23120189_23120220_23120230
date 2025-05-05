#include "DienThoai.h"

void DienThoai::nhapDuLieu() {
	int id = nhapSoNguyen("Nhap ID dien thoai: ");
	_id = id;

	cout << "Nhap ten dien thoai: ";
	getline(cin, _ten);

	cout << "Nhap hang san xuat: ";
	getline(cin, _hang);

	cout << "Nhap he dieu hanh: ";
	getline(cin, _cauHinh.heDieuHanh);

	cout << "Nhap CPU: ";
	getline(cin, _cauHinh.cpu);

	_cauHinh.ram = nhapSoNguyen("Nhap RAM (GB): ");
	_cauHinh.rom = nhapSoNguyen("Nhap ROM (GB): ");
	_cauHinh.dungLuongPin = nhapSoNguyen("Nhap dung luong pin (mAh): ");
	_cauHinh.kichThuocManHinh = nhapSoNguyen("Nhap kich thuoc man hinh (inch): ");

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
	: _id(0), _ten(""), _hang(""), _cauHinh(), _gia("0") {
}

DienThoai::DienThoai(const int id, const string ten, const string hang, const CauHinh cauHinh, string gia)
	: _id(0), _ten(ten), _hang(hang), _cauHinh(cauHinh), _gia(gia) {
}

DienThoai::~DienThoai()
{
	// Destructor
}


ostream& operator<<(ostream& os, const DienThoai dt)
{
	os << "ID              : " << dt._id << "\n"
		<< "Hang            : " << dt._hang << "\n"
		<< "Ten             : " << dt._ten << "\n"
		<< dt._cauHinh << "\n"
		//<< "So luong        : " << dt._soLuong << "\n"
		<< "Gia             : " << dt._gia << " VND";

	return os;
}

bool DienThoai::operator==(const DienThoai dt)
{
	if (_id == dt.getID()) return true;
	return false;
}

bool DienThoai::operator!=(const DienThoai dt)
{
	if (_id != dt.getID()) return true;
	return false;
}

void DienThoai::insertToDB(SQLHDBC db) {
	SQLHSTMT stmt;

	SQLRETURN ret;

	// Kiểm tra xem ID có tồn tại hay không
	std::wstring checkQuery = L"SELECT COUNT(*) FROM DIENTHOAI WHERE ID = " + std::to_wstring(_id);
	SQLAllocHandle(SQL_HANDLE_STMT, db, &stmt);

	ret = SQLExecDirectW(stmt, (SQLWCHAR*)checkQuery.c_str(), SQL_NTS);

	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
		SQLINTEGER count;
		SQLBindCol(stmt, 1, SQL_C_SLONG, &count, 0, nullptr);
		ret = SQLFetch(stmt);
		cout << "Count: " << count << endl; // Debugging line
		if (count > 0) {
			cout << "ID da ton tai. \n";
			//std::wcout << L"⚠ ID điện thoại đã tồn tại (PRIMARY KEY trùng lặp).\n" << std::endl;
			SQLFreeHandle(SQL_HANDLE_STMT, stmt);
			return; // Không thực hiện insert
		}
	}

	SQLFreeHandle(SQL_HANDLE_STMT, stmt);  // Giải phóng stmt sau khi kiểm tra

	// Nếu ID không tồn tại, tiếp tục thực hiện insert
	SQLAllocHandle(SQL_HANDLE_STMT, db, &stmt);

	std::wstring query = L"INSERT INTO DIENTHOAI(ID, Ten, Hang, Gia, HeDieuHanh, CPU, RAM, ROM, KichThuocManHinh, DungLuongPin) VALUES ("
		+ std::to_wstring(_id) + L", N'"
		+ std::wstring(_ten.begin(), _ten.end()) + L"', N'"
		+ std::wstring(_hang.begin(), _hang.end()) + L"', "
		+ std::to_wstring(std::stof(_gia)) + L", N'"  // Convert _gia string to float
		+ std::wstring(_cauHinh.heDieuHanh.begin(), _cauHinh.heDieuHanh.end()) + L"', N'"
		+ std::wstring(_cauHinh.cpu.begin(), _cauHinh.cpu.end()) + L"', "
		+ std::to_wstring(_cauHinh.ram) + L", "
		+ std::to_wstring(_cauHinh.rom) + L", "
		+ std::to_wstring(_cauHinh.kichThuocManHinh) + L", "
		+ std::to_wstring(_cauHinh.dungLuongPin) + L")";
	ret = SQLExecDirectW(stmt, (SQLWCHAR*)query.c_str(), SQL_NTS);

	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
		cout << "Da luu dien thoai thanh cong!\n" << std::endl;
	}
	else {
		std::cout << "❌ Lỗi khi lưu vào CSDL!\n" << std::endl;

		SQLWCHAR sqlState[6];
		SQLINTEGER nativeError;
		SQLWCHAR messageText[256];
		SQLSMALLINT textLength;

		int i = 1;
		while (SQLGetDiagRecW(SQL_HANDLE_STMT, stmt, i, sqlState, &nativeError, messageText, sizeof(messageText) / sizeof(SQLWCHAR), &textLength) == SQL_SUCCESS) {
			std::wcout << L"[Lỗi " << i << L"] SQLSTATE: " << sqlState << std::endl;
			std::wcout << L"Mã lỗi: " << nativeError << std::endl;
			std::wcout << L"Thông báo: " << messageText << std::endl;
			i++;
		}

		// Thực thi truy vấn
		if (SQLExecDirectW(stmt, (SQLWCHAR*)query.c_str(), SQL_NTS) == SQL_SUCCESS) {
			std::cout << "Da lu thong tin dien thoai thanh cong!\n";
		}
		else {
			std::cout << "Loi khi luu vao CSDL!\n";

		}

		SQLFreeHandle(SQL_HANDLE_STMT, stmt);
	}
}