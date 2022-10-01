#include <gtest/gtest.h>

#include "../core/data_access/data_access_file/data_access_file.hpp"

TEST(create_file_txt_test, positive) {
    DataAccessFileTxt file_txt;
    int error = file_txt.create("../data/test.txt");

    EXPECT_EQ(0, error);
}

TEST(load_file_txt_test, positive){
    DataAccessFileTxt file_txt;
    std::string result_load = file_txt.load("../data/numbers.txt");
    EXPECT_NE("", result_load);
}
