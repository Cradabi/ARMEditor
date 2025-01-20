#include <fstream>
#include <vector>

#include "parser_lib/src/SchemeFileNS.h"

#pragma once

#pragma pack(push, 1)

struct BMPFileHeader {
    uint16_t file_type{0x4D42};          // File type always BM which is 0x4D42
    uint32_t file_size{0};               // Size of the file (in bytes)
    uint32_t reserved{0};                // Reserved, always 0
    uint32_t offset_data{0};             // Start position of pixel data (bytes from the beginning of the file)
};


struct BMPInfoHeader {
    uint32_t header_size{0};               // Size of this header (in bytes)
    uint32_t width{0};                     // width of bitmap in pixels
    uint32_t height{0};                    // height of bitmap in pixels
    uint16_t planes{1};                    // No. of planes for the target device, this is always 1
    uint16_t bits_per_pixel{32};           // No. of bits per pixel
    uint32_t compression{0};
    uint32_t size_image{0};                // 0 - for uncompressed images
    uint32_t x_pixels_per_meter{0};
    uint32_t y_pixels_per_meter{0};
    uint32_t colors_used{0};
    // No. color indexes in the color table. Use 0 for the max number of colors allowed by bit_count
    uint32_t colors_important{0};
    // No. of colors used for displaying the bitmap. If 0 all colors are required
};

#pragma pack(pop)

struct BMP {
private:
    BMPFileHeader file_header;
    BMPInfoHeader bmp_info_header;

    void bmpInizialize(uint16_t x_coords, uint16_t y_coords) {
        bmp_info_header.height = y_coords;
        bmp_info_header.width = x_coords;
        bmp_info_header.size_image = y_coords * (x_coords * 4);

        bmp_info_header.header_size = sizeof(bmp_info_header);
        file_header.offset_data =
                sizeof(file_header) + sizeof(bmp_info_header);

        uint64_t d_size = x_coords * 4;

        if (d_size == 0)
            d_size = 4;

        file_header.file_size = file_header.offset_data + (d_size * y_coords);
    }

public:
    void makeBmp(const std::string outputFile, std::vector<std::vector<sop::BGRColor>> pixels) {

        uint16_t y_coords = pixels.size();
        uint16_t x_coords = pixels.back().size();

        bmpInizialize(x_coords, y_coords);

        std::ofstream bmp_fout("../parser_lib/cache/tmp_pictures/" + outputFile + ".bmp", std::ios_base::binary);

        bmp_fout.write((const char*) &file_header, sizeof(file_header));
        bmp_fout.write((const char*) &bmp_info_header, sizeof(bmp_info_header));

        uint8_t byte;
        for (int64_t y = y_coords - 1; y >= 0; --y) {
            for (uint32_t x = 0; x < x_coords; ++x) {
                byte = pixels[y][x].blue;
                bmp_fout << byte;

                byte = pixels[y][x].green;
                bmp_fout << byte;

                byte = pixels[y][x].red;
                bmp_fout << byte;

                byte = 0;
                bmp_fout << byte;
            }
        }
        bmp_fout.close();
    }
};