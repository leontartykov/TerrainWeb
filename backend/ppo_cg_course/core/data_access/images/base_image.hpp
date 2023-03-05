#ifndef _BASE_IMAGE_HPP_
#define _BASE_IMAGE_HPP_

#include <iostream>
#include <vector>
#include <fstream>
#include <QColor>

#include "bmp_structure.h"
#include "core/scene/scene.h"

class BaseImage
{
    public:
        virtual ~BaseImage() {};

        virtual int create(std::string &path, std::vector<std::vector<QColor>> &color_buffer) = 0;
        virtual int create(const std::string &path, const std::vector<std::vector<QColor>> &color_buffer,
                           const scene_win_t win_boards) = 0;

        virtual int load(const std::string &path,
                         std::vector<std::vector<QColor>> &color_buffer) = 0;
};

#endif
