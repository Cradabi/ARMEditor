#pragma once    // Сообщаем препроцессору, что данный заголовочный файл может быть подключен только 1 раз

#include "fstream"

#include "SchemeFileNS.h"
#include "primitives_lib/SchemeClass.h"


// Базовый класс парсера схемы
class SchemeParser
{
protected:
    const std::string file_format_{"схема"};

    std::ifstream scheme_file_; // Файл схемы
    std::ofstream logs_file_; // Файл логов

    std::string schemefile_path_;
    std::string logsfile_path_;

    // Параметры схемы, экземпляр передаётся из-вне
    Scheme::SchemeParams* scheme_params_;

    static sce::SchemePrimitiveTypes objects_types_;
    static sce::TypesSizes size_;

    char byte_; // Переменная для работы с байтами

    const uint16_t buffer_size_{4096}; // Фиксированный размер буфера
    char* buffer_ = new char[buffer_size_]; // Буффер, для работы с байтами

public:

    SchemeParser() = default;

    // Деструктор класса, очищающий память, занятую буффером
    virtual ~SchemeParser()
    {
        delete[] buffer_;
    }

    // Главная функция парсера
    virtual bool parse() = 0;

    bool setSchemeFile(const std::string& schemefile_path);

    bool setLogsFile();

    void setSchemeParams(Scheme::SchemeParams& scheme_params);

    bool getBool(std::ifstream& file);

    void getString(std::ifstream& file, std::string& some_string, uint32_t string_size);

    // // Шаблон получения целочисленного значения из файла
    // template <typename IntType>
    // void getSomeInt(std::ifstream& file, IntType some_int, uint8_t int_size = sizeof(IntType))
    // {
    //     file.read(some_int, int_size);
    // }
    //
    // // Шаблон получения числового значения с плавающей точкой из буффера
    // template <typename FloatType>
    // void getSomeFloat(std::ifstream& file, FloatType some_float, uint8_t float_size = sizeof(FloatType))
    // {
    //     file.read(some_float, float_size);
    // }

    // Шаблон получения целочисленного значения из файла
    template <typename IntType>
    void getSomeInt(std::ifstream& file, IntType& some_int, uint8_t int_size = sizeof(IntType));

    // Шаблон получения числового значения с плавающей точкой из буффера
    template <typename FloatType>
    void getSomeFloat(std::ifstream& file, FloatType& some_float, uint8_t float_size = sizeof(FloatType));

};
