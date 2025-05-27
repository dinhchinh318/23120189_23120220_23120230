#include <gtest/gtest.h>
#include "FunctionScreen/edit_exec_utils.h"
#include "FunctionScreen/delScreen_utils.h"

//Kiểm thử dữ liệu đầu vào hợp lệ và không hợp lệ cho hàm validateEditFields
TEST(EditScreenTest, ValidateEditFields) {
    std::vector<std::string> valid = {"50","Oppo A77s","Oppo","6290000","Android","Snapdragon 680", "8","128","6.5","5000"};
    std::string err;
    EXPECT_TRUE(validateEditFields(valid, err));

    std::vector<std::string> missing = {"","","","","","","","","",""};
    EXPECT_FALSE(validateEditFields(missing, err));
    EXPECT_EQ(err, "Please fill in all fields!");

    std::vector<std::string> invalidID = {"abc","Name","Manu","1000","Android","Snap", "8","128","6.5","5000"};
    EXPECT_FALSE(validateEditFields(invalidID, err));
    EXPECT_EQ(err, "ID must be a valid number!");
}

// Integration test (test trên database)
TEST(EditScreenTest, UpdatePhoneInDB) {
    SQLHENV hEnv;
    SQLHDBC hDbc;
    ASSERT_TRUE(connectToSQLTest(hEnv, hDbc)); // Hàm này bạn đã có

    int testID = 50;
    std::vector<std::string> newFields = {std::to_string(testID), "OnePlus 12R", "OnePlus", "13990000", "Android", "Snapdragon 8 Gen 2", "16", "256", "6.78", "5500"};
    std::string err;
    EXPECT_TRUE(updatePhoneInDB(hDbc, testID, newFields, err));
    EXPECT_EQ(err, "");
}

//Test với dữ liệu sai format
TEST(EditScreenTest, UpdatePhoneInDB_Error_format) {
    SQLHENV hEnv;
    SQLHDBC hDbc;
    ASSERT_TRUE(connectToSQLTest(hEnv, hDbc)); // Hàm này bạn đã có

    int testID = 50;
    std::vector<std::string> newFields = {std::to_string(testID), "OnePlus 12R", "OnePlus", "13990000", "Android", "Snapdragon 8 Gen 2", "16", "256", "6.78", "Pin"};
    std::string err;
    EXPECT_TRUE(updatePhoneInDB(hDbc, testID, newFields, err));
    EXPECT_EQ(err, "");
}

TEST(EditScreenTest, UpdatePhoneInDB_Fail) {
    SQLHENV hEnv;
    SQLHDBC hDbc;
    ASSERT_TRUE(connectToSQLTest(hEnv, hDbc));

    int invalidID = 999999; // ID không tồn tại
    std::vector<std::string> newFields = {std::to_string(invalidID), "Fake", "Fake", "0", "None", "None", "0", "0", "0", "0"};
    std::string err;
    EXPECT_FALSE(updatePhoneInDB(hDbc, invalidID, newFields, err));
    EXPECT_EQ(err, "Update failed!");
}