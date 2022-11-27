#ifndef _PNG_HPP_
#define _PNG_HPP_

#include <png.h>
#include "core/data_access/images/base_image.h"
#include "core/scene/scene.h"

class PNGImage: public BaseDataAccessImage
{
    private:

    public:
        PNGImage() = default;
        ~PNGImage() = default;

        virtual int create(std::string &path, std::vector<std::vector<QColor>> &color_buffer) override;
        int create(std::string &path, std::vector<std::vector<QColor>> &color_buffer, scene_win_t win_boards);
        virtual std::vector<std::vector<QColor>> load(std::string path) override;
};

#endif
