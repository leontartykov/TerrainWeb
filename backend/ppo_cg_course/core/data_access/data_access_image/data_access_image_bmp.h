#ifndef _DATA_ACCESS_IMAGE_BMP_H_
#define _DATA_ACCESS_IMAGE_BMP_H_

#include <QColor>
#include "data_access_image_base.h"

class DataAccessFileBMP: BaseDataAccessImage
{
    public:
        DataAccessFileBMP() = default;
        ~DataAccessFileBMP()  = default;

        virtual int create(std::string path, std::vector<std::vector<QColor>> &color_buffer) override;
        virtual void update() override;
        virtual void remove() override;

        virtual std::vector<std::vector<QColor>> load(std::string path) override;
        void write(std::string path, std::string text);

    private:
        template <typename Type>
        void read(std::ifstream &fp, Type &result, std::size_t size);

        unsigned char bit_extract(const unsigned int byte, const unsigned int mask);

        template <typename T>
        void write(T &input, std::ofstream &fp);
};



#endif
