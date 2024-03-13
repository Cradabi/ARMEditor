#include "BMPFile.h"

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

        std::ofstream bmp_fout("../parser lib/tmp_pictures/" + outputFile + ".bmp", std::ios_base::binary);

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



