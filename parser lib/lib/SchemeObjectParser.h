#include <cmath>
#include <bitset>

#include <tuple>
#include "lib/SchemeClass.cpp"
#include "SchemeFileNS.h"
#include "parser lib//lib/bmp/BMPFile.cpp"

#pragma once

class SchemeObjectParser {

private:

    // Параметры схемы, экземпляр передаётся из-вне
    Scheme::SchemeParams* scheme_params;

    static sce::TypesSizes types_sizes;
    static sce::SchemeObjectsTypes objects_types;

    char byte;

    static constexpr uint16_t buffer_size{4096};    // Фиксированный размер буфера
    char* buffer = new char[buffer_size];           // Буффер, для работы с байтами

    std::ofstream LogsFile;        // Файл логов
    std::ifstream SchemeFile;      // Файл схемы

    std::ofstream CacheFile;       // Файл для временного хранения кеша объектов

    static constexpr uint8_t int32_flag{0};
    static constexpr uint8_t float_flag{1};
    static constexpr uint8_t double_flag{2};

    uint32_t pictures_counter{0};

    bool getBool(const bool is_buffer_filled = false, uint32_t start_index = 0) {

        bool some_bool;

        // Если буффер не заполнен, то заполняем его
        if (!is_buffer_filled) {
            SchemeFile.read(buffer, 1);
        }

        some_bool = static_cast<bool>(buffer[start_index]);

        return some_bool;
    }

    void getString(std::string& some_string, uint32_t string_size,
                   const bool is_buffer_filled = false, uint32_t start_index = 0) {

        some_string = std::string();

        // Если буффер не заполнен, то заполняем его
        if (!is_buffer_filled) {
            SchemeFile.read(buffer, string_size);
        }

        for (uint32_t _byte = 0; _byte < string_size; ++_byte) {
            some_string += buffer[start_index + _byte];
        }

    }

    // Шаблон получения целочисленного значения из файла
    template<typename IntType>
    IntType getSomeInt(IntType some_int, const uint8_t int_size, const bool is_buffer_filled = false,
                       uint32_t start_index = 0) {

        // Заменяем все байты числа на нулевые, чтобы битовый сдвиг работал корректно
        some_int = 0;

        // Если буффер не заполнен, то заполняем его
        if (!is_buffer_filled) {
            SchemeFile.read(buffer, int_size);
        }

        // Идём по записанным в файл байтам в обратном порядке и доблявляем их в some_int
        for (int8_t _byte = int_size - 1; _byte >= 0; --_byte) {
            some_int |= static_cast<uint8_t>(buffer[start_index + _byte]);

            if (_byte != 0)
                some_int <<= 8;
        }

        return some_int;
    }

    // Шаблон получения числового значения с плавающей точкой из буффера
    template<typename FloatType>
    FloatType getSomeFloat(FloatType some_float, const uint8_t float_size, const bool is_buffer_filled = false,
                           uint32_t start_index = 0) {

        // Если буффер не заполнен, то заполняем его
        if (!is_buffer_filled) {
            SchemeFile.read(buffer, float_size);
        }

        char tmp_float[float_size + 1];
        for (int8_t _byte = 0; _byte < float_size; ++_byte)
            tmp_float[_byte] = buffer[start_index + _byte];

        if (float_size <= types_sizes._32bits)
            some_float = *reinterpret_cast<float*>(tmp_float);
        else
            some_float = *reinterpret_cast<double*>(tmp_float);

        return some_float;
    }

    // Функция получения цвета
    void getColor(sop::BGRColor& color, const bool is_buffer_filled = false, uint32_t start_index = 0) {

        // Если буффер не заполнен, то заполняем его
        if (!is_buffer_filled) {
            SchemeFile.read(buffer, 3);
        }

        color.blue = static_cast<uint8_t>(buffer[start_index++]);
        color.green = static_cast<uint8_t>(buffer[start_index++]);
        color.red = static_cast<uint8_t>(buffer[start_index]);

    }

    void parseObject();

    void getMatrix(std::vector<std::vector<double>>& some_matrix, uint8_t size_y, uint8_t size_x) {

        some_matrix.resize(size_y);
        for (uint8_t y = 0; y < size_y; ++y) {

            some_matrix[y].resize(size_x);
            for (uint8_t x = 0; x < size_x; ++x) {

                some_matrix[y][x] = getSomeFloat(some_matrix[y][x], types_sizes._64bits);

            }
        }

    }

    void getVector(std::vector<int>& some_vector, uint8_t vector_size) {

        some_vector.resize(vector_size, 0);
        for (uint8_t _element = 0; _element < vector_size; ++_element) {
            some_vector[_element] = getSomeInt(some_vector[_element], 4);
        }

    }

    void getPicture(sop::PrimitiveParams& primitive_params, std::string& bmp_filepath);

    void parsePrimitive(sop::ObjectParams& object_params);

//    void parseTextObject();

    void parseStructObject(){

    };

    void parseLibObject(sop::ObjectParams& object_params);

public:

    void set_scheme_params(Scheme::SchemeParams* _scheme_params){
        scheme_params = _scheme_params;
    }

    // Функция открытия рабочих файлов
    bool openWorkFiles(const std::string& schemefile_path, const std::string& logsfile_path) {
        SchemeFile.open(schemefile_path, std::ios_base::binary | std::ios_base::app);

        LogsFile.open(logsfile_path, std::ios_base::app);

        if (!SchemeFile) {
            lae::PrintLog("Парсер объектов: Файл схемы не был открыт", true, 12);
            return false;
        }

        if (!LogsFile) {
            lae::PrintLog("Парсер объектов: Файл логов не был открыт", true, 12);
            return false;
        }

        return true;

    }

    // Главная функция парса объектов
    bool parse(uint32_t infile_cursor, const std::string& schemefile_path, const std::string& logsfile_path) {
        if (!openWorkFiles(schemefile_path, logsfile_path)) {
            return false;
        }

        SchemeFile.clear();
        SchemeFile.seekg(infile_cursor);

        parseObject();

        return true;
    }

};

