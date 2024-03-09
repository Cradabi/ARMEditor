#include "bmp_file.h"
#include <fstream>

struct BMP {
    BMPFileHeader file_header;
    BMPInfoHeader bmp_info_header;
};

//void printBMPInfo(BMP& bmp_file) {
//    std::cout << '\n';
//    std::cout << "first header size " << sizeof(bmp_file.file_header);
//    std::cout << '\n';
//    std::cout << "second header size " << bmp_file.bmp_info_header.header_size;
//    std::cout << '\n';
//    std::cout << "offset data " << bmp_file.file_header.offset_data;
//    std::cout << '\n';
//    std::cout << "data size " << bmp_file.file_header.file_size - bmp_file.file_header.offset_data;
//    std::cout << '\n';
//    std::cout << "file size " << bmp_file.file_header.file_size;
//    std::cout << '\n';
//}

void bmpInizialize(BMP& bmp_file, uint16_t x_coords, uint16_t y_coords) {
    bmp_file.bmp_info_header.height = y_coords;
    bmp_file.bmp_info_header.width = x_coords;
    bmp_file.bmp_info_header.size_image = y_coords * x_coords;

    bmp_file.bmp_info_header.header_size = sizeof(bmp_file.bmp_info_header);
    bmp_file.file_header.offset_data =
            sizeof(bmp_file.file_header) + sizeof(bmp_file.bmp_info_header);

    uint64_t d_size = x_coords * 3;

    if (d_size == 0)
        d_size = 4;
    else if (d_size % 4 != 0)
        d_size += 4 - (d_size % 4);

    bmp_file.file_header.file_size = bmp_file.file_header.offset_data + (d_size * y_coords);

//    printBMPInfo(bmp_file);
}

void make_bmp(const std::string outputFile, std::vector<std::vector<ssp::BGRColor>> pixels,
              uint16_t x_coords, uint16_t y_coords) {
    BMP bmp_file;

    bmpInizialize(bmp_file, x_coords, y_coords);

    std::ofstream bmp_fout(outputFile, std::ios_base::binary);
    bmp_fout.write((const char*) &bmp_file.file_header, sizeof(bmp_file.file_header));
    bmp_fout.write((const char*) &bmp_file.bmp_info_header, sizeof(bmp_file.bmp_info_header));

    uint8_t byte;
    for (uint16_t y = 0; y < y_coords; ++y) {
        for (uint16_t x = 0; x < x_coords; ++x) {
            byte = pixels[y][x].blue;
            bmp_fout.write((const char*) &byte, 1);

            byte = pixels[y][x].green;
            bmp_fout.write((const char*) &byte, 1);

            byte = pixels[y][x].red;
            bmp_fout.write((const char*) &byte, 1);
        }

        if ((x_coords * 3) % 4 != 0) {
            byte = 0;
            for (int8_t padding = 0; padding < (4 - ((x_coords * 3) % 4)); ++padding) {
                bmp_fout.write((const char*) &byte, 1);
            }
        }

    }

    bmp_fout.close();
}

