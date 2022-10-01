#include "data_access_image_bmp.h"
#include "data_access_image_bmp.hpp"

int DataAccessFileBMP::create(std::string path, std::vector<std::vector<QColor>> &color_buffer){
    BITMAPFILEHEADER file_header;
    BITMAPV5HEADER file_header_info;
    CIEXYZTRIPLE ciexyzcolors;
    std::ofstream file;

    unsigned int width = color_buffer.size(), height = color_buffer[0].size();

    file_header = {
        .bfType = 0x4D42,
        .bfSize = 0,
        .bfReserved1 = 0,
        .bfReserved2 = 0,
        .bfOffBits = sizeof(file_header) + sizeof(file_header_info)
    };

    file_header_info = {
        .bSize = sizeof(file_header_info),
        .bWidth = width,
        .bHeight = height,
        .bPlanes = 0x00000001,
        .bBitCount = 0x00000018,
        .bCompression = 0,
        .bXPelsPerMeter = 0,
        .bYPelsPerMeter = 0,
        .bClrUsed = 0,
        .bClrImportant = 0,
        .bRedMask = 0x00FF0000,
        .bGreenMask = 0x0000FF00,
        .bBlueMask = 0x000000FF,
        .bAlphaMask = 0xFF000000,
        .bCSType = 0x73524742,
        .bEndpoints = {
            .ciexyzRed = {0, 0, 0},
            .ciexyzGreen = {0, 0, 0},
            .ciexyzBlue = {0, 0, 0}},
         .bGammaRed = 0,
         .bGammaGreen = 0,
         .bGammaBlue = 0,
         .bIntent = 0x00000004,
         .bProfileData = 0,
         .bProfileSize = 0,
         .bReserved = 0
    };

    file_header_info.bSizeImage = width * height * file_header_info.bBitCount;

    file.open(path, std::ofstream::binary);

    if(!file){
        std::cout << "Ошибка создания файла.\n";
        return -1;
    }

    //write the header of file
    this->write(file_header.bfType, file);
    this->write(file_header.bfSize, file);
    this->write(file_header.bfReserved1, file);
    this->write(file_header.bfReserved2, file);
    this->write(file_header.bfOffBits, file);

    //write the header of image
    this->write(file_header_info.bSize, file);
    this->write(file_header_info.bWidth, file);
    this->write(file_header_info.bHeight, file);
    this->write(file_header_info.bPlanes, file);
    this->write(file_header_info.bBitCount, file);
    this->write(file_header_info.bCompression, file);
    this->write(file_header_info.bSizeImage, file);
    this->write(file_header_info.bXPelsPerMeter, file);
    this->write(file_header_info.bYPelsPerMeter, file);
    this->write(file_header_info.bClrUsed, file);
    this->write(file_header_info.bClrImportant, file);
    this->write(file_header_info.bRedMask, file);
    this->write(file_header_info.bGreenMask, file);
    this->write(file_header_info.bBlueMask, file);
    this->write(file_header_info.bAlphaMask, file);
    this->write(file_header_info.bCSType, file);
    this->write(file_header_info.bEndpoints, file);
    this->write(file_header_info.bGammaRed, file);
    this->write(file_header_info.bGammaGreen, file);
    this->write(file_header_info.bGammaBlue, file);
    this->write(file_header_info.bIntent, file);
    this->write(file_header_info.bProfileData, file);
    this->write(file_header_info.bProfileSize, file);
    this->write(file_header_info.bReserved, file);

    int red, green, blue;
    for (unsigned int i = 0; i < width; i++) {
        for (unsigned int j = 0; j < height; j++)
        {
                red = color_buffer[i][j].red();
                green = color_buffer[i][j].green();
                blue = color_buffer[i][j].blue();

                write(blue, file);
                write(green, file);
                write(red, file);
            }
        }
    file.close();
    return 0;
}


void DataAccessFileBMP::update(){
}

void DataAccessFileBMP::remove(){
}

