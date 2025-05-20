#include "Phone.h"

// string priceStandardize(string& price) {
// 	string digits;
// 	for (char c : price) {
// 		if (isdigit(c)) {
// 			digits += c;
// 		}
// 	}

// 	string result;
// 	int count = 0;

// 	for (int i = digits.length() - 1; i >= 0; i--) {
// 		result.push_back(digits[i]);
// 		count++;
// 		if (count % 3 == 0 && i != 0) {
// 			result.push_back('.');
// 		}
// 	}

// 	reverse(result.begin(), result.end());

// 	return result;
// }

string priceStandardize(const string& price) {
	string digits;
	for (char c : price) {
		if (isdigit(c)) digits += c;
	}

	int len = digits.length();
	if (len == 0) return "0";

	string result;
	int mod = len % 3;
	if (mod > 0) result = digits.substr(0, mod);

	for (int i = mod; i < len; i += 3) {
		if (!result.empty()) result += ".";
		result += digits.substr(i, 3);
	}

	return result;
}

int inputIntegerNumber(const std::string& notice) {
	int number;
	while (true) {
		std::cout << notice;
		std::cin >> number;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cout << "Error: Please input corret value!\n";
		}
		else {
			std::cin.ignore(1000, '\n');
			return number;
		}
	}
}

// Hàm kết nối đến database
bool connectToSQL(SQLHENV& hEnv, SQLHDBC& hDbc) {
	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
	SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
	SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);

	/*std::wstring connStr = L"Driver={ODBC Driver 17 for SQL Server};Server=localhost;Database=QLDienThoai;UID=sa;PWD=123;";
	SQLRETURN ret = SQLDriverConnectW(hDbc, nullptr, (SQLWCHAR*)connStr.c_str(), SQL_NTS, nullptr, 0, nullptr, SQL_DRIVER_COMPLETE);*/

	SQLWCHAR connStr[] = L"Driver={ODBC Driver 17 for SQL Server};Server=localhost\\SQLEXPRESS;Database=PhoneManagement;UID=sa;PWD=123;";
	SQLRETURN ret = SQLDriverConnectW(hDbc, NULL, connStr, SQL_NTS, NULL, 0, NULL, SQL_DRIVER_COMPLETE);

	if (SQL_SUCCEEDED(ret)) {
		std::wcout << L"Connect to SQL server successful.\n";
		return true;
	}
	else {
		std::wcout << L"Connect failed.\n";
		return false;
	}
}

void Phone::insertValue() {
	int id = inputIntegerNumber("Please input Phone ID: ");
	_id = id;

	cout << "Please input Phone Name: ";
	getline(cin, _name);

	cout << "Please input Phone manufacturer: ";
	getline(cin, _manufacturer);

	cout << "Please input Phone operating system: ";
	getline(cin, _config.operatingSystem);

	cout << "Please input Phone CPU: ";
	getline(cin, _config.cpu);

	_config.ram = inputIntegerNumber("Input RAM (GB): ");
	_config.rom = inputIntegerNumber("Input ROM (GB): ");
	_config.pin = inputIntegerNumber("Input pin (mAh): ");
	_config.screenSize = inputIntegerNumber("Input screen size (inch): ");

	cout << "Input price (million VND): ";
	getline(cin, _price);
	_price = priceStandardize(_price);
}


// Định nghĩa operator<< để xuất thông tin cấu hình
ostream& operator<<(ostream& os, const ConfigPhone& config)
{
	os	<< "operatingSystem : " << config.operatingSystem	<< "\n"
		<< "CPU             : " << config.cpu				<< "\n"
		<< "RAM             : " << config.ram				<< " GB\n"
		<< "ROM             : " << config.rom				<< " GB\n"
		<< "Man hinh        : " << config.screenSize		<< " inch\n"
		<< "Pin             : " << config.pin				<< " mAh";
	return os;
}

Phone::Phone(const Phone& p)
{
	_id = p._id;
	_name = p._name;
	_manufacturer = p._manufacturer;
	_config = p._config;
	_price = p._price;
}

Phone::Phone()
	: _id(0), _name(""), _manufacturer(""), _config(), _price("0") {}

Phone::Phone(const int id, const string name, const string manu, const ConfigPhone config, string price)
	: _id(id), _name(name), _manufacturer(manu), _config(config), _price(priceStandardize(price)) {}

