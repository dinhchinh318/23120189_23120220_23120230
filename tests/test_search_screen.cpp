#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "../source/FunctionScreen/searchScreen_utils.h"

TEST(SearchScreenUtilsTest, IsValidInteger) {
    EXPECT_TRUE(isValidInteger("12345"));
}

TEST(SearchScreenUtilsTest, IsValidFloat) {
    EXPECT_TRUE(isValidFloat("12.34"));
    EXPECT_TRUE(isValidFloat("0"));
    EXPECT_FALSE(isValidFloat("abc"));
    EXPECT_FALSE(isValidFloat(""));
}

TEST(SearchScreenUtilsTest, ValidateSearchFields) {
    std::vector<std::string> fields1 = {"abc", "123"};
    std::string errorMsg;
    EXPECT_TRUE(validateSearchFields(fields1, errorMsg));
    std::vector<std::string> fields2 = {"", "123"};
    EXPECT_FALSE(validateSearchFields(fields2, errorMsg));
    std::vector<std::string> fields3;
    EXPECT_FALSE(validateSearchFields(fields3, errorMsg));
}

TEST(SearchScreenUtilsTest, SearchInVector) {
    std::vector<std::string> data = {"apple", "banana", "cherry"};
    EXPECT_TRUE(searchInVector(data, "ban"));
    EXPECT_FALSE(searchInVector(data, "orange"));
    EXPECT_TRUE(searchInVector(data, "")); // empty keyword is always found
}

extern bool connectToSQLTest(SQLHENV &hEnv, SQLHDBC &hDbc);

//Trường hợp tìm thấy
TEST(SearchScreenUtilsTest, SearchPhoneInDB_Found) {
    SQLHENV hEnv;
    SQLHDBC hDbc;
    ASSERT_TRUE(connectToSQLTest(hEnv, hDbc));

    // Giả sử đã có bản ghi với NamePhone là "iPhone"
    std::vector<std::string> fields(10, "");
    fields[1] = "iPhone"; // Đúng vị trí trường tên
    std::vector<std::vector<std::string>> results;
    std::string err;
    EXPECT_TRUE(searchPhoneInDB(hDbc, fields, results, err));
    EXPECT_GT(results.size(), 0);
    EXPECT_EQ(err, "");
}

//Trường hợp không tìm thấy
TEST(SearchScreenUtilsTest, SearchPhoneInDB_NotFound) {
    SQLHENV hEnv;
    SQLHDBC hDbc;
    ASSERT_TRUE(connectToSQLTest(hEnv, hDbc));

    std::vector<std::string> fields(10, "");
    fields[1] = "NoSuchPhoneName"; // Đúng vị trí trường tên
    std::vector<std::vector<std::string>> results;
    std::string err;
    EXPECT_FALSE(searchPhoneInDB(hDbc, fields, results, err));
    // EXPECT_EQ(results.size(), 0);
    // EXPECT_EQ(err, "No result found or query error!");
}


//Test trường hợp khi nhập trống
TEST(SearchScreenUtilsTest, SearchPhoneInDB_EmptyFields) {
    SQLHENV hEnv;
    SQLHDBC hDbc;
    ASSERT_TRUE(connectToSQLTest(hEnv, hDbc));

    std::vector<std::string> fields; // empty
    std::vector<std::vector<std::string>> results;
    std::string err;
    EXPECT_FALSE(searchPhoneInDB(hDbc, fields, results, err));
    EXPECT_EQ(err, "No search fields provided!");
}


//Test trường hợp khi tìm ID
TEST(SearchScreenUtilsTest, SearchPhoneInDB_ByID) {
    SQLHENV hEnv;
    SQLHDBC hDbc;
    ASSERT_TRUE(connectToSQLTest(hEnv, hDbc));

    // Giả sử đã có bản ghi với ID là 1
    std::vector<std::string> fields(10, "");
    fields[0] = "1"; // Đúng vị trí trường ID
    std::vector<std::vector<std::string>> results;
    std::string err;
    EXPECT_TRUE(searchPhoneInDB(hDbc, fields, results, err));
    EXPECT_GT(results.size(), 0);
    EXPECT_EQ(err, "");
}

//Test trường hợp khi tìm tên
TEST(SearchScreenUtilsTest, SearchPhoneInDB_ByName) {
    SQLHENV hEnv;
    SQLHDBC hDbc;
    ASSERT_TRUE(connectToSQLTest(hEnv, hDbc));

    // Giả sử đã có bản ghi với NamePhone là "iPhone"
    std::vector<std::string> fields(10, "");
    fields[1] = "v"; // Đúng vị trí trường tên
    std::vector<std::vector<std::string>> results;
    std::string err;
    EXPECT_TRUE(searchPhoneInDB(hDbc, fields, results, err));
    EXPECT_GT(results.size(), 0);
    EXPECT_EQ(err, "");
}

//Test trường hợp khi tìm hãng
TEST(SearchScreenUtilsTest, SearchPhoneInDB_ByManufacturer) {
    SQLHENV hEnv;
    SQLHDBC hDbc;
    ASSERT_TRUE(connectToSQLTest(hEnv, hDbc));

    // Giả sử đã có bản ghi với Manufacturer là "A"
    std::vector<std::string> fields(10, "");
    fields[2] = "A"; // Đúng vị trí trường hãng
    std::vector<std::vector<std::string>> results;
    std::string err;
    EXPECT_TRUE(searchPhoneInDB(hDbc, fields, results, err));
    EXPECT_GT(results.size(), 0);
    EXPECT_EQ(err, "");
}

