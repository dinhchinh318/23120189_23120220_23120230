#include <gtest/gtest.h>
#include "FunctionScreen/delScreen_utils.h"

TEST(DeleteScreenTest, ValidateDeleteFields) {
    std::string err;
    EXPECT_FALSE(validateDeleteFields("", err));
    EXPECT_EQ(err, "Please enter ID!");

    EXPECT_FALSE(validateDeleteFields("abc", err));
    EXPECT_EQ(err, "ID must be a number!");

    EXPECT_TRUE(validateDeleteFields("123", err));
}

TEST(DeleteScreenTest, IsValidDeleteID) {
    EXPECT_TRUE(isValidDeleteID("123"));
    EXPECT_FALSE(isValidDeleteID(""));
    EXPECT_FALSE(isValidDeleteID("12a3"));
}

TEST(DeleteScreenTest, DeletePhone_ValidID) {
    SQLHENV hEnv;
    SQLHDBC hDbc;
    ASSERT_TRUE(connectToSQLTest(hEnv, hDbc)); // Kết nối DB test

    // Thêm bản ghi test
    int testID = 31;
    std::wstring insertQuery = L"INSERT INTO PHONE(ID, NamePhone, Manufacturer, Price, OperatingSystem, CPU, RAM, ROM, ScreenSize, Pin) VALUES (" 
    + std::to_wstring(testID) 
    + L", N'iPhone 14 Pro', N'Apple', N'30990000', N'iOS', N'A16 Bionic', 6, 256, 6.1, 3200)";

    SQLHSTMT stmt;
    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &stmt);
    SQLExecDirectW(stmt, (SQLWCHAR*)insertQuery.c_str(), SQL_NTS);
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    // Xóa bản ghi vừa thêm
    EXPECT_TRUE(deletePhoneFromDB(hDbc, testID));

    // Kiểm tra bản ghi đã bị xóa
    std::wstring selectQuery = L"SELECT * FROM PHONE WHERE ID = " + std::to_wstring(testID);
    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &stmt);
    SQLRETURN ret = SQLExecDirectW(stmt, (SQLWCHAR*)selectQuery.c_str(), SQL_NTS);
    EXPECT_TRUE(ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO);
    // Kiểm tra không còn bản ghi nào trả về
    EXPECT_EQ(SQLFetch(stmt), SQL_NO_DATA);
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}


//Test handleFindButton
TEST(DeleteScreenTest, HandleFindButton_EmptyID) {
    SQLHENV hEnv;
    SQLHDBC hDbc;
    ASSERT_TRUE(connectToSQLTest(hEnv, hDbc));
    std::wstring msg;
    EXPECT_FALSE(handleFindButton(hDbc, "", msg));
    EXPECT_EQ(msg, L"Please input ID!");
}

TEST(DeleteScreenTest, HandleFindButton_InvalidID) {
    SQLHENV hEnv;
    SQLHDBC hDbc;
    ASSERT_TRUE(connectToSQLTest(hEnv, hDbc));
    std::wstring msg;
    EXPECT_FALSE(handleFindButton(hDbc, "abc", msg));
    EXPECT_EQ(msg, L"ID must be a number!");
}

TEST(DeleteScreenTest, HandleFindButton_NotFound) {
    SQLHENV hEnv;
    SQLHDBC hDbc;
    ASSERT_TRUE(connectToSQLTest(hEnv, hDbc));
    std::wstring msg;
    // Giả sử 999999 là ID không tồn tại
    EXPECT_FALSE(handleFindButton(hDbc, "999999", msg));
    EXPECT_EQ(msg, L"Not found!");
}

TEST(DeleteScreenTest, HandleFindButton_Found) {
    SQLHENV hEnv;
    SQLHDBC hDbc;
    ASSERT_TRUE(connectToSQLTest(hEnv, hDbc));
    std::wstring msg;

    int testID = 32; // ID test
    std::wstring insertQuery = L"INSERT INTO PHONE(ID, NamePhone, Manufacturer, Price, OperatingSystem, CPU, RAM, ROM, ScreenSize, Pin) VALUES (" 
    + std::to_wstring(testID) 
    + L", N'iPhone 16 Pro', N'Apple', N'30990000', N'iOS', N'A16 Bionic', 6, 256, 6.1, 3200)";

    SQLHSTMT stmt;
    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &stmt);
    SQLExecDirectW(stmt, (SQLWCHAR*)insertQuery.c_str(), SQL_NTS);
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    // Test tìm kiếm
    EXPECT_TRUE(handleFindButton(hDbc, std::to_string(testID), msg));
    EXPECT_EQ(msg, L"Found successfully!");

    // Xóa bản ghi test
    deletePhoneFromDB(hDbc, testID);
}