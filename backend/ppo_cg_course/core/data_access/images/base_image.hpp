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
        virtual int create(std::string &path, std::vector<std::vector<QColor>> &color_buffer,
                            scene_win_t win_boards) = 0;

        virtual std::vector<std::vector<QColor>> load(std::string path) = 0;
};

#endif
