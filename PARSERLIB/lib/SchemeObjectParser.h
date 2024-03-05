#include "SchemeFileNS.h"
#include <cmath>
#include <bitset>

#include "lib/SchemeClass.cpp"

#pragma once

class SchemeObjectParser {

private:
    // Шаблон получения числового значения из буффера (some_int ОБЯЗАТЕЛЬНО должен иметь нулевое значение!)
    template<typename IntType>
    IntType GetSomeInt(char* buffer, IntType some_int, uint8_t block_size, uint32_t start_index = 0) {

        for (int8_t i = block_size - 1; i >= 0; --i) {
            some_int |= static_cast<uint8_t>(buffer[start_index + i]);

            if (i != 0)
                some_int <<= 8;
        }

        return some_int;
    }

public:

    void ParseEllips(char* buffer, Scheme::SchemeParams& scheme_params, const uint32_t& block_size, int id_pos) {

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

        bytes_counter = id_pos + 4;

        uint32_t id = 0;
        for (uint32_t i = bytes_counter + 3; i >= bytes_counter; --i) {
            id |= static_cast<uint8_t>(buffer[i]);

            if (i != bytes_counter)
                id <<= 8;
        }

        bytes_counter += 16; //

        uint32_t half_x = 0;
        for (uint32_t i = bytes_counter + 3; i >= bytes_counter; --i) {
            half_x |= static_cast<uint8_t>(buffer[i]);

            if (i != bytes_counter)
                half_x <<= 8;
        }

        bytes_counter += 12;

        uint32_t half_y = GetSomeInt(buffer, 0, 4, bytes_counter);

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

        bool brush_style;
        brush_style = static_cast<bool>(buffer[bytes_counter++]);

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
                            brush_style));

    }

    void ParseNone(char* buffer, Scheme::SchemeParams& scheme_params, uint32_t block_size, int id_pos) {
        ;
    }

    void ParseGoBtn(char* buffer, Scheme::SchemeParams& scheme_params, uint32_t block_size, int id_pos) {
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

        bytes_counter = id_pos + 4;

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


        scheme_params.objects_vector.push_back(
                new TransitionButton(0, center_x - half_x, center_y - half_y,
                                     half_x * 2, half_y * 2, angle,
                                     {brush.red, brush.green, brush.blue},
                                     " Кнопка перехода ", true, 1));

    }

    void ParseGoPoint(char* buffer, Scheme::SchemeParams& scheme_params, uint32_t block_size, int id_pos) {
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


        bytes_counter = id_pos + 4;

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


        scheme_params.objects_vector.push_back(
                new TransitionPoint(0, center_x - half_x, center_y - half_y,
                                    half_x * 2, half_y * 2,
                                    {pen.red, pen.green, pen.blue},
                                    " Точка перехода ", true, 0));
    }

    void ParseGluePoint(char* buffer, Scheme::SchemeParams& scheme_params, uint32_t block_size, int id_pos) {
        ;
    }

    void ParseLine(char* buffer, Scheme::SchemeParams& scheme_params, uint32_t block_size, int id_pos) {
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

        bytes_counter = id_pos + 4;

        uint32_t id = 0;
        for (uint32_t i = bytes_counter + 3; i >= bytes_counter; --i) {
            id |= static_cast<uint8_t>(buffer[i]);

            if (i != bytes_counter)
                id <<= 8;
        }

        bytes_counter += 8; //

        int32_t cord_x1 = GetSomeInt(buffer, 0, 4, bytes_counter);

        bytes_counter += 4;

        int32_t cord_y1 = GetSomeInt(buffer, 0, 4, bytes_counter);

        bytes_counter += 4;

        int32_t cord_x2 = GetSomeInt(buffer, 0, 4, bytes_counter);

        bytes_counter += 4;

        int32_t cord_y2 = GetSomeInt(buffer, 0, 4, bytes_counter);

        bytes_counter += 6;

        ssp::BGRColor pen;
        pen.blue = static_cast<uint8_t>(buffer[bytes_counter++]);
        pen.green = static_cast<uint8_t>(buffer[bytes_counter++]);
        pen.red = static_cast<uint8_t>(buffer[bytes_counter++]);

        bytes_counter += 7;

        bool brush_style;
        brush_style = static_cast<bool>(buffer[bytes_counter++]);

        uint8_t line_style;
        line_style = static_cast<uint8_t>(buffer[bytes_counter++]);

        uint8_t width;
        width = static_cast<uint8_t>(buffer[bytes_counter]);

        bytes_counter += 5;

        uint8_t end_arrow_style = static_cast<uint8_t> (buffer[bytes_counter++]);

        uint8_t start_arrow_style = static_cast<uint8_t> (buffer[bytes_counter]);

        scheme_params.objects_vector.push_back(
                new Line((int) round(center_x + cord_x1), (int) round(center_y + cord_y1),
                         (int) round(center_x + cord_x2), (int) round(center_y + cord_y2), "", "Линия",
                         true,
                         line_style, 0, width, start_arrow_style, end_arrow_style, {pen.red, pen.green, pen.blue}));
    }

    void ParseText(char* buffer, Scheme::SchemeParams& scheme_params, uint32_t block_size, int id_pos) {

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

        bytes_counter = id_pos + 4;

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

        bool brush_style;
        brush_style = static_cast<bool>(buffer[bytes_counter++]);

        uint8_t line_style;
        line_style = static_cast<uint8_t>(buffer[bytes_counter++]);

        uint8_t width;
        width = static_cast<uint8_t>(buffer[bytes_counter++]);

        uint32_t text_length = 0;
        for (uint32_t i = bytes_counter + 3; i >= bytes_counter; --i) {
            text_length |= static_cast<uint8_t>(buffer[i]);

            if (i != bytes_counter)
                text_length <<= 8;
        }
        bytes_counter += 4;

        std::string text;
        for (int i = bytes_counter; i < text_length + bytes_counter; ++i) {
            text += buffer[i];
        }
        bytes_counter += text_length;

        bytes_counter += 4;

        uint8_t font_bool = static_cast<uint8_t>(buffer[bytes_counter++]);

        if (font_bool) {
            uint32_t font_size = GetSomeInt(buffer, 0, 4, bytes_counter);

            bytes_counter += 4;

            uint8_t bold_bool = static_cast<uint8_t>(buffer[bytes_counter++]);

            uint8_t italic_bool = static_cast<uint8_t>(buffer[bytes_counter++]);

            uint8_t underlined_bool = static_cast<uint8_t>(buffer[bytes_counter++]);

            uint32_t font_name_length = GetSomeInt(buffer, 0, 4, bytes_counter);
            bytes_counter += 4;
            std::string font_name;
            for (int i = bytes_counter; i < font_name_length + bytes_counter; ++i) {
                font_name += buffer[i];
            }
            bytes_counter += font_name_length;

            ssp::BGRColor font_color;
            font_color.blue = static_cast<uint8_t>(buffer[bytes_counter++]);
            font_color.green = static_cast<uint8_t>(buffer[bytes_counter++]);
            font_color.red = static_cast<uint8_t>(buffer[bytes_counter++]);

            uint8_t font_align_horz = static_cast<uint8_t>(buffer[bytes_counter++]);
            uint8_t font_align_vert = static_cast<uint8_t>(buffer[bytes_counter++]);
            bytes_counter += 2; //MB цвет заливки

            uint8_t font_autosize = static_cast<uint8_t>(buffer[bytes_counter++]);

            uint32_t font_width = GetSomeInt(buffer, 0, 4, bytes_counter);

            bytes_counter += 4;

            uint32_t font_height = GetSomeInt(buffer, 0, 4, bytes_counter);

            bytes_counter += 4;

            uint32_t font_descent = GetSomeInt(buffer, 0, 4, bytes_counter);

            scheme_params.objects_vector.push_back(
                    new Text((int) round(center_x - half_x), (int) round(center_y - half_y), half_x * 2, half_y * 2,
                             (360 - (int) angle) % 360,
                             text, " Текст ", line_style,
                             {brush.red, brush.green, brush.blue},
                             1, brush_style, font_name, font_size,
                             {font_color.red, font_color.green, font_color.blue},
                             font_align_horz, font_align_vert, bold_bool, italic_bool, underlined_bool, 0,
                             font_autosize));
        }
    }

    void ParsePolygon(char* buffer, Scheme::SchemeParams& scheme_params, uint32_t block_size, int id_pos) {
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

        bytes_counter = id_pos + 4;

        uint32_t id = 0;
        for (uint32_t i = bytes_counter + 3; i >= bytes_counter; --i) {
            id |= static_cast<uint8_t>(buffer[i]);

            if (i != bytes_counter)
                id <<= 8;
        }

        bytes_counter += 4;

        uint32_t amount_of_dots = GetSomeInt(buffer, 0, 4, bytes_counter);

        bytes_counter += 4;

        bool end_polygon = false;
        std::vector<std::vector<int>>coords;
        for (int32_t i = 0; i < amount_of_dots; ++i){
            std::vector<int>pair;
            int32_t x = GetSomeInt(buffer, 0, 4, bytes_counter);
            bytes_counter += 4;
            int32_t y = GetSomeInt(buffer, 0, 4, bytes_counter);
            bytes_counter += 4;
            if (i == amount_of_dots - 1 and center_x + x == coords[0][0] and center_y + y == coords[0][1]){
                    end_polygon = true;
            } else {
                std::vector<int> pair_coords;
                coords.push_back(pair_coords);
                coords[i].push_back(center_x + x);
                coords[i].push_back(center_y + y);
            }
        }
        bytes_counter +=2;

        ssp::BGRColor pen;
        pen.blue = static_cast<uint8_t>(buffer[bytes_counter++]);
        pen.green = static_cast<uint8_t>(buffer[bytes_counter++]);
        pen.red = static_cast<uint8_t>(buffer[bytes_counter++]);

        ssp::BGRColor brush;
        brush.blue = static_cast<uint8_t>(buffer[bytes_counter++]);
        brush.green = static_cast<uint8_t>(buffer[bytes_counter++]);
        brush.red = static_cast<uint8_t>(buffer[bytes_counter++]);

        bytes_counter += 4;

        bool brush_style;
        brush_style = static_cast<bool>(buffer[bytes_counter++]);

        uint8_t line_style;
        line_style = static_cast<uint8_t>(buffer[bytes_counter++]);

        uint8_t width;
        width = static_cast<uint8_t>(buffer[bytes_counter++]);

        uint32_t text_length = 0;
        for (uint32_t i = bytes_counter + 3; i >= bytes_counter; --i) {
            text_length |= static_cast<uint8_t>(buffer[i]);

            if (i != bytes_counter)
                text_length <<= 8;
        }
        bytes_counter += 4;

        std::string text;
        for (int i = bytes_counter; i < text_length + bytes_counter; ++i) {
            text += buffer[i];
        }
        bytes_counter += text_length;

        scheme_params.objects_vector.push_back(
                new Polygon(coords, end_polygon,
                              (360 - (int) angle) % 360,
                              width, line_style, " Прямоугольник ",
                              {pen.red, pen.green, pen.blue},
                            {brush.red, brush.green, brush.blue},
                               true, brush_style));
    }

    void ParseRectangle(char* buffer, Scheme::SchemeParams& scheme_params, uint32_t block_size, int id_pos) {

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

        bytes_counter = id_pos + 4;

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

        bool brush_style;
        brush_style = static_cast<bool>(buffer[bytes_counter++]);

        uint8_t line_style;
        line_style = static_cast<uint8_t>(buffer[bytes_counter++]);

        uint8_t width;
        width = static_cast<uint8_t>(buffer[bytes_counter]);

        scheme_params.objects_vector.push_back(
                new Rectangle(center_x - half_x, center_y - half_y, half_x * 2, half_y * 2,
                              (360 - (int) angle) % 360,
                              width, line_style,
                              {pen.red, pen.green, pen.blue},
                              " Прямоугольник ", true, 0, 0,
                              {brush.red, brush.green, brush.blue},
                              brush_style));

    }

    void ParseDuga(char* buffer, Scheme::SchemeParams& scheme_params, uint32_t block_size, int id_pos) {
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

        bytes_counter = id_pos + 4;

        uint32_t id = 0;
        for (uint32_t i = bytes_counter + 3; i >= bytes_counter; --i) {
            id |= static_cast<uint8_t>(buffer[i]);

            if (i != bytes_counter)
                id <<= 8;
        }

        bytes_counter += 16; //

        uint32_t half_x = 0;
        for (uint32_t i = bytes_counter + 3; i >= bytes_counter; --i) {
            half_x |= static_cast<uint8_t>(buffer[i]);

            if (i != bytes_counter)
                half_x <<= 8;
        }

        bytes_counter += 20;

        uint32_t half_y = GetSomeInt(buffer, 0, 4, bytes_counter);

        bytes_counter += 4;

        uint32_t start_angle = GetSomeInt(buffer, 0, 4, bytes_counter);

        bytes_counter += 4;

        uint32_t end_angle = GetSomeInt(buffer, 0, 4, bytes_counter);

        bytes_counter += 6;

        ssp::BGRColor pen;
        pen.blue = static_cast<uint8_t>(buffer[bytes_counter++]);
        pen.green = static_cast<uint8_t>(buffer[bytes_counter++]);
        pen.red = static_cast<uint8_t>(buffer[bytes_counter++]);

        ssp::BGRColor brush;
        brush.blue = static_cast<uint8_t>(buffer[bytes_counter++]);
        brush.green = static_cast<uint8_t>(buffer[bytes_counter++]);
        brush.red = static_cast<uint8_t>(buffer[bytes_counter++]);

        bytes_counter += 4;

        bool brush_style;
        brush_style = static_cast<bool>(buffer[bytes_counter++]);

        uint8_t line_style;
        line_style = static_cast<uint8_t>(buffer[bytes_counter++]);

        uint8_t width;
        width = static_cast<uint8_t>(buffer[bytes_counter]);

        scheme_params.objects_vector.push_back(
                new Arc(center_x - half_x, center_y - half_y, half_x * 2, half_y * 2,
                        (360 - (int) angle) % 360, start_angle, end_angle,
                        width, line_style,
                        {pen.red, pen.green, pen.blue},
                        " Дуга ",
                        true,
                        {brush.red, brush.green, brush.blue},
                        brush_style));
    }

    void ParseTeleupr(char* buffer, Scheme::SchemeParams& scheme_params, uint32_t block_size, int id_pos) {

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

        bytes_counter = id_pos + 4;

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

        bool brush_style;
        brush_style = static_cast<bool>(buffer[bytes_counter++]);

        uint8_t line_style;
        line_style = static_cast<uint8_t>(buffer[bytes_counter++]);

        uint8_t width;
        width = static_cast<uint8_t>(buffer[bytes_counter++]);

        uint32_t text_length = 0;
        for (uint32_t i = bytes_counter + 3; i >= bytes_counter; --i) {
            text_length |= static_cast<uint8_t>(buffer[i]);

            if (i != bytes_counter)
                text_length <<= 8;
        }
        bytes_counter += 4;

        std::string text;
        for (int i = bytes_counter; i < text_length + bytes_counter; ++i) {
            text += buffer[i];
        }
        bytes_counter += text_length;

        bytes_counter += 4;

        uint8_t font_bool = static_cast<uint8_t>(buffer[bytes_counter++]);

        if (font_bool) {
            uint32_t font_size = GetSomeInt(buffer, 0, 4, bytes_counter);

            bytes_counter += 4;

            uint8_t bold_bool = static_cast<uint8_t>(buffer[bytes_counter++]);

            uint8_t italic_bool = static_cast<uint8_t>(buffer[bytes_counter++]);

            uint8_t underlined_bool = static_cast<uint8_t>(buffer[bytes_counter++]);

            uint32_t font_name_length = GetSomeInt(buffer, 0, 4, bytes_counter);
            bytes_counter += 4;
            std::string font_name;
            for (int i = bytes_counter; i < font_name_length + bytes_counter; ++i) {
                font_name += buffer[i];
            }
            bytes_counter += font_name_length;

            ssp::BGRColor font_color;
            font_color.blue = static_cast<uint8_t>(buffer[bytes_counter++]);
            font_color.green = static_cast<uint8_t>(buffer[bytes_counter++]);
            font_color.red = static_cast<uint8_t>(buffer[bytes_counter++]);

            uint8_t font_align_horz = static_cast<uint8_t>(buffer[bytes_counter++]);
            uint8_t font_align_vert = static_cast<uint8_t>(buffer[bytes_counter++]);
            bytes_counter += 2; //MB цвет заливки

            uint8_t font_autosize = static_cast<uint8_t>(buffer[bytes_counter++]);

            uint32_t font_width = GetSomeInt(buffer, 0, 4, bytes_counter);

            bytes_counter += 4;

            uint32_t font_height = GetSomeInt(buffer, 0, 4, bytes_counter);

            bytes_counter += 4;

            uint32_t font_descent = GetSomeInt(buffer, 0, 4, bytes_counter);

            scheme_params.objects_vector.push_back(
                    new Telecontrol((int) round(center_x - half_x), (int) round(center_y - half_y), half_x * 2,
                                    half_y * 2,
                                    (360 - (int) angle) % 360,
                                    text, " Телеуправление ", line_style,
                                    {brush.red, brush.green, brush.blue},
                                    1, brush_style, font_name, font_size,
                                    {font_color.red, font_color.green, font_color.blue},
                                    font_align_horz, font_align_vert, bold_bool, italic_bool, underlined_bool, 0,
                                    font_autosize));
        }

    }

    void ParseTeleizm(char* buffer, Scheme::SchemeParams& scheme_params, uint32_t block_size, int id_pos) {
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

        bytes_counter = id_pos + 4;

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

        bool brush_style;
        brush_style = static_cast<bool>(buffer[bytes_counter++]);

        uint8_t line_style;
        line_style = static_cast<uint8_t>(buffer[bytes_counter++]);

        uint8_t width;
        width = static_cast<uint8_t>(buffer[bytes_counter++]);

        uint32_t text_length = 0;
        for (uint32_t i = bytes_counter + 3; i >= bytes_counter; --i) {
            text_length |= static_cast<uint8_t>(buffer[i]);

            if (i != bytes_counter)
                text_length <<= 8;
        }
        bytes_counter += 4;

        std::string text;
        for (int i = bytes_counter; i < text_length + bytes_counter; ++i) {
            text += buffer[i];
        }
        bytes_counter += text_length;

        bytes_counter += 4;

        uint8_t font_bool = static_cast<uint8_t>(buffer[bytes_counter++]);

        if (font_bool) {
            uint32_t font_size = GetSomeInt(buffer, 0, 4, bytes_counter);

            bytes_counter += 4;

            uint8_t bold_bool = static_cast<uint8_t>(buffer[bytes_counter++]);

            uint8_t italic_bool = static_cast<uint8_t>(buffer[bytes_counter++]);

            uint8_t underlined_bool = static_cast<uint8_t>(buffer[bytes_counter++]);

            uint32_t font_name_length = GetSomeInt(buffer, 0, 4, bytes_counter);
            bytes_counter += 4;
            std::string font_name;
            for (int i = bytes_counter; i < font_name_length + bytes_counter; ++i) {
                font_name += buffer[i];
            }
            bytes_counter += font_name_length;

            ssp::BGRColor font_color;
            font_color.blue = static_cast<uint8_t>(buffer[bytes_counter++]);
            font_color.green = static_cast<uint8_t>(buffer[bytes_counter++]);
            font_color.red = static_cast<uint8_t>(buffer[bytes_counter++]);

            uint8_t font_align_horz = static_cast<uint8_t>(buffer[bytes_counter++]);
            uint8_t font_align_vert = static_cast<uint8_t>(buffer[bytes_counter++]);
            bytes_counter += 2; //MB цвет заливки

            uint8_t font_autosize = static_cast<uint8_t>(buffer[bytes_counter++]);

            uint32_t font_width = GetSomeInt(buffer, 0, 4, bytes_counter);

            bytes_counter += 4;

            uint32_t font_height = GetSomeInt(buffer, 0, 4, bytes_counter);

            bytes_counter += 4;

            uint32_t font_descent = GetSomeInt(buffer, 0, 4, bytes_counter);

            scheme_params.objects_vector.push_back(
                    new Telemeasure((int) round(center_x - half_x), (int) round(center_y - half_y), half_x * 2,
                                    half_y * 2,
                                    (360 - (int) angle) % 360,
                                    text, " Телеизмерение ", line_style,
                                    {brush.red, brush.green, brush.blue},
                                    1, brush_style, font_name, font_size,
                                    {font_color.red, font_color.green, font_color.blue},
                                    font_align_horz, font_align_vert, bold_bool, italic_bool, underlined_bool, 0,
                                    font_autosize));
        }
    }

    void ParseSignal(char* buffer, Scheme::SchemeParams& scheme_params, uint32_t block_size, int id_pos) {
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

        bytes_counter = id_pos + 4;

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

        bool brush_style;
        brush_style = static_cast<bool>(buffer[bytes_counter++]);

        uint8_t line_style;
        line_style = static_cast<uint8_t>(buffer[bytes_counter++]);

        uint8_t width;
        width = static_cast<uint8_t>(buffer[bytes_counter++]);

        uint32_t text_length = 0;
        for (uint32_t i = bytes_counter + 3; i >= bytes_counter; --i) {
            text_length |= static_cast<uint8_t>(buffer[i]);

            if (i != bytes_counter)
                text_length <<= 8;
        }
        bytes_counter += 4;

        std::string text;
        for (int i = bytes_counter; i < text_length + bytes_counter; ++i) {
            text += buffer[i];
        }
        bytes_counter += text_length;

        bytes_counter += 4;

        uint8_t font_bool = static_cast<uint8_t>(buffer[bytes_counter++]);

        if (font_bool) {
            uint32_t font_size = GetSomeInt(buffer, 0, 4, bytes_counter);

            bytes_counter += 4;

            uint8_t bold_bool = static_cast<uint8_t>(buffer[bytes_counter++]);

            uint8_t italic_bool = static_cast<uint8_t>(buffer[bytes_counter++]);

            uint8_t underlined_bool = static_cast<uint8_t>(buffer[bytes_counter++]);

            uint32_t font_name_length = GetSomeInt(buffer, 0, 4, bytes_counter);
            bytes_counter += 4;
            std::string font_name;
            for (int i = bytes_counter; i < font_name_length + bytes_counter; ++i) {
                font_name += buffer[i];
            }
            bytes_counter += font_name_length;

            ssp::BGRColor font_color;
            font_color.blue = static_cast<uint8_t>(buffer[bytes_counter++]);
            font_color.green = static_cast<uint8_t>(buffer[bytes_counter++]);
            font_color.red = static_cast<uint8_t>(buffer[bytes_counter++]);

            uint8_t font_align_horz = static_cast<uint8_t>(buffer[bytes_counter++]);
            uint8_t font_align_vert = static_cast<uint8_t>(buffer[bytes_counter++]);
            bytes_counter += 2; //MB цвет заливки

            uint8_t font_autosize = static_cast<uint8_t>(buffer[bytes_counter++]);

            uint32_t font_width = GetSomeInt(buffer, 0, 4, bytes_counter);

            bytes_counter += 4;

            uint32_t font_height = GetSomeInt(buffer, 0, 4, bytes_counter);

            bytes_counter += 4;

            uint32_t font_descent = GetSomeInt(buffer, 0, 4, bytes_counter);

            scheme_params.objects_vector.push_back(
                    new Telesignalisation((int) round(center_x - half_x), (int) round(center_y - half_y), half_x * 2,
                                    half_y * 2,
                                    (360 - (int) angle) % 360,
                                    text, " Телесигнализация ", line_style,
                                    {brush.red, brush.green, brush.blue},
                                    1, brush_style, font_name, font_size,
                                    {font_color.red, font_color.green, font_color.blue},
                                    font_align_horz, font_align_vert, bold_bool, italic_bool, underlined_bool, 0,
                                    font_autosize));
        }
    }

    void ParsePicture(char* buffer, Scheme::SchemeParams& scheme_params, uint32_t block_size, int id_pos) {
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

        bytes_counter = id_pos + 4;

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

        bool brush_style;
        brush_style = static_cast<bool>(buffer[bytes_counter++]);

        uint8_t line_style;
        line_style = static_cast<uint8_t>(buffer[bytes_counter++]);

        uint8_t width;
        width = static_cast<uint8_t>(buffer[bytes_counter++]);

        uint32_t text_length = 0;
        for (uint32_t i = bytes_counter + 3; i >= bytes_counter; --i) {
            text_length |= static_cast<uint8_t>(buffer[i]);

            if (i != bytes_counter)
                text_length <<= 8;
        }
        bytes_counter += 4;

        std::string text;
        for (int i = bytes_counter; i < text_length + bytes_counter; ++i) {
            text += buffer[i];
        }
        bytes_counter += text_length;

        bytes_counter += 89;

        uint8_t not_scale;
        not_scale = static_cast<uint8_t>(buffer[bytes_counter++]);

        uint8_t is_picture;
        is_picture = static_cast<uint8_t>(buffer[bytes_counter++]);

        uint32_t width_of_picture = GetSomeInt(buffer, 0, 4, bytes_counter);

        bytes_counter += 4;

        uint32_t height_of_picture = GetSomeInt(buffer, 0, 4, bytes_counter);

        bytes_counter += 4;

        uint8_t bit_depth;
        bit_depth = static_cast<uint8_t>(buffer[bytes_counter++]);

        std::vector<std::vector<ssp::BGRColor>>bitmap;
        for (uint32_t x = 0; x < width_of_picture; ++x){
            std::vector<ssp::BGRColor> pixel_line;
            bitmap.push_back(pixel_line);
            for(uint32_t y = 0; y < height_of_picture; ++y){
                ssp::BGRColor pixel;
                pixel.blue = static_cast<uint8_t>(buffer[bytes_counter++]);
                pixel.green = static_cast<uint8_t>(buffer[bytes_counter++]);
                pixel.red = static_cast<uint8_t>(buffer[bytes_counter++]);
                bitmap[x].push_back(pixel);
            }
            bytes_counter += 2;
        }
        //TODO написать передачу картинки в кутэ

    }

    void ParseShape(char* buffer, Scheme::SchemeParams& scheme_params, uint32_t block_size, int id_pos) {
        ;
    }
};

