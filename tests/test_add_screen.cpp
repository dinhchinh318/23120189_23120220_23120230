#include <gtest/gtest.h>
#include "FunctionScreen/addScreen.h"

TEST(AddScreenTest, IsValidInteger) {
    EXPECT_TRUE(isValidInteger("123"));
    EXPECT_FALSE(isValidInteger("12a3"));
    EXPECT_FALSE(isValidInteger(""));
    EXPECT_FALSE(isValidInteger("-123"));
}

TEST(AddScreenTest, IsValidFloat) {
    EXPECT_TRUE(isValidFloat("123.45"));
    EXPECT_TRUE(isValidFloat("0.0"));
    EXPECT_TRUE(isValidFloat("100"));
    EXPECT_FALSE(isValidFloat("abc"));
    EXPECT_FALSE(isValidFloat(""));
    EXPECT_FALSE(isValidFloat("12.3.4"));
}

TEST(AddScreenTest, ValidatePhoneFields) {
    std::vector<std::string> valid = {"1","Name","Manu","1000","Android","Snap", "8","128","6.5","5000"};
    std::string err;
    EXPECT_TRUE(validatePhoneFields(valid, err));

    std::vector<std::string> missing = {"","","","","","","","","",""};
    EXPECT_FALSE(validatePhoneFields(missing, err));
    EXPECT_EQ(err, "Please fill in all fields!");

    std::vector<std::string> invalidID = {"abc","Name","Manu","1000","Android","Snap", "8","128","6.5","5000"};
    EXPECT_FALSE(validatePhoneFields(invalidID, err));
    EXPECT_EQ(err, "ID must be a valid number!");

    std::vector<std::string> invalidNum = {"1","Name","Manu","1000","Android","Snap", "a","b","c","d"};
    EXPECT_FALSE(validatePhoneFields(invalidNum, err));
    EXPECT_EQ(err, "RAM, ROM, Pin must be integer. Screen must be float!");
}

//test thành công
TEST(AddScreenTest, AddPhoneToDB_Success) {
    SQLHENV hEnv;
    SQLHDBC hDbc;
    ASSERT_TRUE(connectToSQLTest(hEnv, hDbc));

    int testID = 55;
    std::vector<std::string> fields = {std::to_string(testID), "Google Pixel 8", "Google", "18990000", "Android", "Google Tensor G3", "8", "128", "6.5", "4575"};
    std::string err;
    EXPECT_TRUE(addPhoneToDB(hDbc, fields, err));
    EXPECT_EQ(err, "");
}

//test khi trùng ID
TEST(AddScreenTest, AddPhoneToDB_DuplicateID) {
    SQLHENV hEnv;
    SQLHDBC hDbc;
    ASSERT_TRUE(connectToSQLTest(hEnv, hDbc));

    int testID = 1;
    std::vector<std::string> fields = {std::to_string(testID), "TestName", "TestManu", "1000", "Android", "Snap", "8", "128", "6.5", "5000"};
    std::string err;
    EXPECT_FALSE(addPhoneToDB(hDbc, fields, err));
}

TEST(AddScreenTest, AddPhoneToDB_EmptyFields) {
    SQLHENV hEnv;
    SQLHDBC hDbc;
    ASSERT_TRUE(connectToSQLTest(hEnv, hDbc));

    std::vector<std::string> emptyFields = {"","","","","","","","","",""};
    std::string err;
    EXPECT_FALSE(addPhoneToDB(hDbc, emptyFields, err));
}