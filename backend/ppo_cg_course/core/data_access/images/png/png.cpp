#include <stdio.h>
#include "png.hpp"


int PNGImage::create(std::string &path, std::vector<std::vector<QColor> > &color_buffer) {}

int PNGImage::create(const std::string &path, const std::vector<std::vector<QColor>> &color_buffer,
                           const scene_win_t win_boards)
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
    //width = max_y - min_y, height = max_x - min_x;
    //width = 561; height = 772;
    //width = color_buffer.size(); height = color_buffer[0].size();
    std::cerr << " width: " << width << "height: " << height  << "\n";
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
    std::cerr << "point_1\n";

    std::vector<std::vector<QColor>> new_buffer;

    new_buffer.reserve(height);
    for (int i = 0; i < height; ++i){
        new_buffer[i].reserve(width);
    }
    std::cerr << "point_2\n";

    for (int i = 0; i < height; ++i){
        for (int j = 0; j < width; ++j){
            new_buffer[i][j] = color_buffer[i][j];
        }
    }
    std::cerr << "point_3\n";

    /*for (int i = 0; i < width; ++i){
        for (int j = 0; j < height; ++j){
            std::cerr << "(" << color_buffer[i][j].red() << "," << color_buffer[i][j].green() << "," << color_buffer[i][j].blue() << "),";
        }
        std::cout << "\n";
    }*/

    /*for (int i = 0; i < height; ++i){
        std::cerr << "i=" << i;
        for (int j = 0; j < width; ++j){
            //std::cerr << "(" << new_buffer[i][j].red() << "," << new_buffer[i][j].green() << "," << new_buffer[i][j].blue() << "),";
            std::cerr << new_buffer[i][j].red() << " " << new_buffer[i][j].green() << " " << new_buffer[i][j].blue() << " ";
        }
        std::cerr << "\n";
    }
    std::cerr << "TRANSER\n";*/
    int red, green, blue;
    png_bytep px;
    for(int y = 0; y < height; y++) {
        png_bytep row = row_pointers[y];
        for(int x = 0; x < width; x++) {
          //std::cerr << "y: " << y << " x: " << x << "\n";
          px = &(row[x * 4]);
          new_buffer[y][x].getRgb(&red, &green, &blue);
          //color_buffer[x][y].getRgb(&red, &green, &blue);
          px[0] = red;
          px[1] = green;
          px[2] = blue;
          px[3] = 255;
        }
      }
    std::cerr << "point_4\n";

    png_write_image(png, row_pointers);
    png_write_end(png, NULL);

    if (png && info){
       png_destroy_write_struct(&png, &info);
    }

    for(int y = 0; y < height; y++) {
        free(row_pointers[y]);
      }
    free(row_pointers);

    std::cerr << "success: " << success << "\n";
    return success;
}

int PNGImage::load(const std::string &path,
                   std::vector<std::vector<QColor>> &color_buffer)
{
    int width, height;
    png_byte color_type;
    png_byte bit_depth;
    png_bytep *row_pointers = NULL;

    FILE *fp = fopen(path.c_str(), "rb");

      png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
      if(!png) abort();

      png_infop info = png_create_info_struct(png);
      if(!info) abort();

      if(setjmp(png_jmpbuf(png))) abort();

      png_init_io(png, fp);

      png_read_info(png, info);

      width      = png_get_image_width(png, info);
      height     = png_get_image_height(png, info);
      color_type = png_get_color_type(png, info);
      bit_depth  = png_get_bit_depth(png, info);
      std::cerr << " width: " << width << "height: " << height  << " bit_depth: " << bit_depth << "\n";
      std::cerr << "color_type: " << color_type << "\n";


      // Read any color_type into 8bit depth, RGBA format.
      // See http://www.libpng.org/pub/png/libpng-manual.txt

      if(bit_depth == 16)
        png_set_strip_16(png);

      if(color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(png);

      // PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth.
      if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
        png_set_expand_gray_1_2_4_to_8(png);

      if(png_get_valid(png, info, PNG_INFO_tRNS))
        png_set_tRNS_to_alpha(png);

      // These color_type don't have an alpha channel then fill it with 0xff.
      if(color_type == PNG_COLOR_TYPE_RGB ||
         color_type == PNG_COLOR_TYPE_GRAY ||
         color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_filler(png, 0xFF, PNG_FILLER_AFTER);

      if(color_type == PNG_COLOR_TYPE_GRAY ||
         color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
        png_set_gray_to_rgb(png);

      png_read_update_info(png, info);

      if (row_pointers) abort();

      row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
      for(int y = 0; y < height; y++) {
        row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png,info));
      }
      std::cerr << "point_1\n";
      png_read_image(png, row_pointers);
      std::cerr << "point_1.1\n";
      fclose(fp);

      png_destroy_read_struct(&png, &info, NULL);
      png=NULL; info=NULL;

      std::cerr << "point_1.5\n";

      std::vector<std::vector<QColor>> cBuffer(height, std::vector<QColor>(width));

      std::cerr << "point_2\n";

      for(int y = 0; y < height; y++) {
          png_bytep row = row_pointers[y];
          for(int x = 0; x < width; x++) {
            png_bytep px = &(row[x * 4]);
            // Do something awesome for each pixel here...
            //printf("%3d %3d %3d ", px[0], px[1], px[2]);
            cBuffer[y][x].setRgb(px[0], px[1], px[2]);
            //color_buffer[y].push_back(QColor(px[0], px[1], px[2]));
          }
          //std::cerr << "\n";
        }
      std::cerr << "point_3\n";
      color_buffer = cBuffer;

      for(int y = 0; y < height; y++) {
          free(row_pointers[y]);
        }
        free(row_pointers);

    return true;
}