std::vector<std::vector<QColor>> DataAccessFileBMP::load(std::string path)
{
    std::ifstream file;
    std::vector<std::vector<QColor>> color_buffer;

    file.open(path, std::ifstream::binary);

    if (!file.is_open()){
        std::cout << "Ошибка открытия файла.\n";
        return color_buffer;
    }

    //general info about bmp file
    BITMAPFILEHEADER file_header;
    BITMAPV5HEADER file_header_info;
    read(file, file_header.bfType, sizeof(file_header.bfType));

    //check, if file is a bmp
    if (file_header.bfType != 0x4D42) {
            std::cout << "Error:  is not BMP file." << std::endl;
            return color_buffer;
    }

    read(file, file_header.bfSize, sizeof(file_header.bfSize));
    read(file, file_header.bfReserved1, sizeof(file_header.bfReserved1));
    read(file, file_header.bfReserved2, sizeof(file_header.bfReserved2));
    read(file, file_header.bfOffBits, sizeof(file_header.bfOffBits));

    // get info about header
    read(file, file_header_info.bSize, sizeof(file_header_info.bSize));

    //get info to a structure
    //amount of filled fields depend on version of bmp
    if (file_header_info.bSize >= 12) {
        read(file, file_header_info.bWidth, sizeof(file_header_info.bWidth));
        read(file, file_header_info.bHeight, sizeof(file_header_info.bHeight));
        read(file, file_header_info.bPlanes, sizeof(file_header_info.bPlanes));
        read(file, file_header_info.bBitCount, sizeof(file_header_info.bBitCount));
    }

    int count_colors = file_header_info.bBitCount >> 3;
    if (count_colors < 3) {
        count_colors = 3;
    }

    int bits_on_color = file_header_info.bBitCount / count_colors;
    int mask_value= (1 << bits_on_color) - 1;

    // bmp v1
    if (file_header_info.bSize >= 40)
    {
        read(file, file_header_info.bCompression, sizeof(file_header_info.bCompression));
        read(file, file_header_info.bSizeImage, sizeof(file_header_info.bSizeImage));
        read(file, file_header_info.bXPelsPerMeter, sizeof(file_header_info.bXPelsPerMeter));
        read(file, file_header_info.bYPelsPerMeter, sizeof(file_header_info.bYPelsPerMeter));
        read(file, file_header_info.bClrUsed, sizeof(file_header_info.bClrUsed));
        read(file, file_header_info.bClrImportant, sizeof(file_header_info.bClrImportant));
    }

    // bmp v2
    file_header_info.bRedMask = 0;
    file_header_info.bGreenMask = 0;
    file_header_info.bBlueMask = 0;

    if (file_header_info.bSize >= 52) {
        read(file, file_header_info.bRedMask, sizeof(file_header_info.bRedMask));
        read(file, file_header_info.bGreenMask, sizeof(file_header_info.bGreenMask));
        read(file, file_header_info.bBlueMask, sizeof(file_header_info.bBlueMask));
    }

    // create mask if it is absent
    if (file_header_info.bRedMask == 0 || file_header_info.bGreenMask == 0 || file_header_info.bBlueMask == 0) {
        file_header_info.bRedMask = mask_value << (bits_on_color * 2);
        file_header_info.bGreenMask = mask_value << bits_on_color;
        file_header_info.bBlueMask = mask_value;
    }

    // bmp v3
    if (file_header_info.bSize >= 56) {
        read(file, file_header_info.bAlphaMask, sizeof(file_header_info.bAlphaMask));
    } else {
        file_header_info.bAlphaMask = mask_value<< (bits_on_color * 3);
    }

    // bmp v4
    if (file_header_info.bSize >= 108) {
        read(file, file_header_info.bCSType, sizeof(file_header_info.bCSType));
        read(file, file_header_info.bEndpoints, sizeof(file_header_info.bEndpoints));
        read(file, file_header_info.bGammaRed, sizeof(file_header_info.bGammaRed));
        read(file, file_header_info.bGammaGreen, sizeof(file_header_info.bGammaGreen));
        read(file, file_header_info.bGammaBlue, sizeof(file_header_info.bGammaBlue));
    }

    // bmp v5
    if (file_header_info.bSize >= 124) {
        read(file, file_header_info.bIntent, sizeof(file_header_info.bIntent));
        read(file, file_header_info.bProfileData, sizeof(file_header_info.bProfileData));
        read(file, file_header_info.bProfileSize, sizeof(file_header_info.bProfileSize));
        read(file, file_header_info.bReserved, sizeof(file_header_info.bReserved));
    }

    // rgb info
    RGBQUAD **rgb_info = nullptr;
    rgb_info = new RGBQUAD*[file_header_info.bHeight];
    for (unsigned int i = 0; i < file_header_info.bHeight; i++) {
        rgb_info[i] = new RGBQUAD[file_header_info.bWidth];
    }

    //padding
    int line_padding = ((file_header_info.bWidth * (file_header_info.bBitCount / 8)) % 4) & 3;

    // read pixels
    unsigned int buffer;
    std::vector<QColor> row_color_buffer;

    for (unsigned int i = 0; i < file_header_info.bHeight; i++) {
        for (unsigned int j = 0; j < file_header_info.bWidth; j++) {
            read(file, buffer, file_header_info.bBitCount / 8);

            rgb_info[i][j].rgbRed = bit_extract(buffer, file_header_info.bRedMask);
            rgb_info[i][j].rgbGreen = bit_extract(buffer, file_header_info.bGreenMask);
            rgb_info[i][j].rgbBlue = bit_extract(buffer, file_header_info.bBlueMask);
            rgb_info[i][j].rgbReserved = bit_extract(buffer, file_header_info.bAlphaMask);

            row_color_buffer.push_back(qRgb((int)rgb_info[i][j].rgbRed,
                                                (int)rgb_info[i][j].rgbGreen, (int)rgb_info[i][j].rgbBlue));
        }
        file.seekg(line_padding, std::ios_base::cur);
        color_buffer.push_back(row_color_buffer);
        row_color_buffer.clear();
    }

    for (unsigned int i = 0; i < file_header_info.bHeight; i++) {
        delete[] rgb_info[i];
    }
    delete[] rgb_info;

    file.close();
    return color_buffer;
}

void DataAccessFileBMP::write(std::string path, std::string text){
}

unsigned char DataAccessFileBMP::bit_extract(const unsigned int byte, const unsigned int mask) {
    if (mask == 0) {
        return 0;
    }

    int mask_buffer = mask, mask_pudding = 0;
    while (!(mask_buffer & 1)) {
        mask_buffer >>= 1;
        mask_pudding++;
    }

    return (byte & mask) >> mask_pudding;
}
