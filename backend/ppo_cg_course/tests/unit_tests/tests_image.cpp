#include <gtest/gtest.h>

#include <QCoreApplication>
#include <QDebug>
#include "core/data_access/images/data_access_image_bmp.hpp"
#include "core/data_access/images/data_access_image_bmp.h"

/*TEST(create_bmp_file_test, positive) {
    DataAccessFileBMP file_bmp;
    std::string file_name = "../data/heightmap.bmp";
    std::vector<std::vector<QColor>> color_buffer;
    std::vector<QColor> temp;

    for (int i = 0; i < 5; i++){
        temp.push_back(qRgb(126 + i, 134 + i, 167 + i));
    }
    color_buffer.push_back(temp);

    int result = file_bmp.create(file_name, color_buffer);

    EXPECT_EQ(0, result);
}

TEST(load_bmp_file_test, positive) {
    DataAccessFileBMP file_bmp;
    std::vector<std::vector<QColor>> result_rgb_info = file_bmp.load("../data/example.bmp");
    int result_size = 0, rgb_info_size = result_rgb_info.size();

    EXPECT_NE(result_size, rgb_info_size);
}*/
