#ifndef _PNG_HPP_
#define _PNG_HPP_

#include <png.h>
#include "core/data_access/images/base_image.hpp"
#include "core/scene/scene.h"

class PNGImage: public BaseImage
{
    private:

    public:
        PNGImage() = default;
        virtual ~PNGImage() override {};

        virtual int create(std::string &path, std::vector<std::vector<QColor>> &color_buffer) override;
        virtual int create(std::string &path, std::vector<std::vector<QColor>> &color_buffer,
                           scene_win_t win_boards) override;
        virtual std::vector<std::vector<QColor>> load(std::string path) override;
};

#endif
