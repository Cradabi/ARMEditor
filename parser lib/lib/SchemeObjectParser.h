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
    static sce::SchemePrimitiveTypes objects_types;

    char byte;

    static constexpr uint16_t buffer_size{4096};    // Фиксированный размер буфера
    char buffer[buffer_size];                       // Буффер, для работы с байтами

    std::ofstream LogsFile;        // Файл логов
    std::ifstream SchemeFile;      // Файл схемы

    const std::string cachefile_path = "../parser lib/cache/tmp.cache";
    std::ofstream CacheFileOut;       // Файл для временного хранения кеша объектов
    std::ifstream CacheFileIn;       // Файл для временного хранения кеша объектов
    bool is_cache_open{false};

    static constexpr uint8_t int32_flag{0};
    static constexpr uint8_t float_flag{1};
    static constexpr uint8_t double_flag{2};

    uint32_t pictures_counter{0};

    bool getBool(std::ifstream& File, const bool is_buffer_filled = false, uint32_t start_index = 0) {

        bool some_bool;

        // Если буффер не заполнен, то заполняем его
        if (!is_buffer_filled) {
            File.read(buffer, 1);
        }

        some_bool = static_cast<bool>(buffer[start_index]);

        return some_bool;
    }

    void getString(std::ifstream& File, std::string& some_string, uint32_t string_size,
                   const bool is_buffer_filled = false) {

        some_string = std::string();

        // Если буффер не заполнен, то заполняем его
        if (!is_buffer_filled) {
            File.read(buffer, string_size);
        }

        for (uint32_t _byte = 0; _byte < string_size; ++_byte) {
            some_string += buffer[_byte];
        }

    }

    // Шаблон получения целочисленного значения из файла
    template<typename IntType>
    IntType getSomeInt(std::ifstream& File, IntType some_int, const bool is_buffer_filled = false) {

        // Вычисляем размер необходимого целочисленного типа данных
        uint8_t int_size = sizeof(some_int);

        // Если буффер не заполнен, то заполняем его
        if (!is_buffer_filled) {
            File.read(buffer, int_size);
        }

        some_int = *reinterpret_cast<IntType*>(buffer);

        return some_int;
    }

    // Шаблон получения числового значения с плавающей точкой из буффера
    template<typename FloatType>
    FloatType getSomeFloat(std::ifstream& File, FloatType some_float, const bool is_buffer_filled = false) {

        uint8_t float_size = sizeof(some_float);

        // Если буффер не заполнен, то заполняем его
        if (!is_buffer_filled) {
            File.read(buffer, float_size);
        }

        if (float_size == types_sizes._32bits) {
            some_float = *reinterpret_cast<float*>(buffer);
        } else if (float_size == types_sizes._64bits) {
            some_float = *reinterpret_cast<double*>(buffer);
        }

        return some_float;
    }

    // Функция получения цвета
    void getColor(std::ifstream& File, sop::BGRColor& color, const bool is_buffer_filled = false) {

        // Если буффер не заполнен, то заполняем его
        if (!is_buffer_filled) {
            File.read(buffer, 3);
        }

        std::bitset<8> print_byte;

        color.blue = static_cast<uint8_t>(buffer[0]);
        color.green = static_cast<uint8_t >(buffer[1]);
        color.red = static_cast<uint8_t >(buffer[2]);
    }

    void getMatrix(std::ifstream& File, std::vector<std::vector<double>>& some_matrix, uint8_t size_y, uint8_t size_x,
                   bool is_buffer_filled = false) {

        some_matrix.resize(size_y);
        for (uint8_t y = 0; y < size_y; ++y) {

            some_matrix[y].resize(size_x);
            for (uint8_t x = 0; x < size_x; ++x) {

                some_matrix[y][x] = getSomeFloat(File, some_matrix[y][x], is_buffer_filled);

            }
        }

    }

    void getVector(std::ifstream& File, std::vector<sop::Point>& some_vector, uint8_t vector_size,
                   bool is_buffer_filled = false) {

        some_vector.resize(vector_size);
        for (uint8_t _element = 0; _element < vector_size; ++_element) {
            some_vector[_element].x = getSomeInt(File, some_vector[_element].x, is_buffer_filled);

            some_vector[_element].y = getSomeInt(File, some_vector[_element].y, is_buffer_filled);

        }

    }

    void getFont(std::ifstream& File, sop::PrimitiveParams& primitive_params);

    void getPicture(std::ifstream& File, sop::PrimitiveParams& primitive_params, std::string& bmp_filepath);

    void parseObject(std::ifstream& File, int32_t lib_index);

    void getButtonsInfo(std::ifstream& File, sop::ObjectParams& object_params);

    void getAnimationInfo(std::ifstream& File, sop::ObjectParams& object_params);

    void rewriteCacheObject(int32_t lib_index, int32_t cache_size);

    void parsePrimitiveCommonFields(std::ifstream& File, sop::PrimitiveParams& primitive_params);

    void parsePrimitive(std::ifstream& File, sop::ObjectParams& object_params);

//  void parseTextObject();

//  void parseStructObject() {};

    void parseLibObject(sop::ObjectParams& object_params);

    void writeFontInfo(const sop::PrimitiveParams& primitive_params);

    void writeObjectInfo(const sop::ObjectParams& object_params);

    void writePrimitiveParams(const sop::PrimitiveParams& primitive_params);

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

public:

    explicit SchemeObjectParser() {
        CacheFileOut.open(cachefile_path, std::ofstream::out | std::ios_base::trunc);
        CacheFileOut.close();
    }

    void set_params(Scheme::SchemeParams* _scheme_params) {
        scheme_params = _scheme_params;
    }

    // Главная функция парса объектов
    bool parse(uint32_t infile_cursor, const std::string& schemefile_path, const std::string& logsfile_path,
               int32_t lib_index, bool is_cache = false, int32_t cache_size = 0) {

        if (!openWorkFiles(schemefile_path, logsfile_path)) {
            return false;
        }

        SchemeFile.clear();
        SchemeFile.seekg(infile_cursor);

        if (!is_cache) {
            parseObject(SchemeFile, lib_index);
        } else {
            CacheFileOut.open(cachefile_path, std::ios_base::binary | std::ios_base::app);
            rewriteCacheObject(lib_index, cache_size);
        }

        SchemeFile.close();
        CacheFileOut.close();
        CacheFileIn.close();
        LogsFile.close();

        return true;
    }


};

