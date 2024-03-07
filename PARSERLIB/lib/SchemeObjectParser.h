#include "SchemeFileNS.h"
#include <cmath>
#include <bitset>

#include "lib/SchemeClass.cpp"

#pragma once

class SchemeObjectParser {

private:
    // Шаблон получения целочисленного значения из буффера
    template<typename IntType>
    void getSomeInt(const char* buffer, IntType& some_int, uint8_t int_size, uint32_t& start_index) {

        some_int = 0;

        for (int8_t i = int_size - 1; i >= 0; --i) {
            some_int |= static_cast<uint8_t>(buffer[start_index + i]);

            if (i != 0)
                some_int <<= 8;
        }

        start_index += int_size;
    }

    // Шаблон получения числового значения с плавающей точкой из буффера
    template<typename FloatType>
    void getSomeFloat(const char* buffer, FloatType& some_float, uint8_t float_size, uint32_t& start_index) {

        char tmp_float[float_size + 1];
        for (int8_t _byte = 0; _byte < float_size; ++_byte)
            tmp_float[_byte] = buffer[start_index + _byte];

        if (float_size <= 4)
            some_float = *reinterpret_cast<float*>(tmp_float);
        else
            some_float = *reinterpret_cast<double*>(tmp_float);

        start_index += float_size;
    }

    //
    void getColor(const char* buffer, ssp::BGRColor& color, uint32_t& start_index, bool is_rgb = false) {
        if (is_rgb) {
            color.red = static_cast<uint8_t>(buffer[start_index++]);
            color.green = static_cast<uint8_t>(buffer[start_index++]);
            color.blue = static_cast<uint8_t>(buffer[start_index++]);
        } else {
            color.blue = static_cast<uint8_t>(buffer[start_index++]);
            color.green = static_cast<uint8_t>(buffer[start_index++]);
            color.red = static_cast<uint8_t>(buffer[start_index++]);
        }
    }

    // TODO Сделать типизированную функцию получения инфы о шрифте
    // TODO В функцию передавать по ссылке все нужные переменные
//    void getFontInfo(const char* buffer, uint32_t& bytes_counter, uint32_t& font_size, ...){
//
//        getSomeInt(buffer, font_size, 4, bytes_counter);
//
//        uint8_t bold_bool = static_cast<uint8_t>(buffer[bytes_counter++]);
//
//        uint8_t italic_bool = static_cast<uint8_t>(buffer[bytes_counter++]);
//
//        uint8_t underlined_bool = static_cast<uint8_t>(buffer[bytes_counter++]);
//
//        uint32_t font_name_length;
//        getSomeInt(buffer, font_name_length, 4, bytes_counter);
//
//        std::string font_name;
//        for (int i = bytes_counter; i < font_name_length + bytes_counter; ++i) {
//            font_name += buffer[i];
//        }
//        bytes_counter += font_name_length;
//
//        ssp::BGRColor font_color;
//        getColor(font_color);
//
//        uint8_t font_align_horz = static_cast<uint8_t>(buffer[bytes_counter++]);
//        uint8_t font_align_vert = static_cast<uint8_t>(buffer[bytes_counter++]);
//        bytes_counter += 2; //MB цвет заливки
//
//        uint8_t font_autosize = static_cast<uint8_t>(buffer[bytes_counter++]);
//
//        uint32_t font_width;
//        getSomeInt(buffer, font_width, 4, bytes_counter);
//
//        uint32_t font_height;
//        getSomeInt(buffer, font_height, 4, bytes_counter);
//
//        uint32_t font_descent;
//        getSomeInt(buffer, font_descent, 4, bytes_counter);
//    }

public:

    void parseNone(const char* buffer, Scheme::SchemeParams& scheme_params, const uint32_t block_size, int id_pos);

    void parseEllips(const char* buffer, Scheme::SchemeParams& scheme_params, const uint32_t block_size, int id_pos);

    void parseGoBtn(const char* buffer, Scheme::SchemeParams& scheme_params, const uint32_t block_size, int id_pos);

    void parseGoPoint(const char* buffer, Scheme::SchemeParams& scheme_params, const uint32_t block_size, int id_pos);

    void parseGluePoint(const char* buffer, Scheme::SchemeParams& scheme_params, const uint32_t block_size, int id_pos);

    void parseLine(const char* buffer, Scheme::SchemeParams& scheme_params, const uint32_t block_size, int id_pos);

    void parseText(const char* buffer, Scheme::SchemeParams& scheme_params, const uint32_t block_size, int id_pos);

    void parsePolygon(const char* buffer, Scheme::SchemeParams& scheme_params, const uint32_t block_size, int id_pos);

    void parseRectangle(const char* buffer, Scheme::SchemeParams& scheme_params, const uint32_t block_size, int id_pos);

    void parseArc(const char* buffer, Scheme::SchemeParams& scheme_params, const uint32_t block_size, int id_pos);

    void parseTelecontrol(const char* buffer, Scheme::SchemeParams& scheme_params, const uint32_t block_size, int id_pos);

    void parseTelemeasure(const char* buffer, Scheme::SchemeParams& scheme_params, const uint32_t block_size, int id_pos);

    void parseSignal(const char* buffer, Scheme::SchemeParams& scheme_params, const uint32_t block_size, int id_pos);

    void parsePicture(const char* buffer, Scheme::SchemeParams& scheme_params, const uint32_t block_size, int id_pos);

    void parseShape(const char* buffer, Scheme::SchemeParams& scheme_params, const uint32_t block_size, int id_pos);
};

