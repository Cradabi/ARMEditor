#include "SchemeObjectNS.h"
#include "SchemeFileNS.h"

#include <bitset>

#include "lib/SchemeClass.cpp"

#pragma once

class SchemeObjectParser {
private:
    char byte;      // Байт для работы с данными объекта

public:

    void ParseELLIPS(char* buffer, Scheme::SchemeParams& scheme_params, const uint32_t& block_size) {

        uint32_t bytes_counter = 16;

        char tmp_center_x[9];
        for (int8_t _byte = 0; _byte < 8; ++_byte)
            tmp_center_x[_byte] = buffer[bytes_counter + _byte];

        double center_x = *reinterpret_cast<double*>(tmp_center_x);

        bytes_counter += 24;

        char tmp_center_y[9];
        for (int8_t _byte = 0; _byte < 8; ++_byte)
            tmp_center_y[_byte] = buffer[bytes_counter + _byte];
        double center_y = *reinterpret_cast<double*>(tmp_center_y);

        bytes_counter += 32;

        char tmp_angle[9];
        for (int8_t _byte = 0; _byte < 8; ++_byte)
            tmp_angle[_byte] = buffer[bytes_counter + _byte];
        double angle = *reinterpret_cast<double*>(tmp_angle);

        bytes_counter = 576;

        uint32_t id = 0;
        for (uint32_t i = bytes_counter + 3; i >= bytes_counter; --i) {
            id |= static_cast<uint8_t>(buffer[i]);

            if (i != bytes_counter)
                id <<= 8;
        }

        bytes_counter += 16;

        uint32_t half_x = 0;
        for (uint32_t i = bytes_counter + 3; i >= bytes_counter; --i) {
            half_x |= static_cast<uint8_t>(buffer[i]);

            if (i != bytes_counter)
                half_x <<= 8;
        }

        bytes_counter += 12;

        uint32_t half_y = 0;
        for (uint32_t i = bytes_counter + 3; i >= bytes_counter; --i) {
            half_y |= static_cast<uint8_t>(buffer[i]);

            if (i != bytes_counter)
                half_y <<= 8;
        }

        bytes_counter += 14;

        ssp::BGRColor pen;
        pen.blue = static_cast<uint8_t>(buffer[bytes_counter++]);
        pen.green = static_cast<uint8_t>(buffer[bytes_counter++]);
        pen.red = static_cast<uint8_t>(buffer[bytes_counter++]);

        ssp::BGRColor brush;
        brush.blue = static_cast<uint8_t>(buffer[bytes_counter++]);
        brush.green = static_cast<uint8_t>(buffer[bytes_counter++]);
        brush.red = static_cast<uint8_t>(buffer[bytes_counter++]);

        bytes_counter += 4;

        uint8_t brush_style;
        brush_style = static_cast<uint8_t>(buffer[bytes_counter++]);

        uint8_t line_style;
        line_style = static_cast<uint8_t>(buffer[bytes_counter++]);

        uint8_t width;
        width = static_cast<uint8_t>(buffer[bytes_counter]);

        scheme_params.objects_vector.push_back(
                new Ellipse(center_x - half_x, center_y - half_y, half_x * 2, half_y * 2,
                            (360 - (int) angle) % 360,
                            width, line_style,
                            {pen.red, pen.green, pen.blue},
                            " Эллипс ",
                            true,
                            {brush.red, brush.green, brush.blue},
                            true));

    }

};

