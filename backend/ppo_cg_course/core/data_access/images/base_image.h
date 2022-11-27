#ifndef _BASE_IMAGE_H_
#define _BASE_IMAGE_H_

#include <iostream>
#include <vector>
#include <fstream>
#include <QColor>

#include "bmp_structure.h"

class BaseDataAccessImage
{
    public:
        virtual ~BaseDataAccessImage() = default;

        virtual int create(std::string &path, std::vector<std::vector<QColor>> &color_buffer) = 0;

        virtual std::vector<std::vector<QColor>> load(std::string path) = 0;
};

#endif
