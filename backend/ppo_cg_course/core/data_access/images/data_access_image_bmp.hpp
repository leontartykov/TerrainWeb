#include "data_access_image_bmp.h"
#include "bmp_structure.h"
#include <QDebug>

template <typename T>
void DataAccessFileBMP::write(T &input, std::ofstream &fp){
    fp.write(reinterpret_cast<char*>(&input), sizeof(input));
}



template <typename Type>
void DataAccessFileBMP::read(std::ifstream &fp, Type &result, std::size_t size) {
    fp.read(reinterpret_cast<char*>(&result), size);
}