Phone::~Phone()
{
	// Destructor
}


ostream& operator<<(ostream& os, const Phone p)
{
	os	<< "ID              : " <<	p._id				<< "\n"
		<< "Manufacturer    : " <<	p._manufacturer		<< "\n"
		<< "NamePhone       : " <<	p._name				<< "\n"
		<<							p._config			<< "\n"
		<< "Price           : " <<	p._price			<< " VND";
	return os;
}

bool Phone::operator==(const Phone p)
{
	if (_id == p.getID()) return true;
	return false;
}

bool Phone::operator!=(const Phone p)
{
	if (_id != p.getID()) return true;
	return false;
}

void Phone::insertToDB(SQLHDBC db) {
	SQLHSTMT stmt;

	SQLRETURN ret;

	// Kiểm tra xem ID có tồn tại hay không
	std::wstring checkQuery = L"SELECT COUNT(*) FROM PHONE WHERE ID = " + std::to_wstring(_id);
	SQLAllocHandle(SQL_HANDLE_STMT, db, &stmt);

	ret = SQLExecDirectW(stmt, (SQLWCHAR*)checkQuery.c_str(), SQL_NTS);

	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
		SQLINTEGER count;
		SQLBindCol(stmt, 1, SQL_C_SLONG, &count, 0, nullptr);
		ret = SQLFetch(stmt);
		cout << "Count: " << count << endl; // Debugging line
		if (count > 0) {
			cout << "ID is exists. \n";
			//std::wcout << L"⚠ ID điện thoại đã tồn tại (PRIMARY KEY trùng lặp).\n" << std::endl;
			SQLFreeHandle(SQL_HANDLE_STMT, stmt);
			return; // Không thực hiện insert
		}
	}

	SQLFreeHandle(SQL_HANDLE_STMT, stmt);  // Giải phóng stmt sau khi kiểm tra

	// Nếu ID không tồn tại, tiếp tục thực hiện insert
	SQLAllocHandle(SQL_HANDLE_STMT, db, &stmt);

	std::wstring query = L"INSERT INTO PHONE(ID, NamePhone, Manufacturer, Price, OperatingSystem, CPU, RAM, ROM, ScreenSize, Pin) VALUES ("
		+ std::to_wstring(_id) + L", N'"
		+ std::wstring(_name.begin(), _name.end()) + L"', N'"
		+ std::wstring(_manufacturer.begin(), _manufacturer.end()) + L"', "
		+ std::to_wstring(std::stoi(_price)) + L", N'"
		+ std::wstring(_config.operatingSystem.begin(), _config.operatingSystem.end()) + L"', N'"
		+ std::wstring(_config.cpu.begin(), _config.cpu.end()) + L"', "
		+ std::to_wstring(_config.ram) + L", "
		+ std::to_wstring(_config.rom) + L", "
		+ std::to_wstring(_config.screenSize) + L", "
		+ std::to_wstring(_config.pin) + L")";
	ret = SQLExecDirectW(stmt, (SQLWCHAR*)query.c_str(), SQL_NTS);

	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
		cout << "Save phone into database succesful!\n" << std::endl;
	}
	else {
		std::cout << "Error! Can't save into database!\n" << std::endl;

		SQLWCHAR sqlState[6];
		SQLINTEGER nativeError;
		SQLWCHAR messageText[256];
		SQLSMALLINT textLength;

		int i = 1;
		while (SQLGetDiagRecW(SQL_HANDLE_STMT, stmt, i, sqlState, &nativeError, messageText, sizeof(messageText) / sizeof(SQLWCHAR), &textLength) == SQL_SUCCESS) {
			std::wcout << L"[Error " << i << L"] SQLSTATE: " << sqlState << std::endl;
			std::wcout << L"Error Code: " << nativeError << std::endl;
			std::wcout << L"Notice: " << messageText << std::endl;
			i++;
		}

		// Thực thi truy vấn
		if (SQLExecDirectW(stmt, (SQLWCHAR*)query.c_str(), SQL_NTS) == SQL_SUCCESS) {
			std::cout << "Save phone into database succesful!\n";
		}
		else {
			std::cout << "Error! Can't save into database!\n";

		}

		SQLFreeHandle(SQL_HANDLE_STMT, stmt);
	}
}