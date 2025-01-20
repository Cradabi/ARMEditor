#pragma once    // Сообщаем препроцессору, что данный заголовочный файл может быть подключен только 1 раз

#include "fstream"
#include "parser_lib/src/SchemeFileNS.h"
#include "parser_lib/src/SchemeSectionsParser.h"
#include "parser_lib/src/SchemeObjectParser.h"

// Главный класс парсера схемы
class SchemeFileParser : public SchemeSectionsParser
{
    uint64_t file_size_{}; // Размер файла схемы

    // Функция получения размера файла
    void getFileSize();

public:
    explicit SchemeFileParser() = default;

    ~SchemeFileParser() = default;

    bool parse(Scheme::SchemeParams& scheme_params, const std::string& schemefile_path);
};
