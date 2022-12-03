#include <stdio.h>
#include "png.hpp"


int PNGImage::create(std::string &path, std::vector<std::vector<QColor> > &color_buffer)
{
}

int PNGImage::create(std::string &path, std::vector<std::vector<QColor>> &color_buffer,
                     scene_win_t win_boards)
{
    int width = 0, height = 0;
    bool success = true;
    png_bytep *row_pointers = NULL;

    png_structp png;
    png_infop info;
    FILE *file = NULL;

    file = fopen(path.c_str(), "wb");
    if (!file) {return false;}

    png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    info = png_create_info_struct(png);

    if (setjmp(png_jmpbuf(png))) {return false;}

    png_init_io(png, file);

    //width = win_boards.max_y; height = win_boards.max_x;
    int min_x = win_boards.min_x, max_x = win_boards.max_x;
    int min_y = win_boards.min_y, max_y = win_boards.max_y;
    width = max_x - min_x, height = max_y - min_y;
    //std::cerr << " height: " << height << "width: " << width  << "\n";
    png_set_IHDR(
        png,
        info,
        width, height,
        8,
        PNG_COLOR_TYPE_RGBA,
        PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_DEFAULT,
        PNG_FILTER_TYPE_DEFAULT
      );

    png_write_info(png, info);

    row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
    for(int y = 0; y < height; y++) {
        row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png,info));
      }

    std::vector<std::vector<QColor>> new_buffer;

    new_buffer.reserve(height);
    for (int i = 0; i < height; ++i){
        new_buffer[i].reserve(width);
    }

    for (int i = 0; i < height; ++i){
        for (int j = 0; j < width; ++j){
            new_buffer[i][j] = color_buffer[i+min_y][j+min_x];
        }
    }


    /*for (int i = 0; i < height; ++i){
        std::cerr << "i=" << i;
        for (int j = 0; j < width; ++j){
            std::cerr << "(" << color_buffer[i][j].red() << "," << color_buffer[i][j].green() << "," << color_buffer[i][j].blue() << "),";
        }
        std::cerr << "\n";
    }*/
    std::cerr << "TRANSER\n";
    int red, green, blue;
    png_bytep px;
    for(int y = 0; y < height; y++) {
        png_bytep row = row_pointers[y];
        for(int x = 0; x < width; x++) {
          px = &(row[x * 4]);
          new_buffer[x][y].getRgb(&red, &green, &blue);
          px[0] = red;
          px[1] = green;
          px[2] = blue;
          px[3] = 255;
        }
      }

    png_write_image(png, row_pointers);
    png_write_end(png, NULL);

    if (png && info){
       png_destroy_write_struct(&png, &info);
    }

    for(int y = 0; y < height; y++) {
        free(row_pointers[y]);
      }
    free(row_pointers);

    return success;
}

std::vector<std::vector<QColor> > PNGImage::load(std::string path)
{

}
