#include <iostream>
#include <locale>
#include <bitset>

#include <sys/stat.h>
#include <sys/types.h>

#include "SchemeObjectParser.h"

#pragma once    // Сообщаем препроцессору, что данный заголовочный файл может быть подключен только 1 раз


// Главный класс парсера схемы
class SchemeFileParser {
private:

    std::ofstream LogsFile;         // Файл логов
    std::ifstream SchemeFile;       // Файл схемы

    std::string schemefile_path;
    std::string logsfile_path;

    uint64_t file_size;             // Размер файла схемы

    // Параметры схемы, экземпляр передаётся из-вне
    Scheme::SchemeParams *scheme_params;

    // Структуры содержащие флаги параметров секций

    static sce::schm schm_data;     // Параметры секции schm
    static sce::cach cach_data;     // Параметры секции cach
    static sce::link link_data;     // Параметры секции link
    static sce::sect sect_data;     // Параметры секции sect
    static sce::objs objs_data;     // Параметры секции objs
    static sce::extd extd_data;     // Параметры секции extd
    static sce::sch2 sch2_data;     // Параметры секции sch2
    static sce::font font_data;     // Параметры секции font

    static sce::SchemeFlags scheme_flags;   // Флаги необходимые для парса секций и блоков схемы
    static sce::TypesSizes types_sizes;

    // Структура секции
    struct Section {
        Section *parrent_sect{nullptr};

        uint32_t sect_size{0};          // Размер секции
        uint32_t start_pos;             // Номер стартового байта секции

        std::string sect_name;          // Имя секции
//      uint32_t sect_number{0};        // Номер секции (пустой, если есть имя)
    };

    // Стек открытых секций
    std::vector<Section> sections_stack;

    const std::string file_format{"схема"};

    bool check_scheme_version = false;

    char byte;      // Переменная для работы с байтами

    static constexpr uint16_t buffer_size{4096};    // Фиксированный размер буфера
    char *buffer = new char[buffer_size];           // Буффер, для работы с байтами

    SchemeObjectParser objectParser = SchemeObjectParser();     // Экземпляр парсера объектов схемы

    static sce::SchemePrimitiveTypes objects_types; // Экземпляр структуры с типами объектов схемы
    uint64_t objects_amount{0};                     // Кол-во объектов в схеме

    int32_t actual_nesting_level{1};
    bool is_object{true};

    // Шаблон получения целочисленного значения из файла
    template<typename IntType>
    IntType getSomeInt(IntType some_int, const uint8_t int_size, const bool is_buffer_filled = false) {

        some_int = 0;

        // Если буффер не заполнен, то заполняем его
        if (!is_buffer_filled) {
            SchemeFile.read(buffer, int_size);
        }
        if (int_size == 1) {
            buffer[1] = 0;
            buffer[2] = 0;
            buffer[3] = 0;
        } else if (int_size == 2) {
            buffer[2] = 0;
            buffer[3] = 0;
        }

        some_int = *reinterpret_cast<IntType *>(buffer);

        return some_int;
    }

    // Функция получения размера файла
    void getFileSize() {

        SchemeFile.seekg(0, std::ios::end);    // Курсор ставится в конец файла
        file_size = SchemeFile.tellg();        // Записывается позиция курсора

        SchemeFile.clear();                    // С файла сбрасываются возможные ошибки чтения
        SchemeFile.seekg(0, std::ios::beg);    // Курсор возвращается в начало файла

        lae::PrintLog("Размер файла схемы: ", false, 2);
        lae::PrintLog(file_size, false, 2);
        lae::PrintLog(" байт", true, 2);

        lae::WriteLog(LogsFile, "\nFile size: ");
        lae::WriteLog(LogsFile, file_size);
        lae::WriteLog(LogsFile, " bytes\n", true);
    }

    // Функция закрытия секции
    void closeSection() {
        // Если размер стека секция больше 1, то секция считается вложенной
        if (sections_stack.size() > 1) {
            for (uint16_t _section = 1; _section < sections_stack.size(); ++_section)
                lae::WriteLog(LogsFile, "- ");
            lae::WriteLog(LogsFile, "INTER ");
        }

        lae::WriteLog(LogsFile, "SECTION CLOSED ");

        lae::WriteLog(LogsFile, "section scheme_name: ");
        for (uint16_t _section = 1; _section < sections_stack.size() - 1; ++_section) {
            lae::WriteLog(LogsFile, sections_stack[_section].sect_name);
            lae::WriteLog(LogsFile, ".");
        }
        lae::WriteLog(LogsFile, sections_stack.back().sect_name, true);

        sections_stack.pop_back();

    }

    // Функция чтения заголовка секции схемы
    bool enterSection() {
        // Новый экземпляр структуры секции
        Section new_section;

        // Если стек секции не пустой, секция считается вложенной
        if (!sections_stack.empty()) {
            new_section.parrent_sect = &sections_stack.back();

            for (uint16_t _section = 0; _section < sections_stack.size(); ++_section)
                lae::WriteLog(LogsFile, "- ");
            lae::WriteLog(LogsFile, "INTER ");
        }

        lae::WriteLog(LogsFile, "SECTION OPENED ");

        // Считаем размер секции
        new_section.sect_size = getSomeInt(new_section.sect_size, 4);

        // Находим имя или номер секции
        SchemeFile.read(buffer, 4);

        // Если первый байт это буква, то считаем, что это именованная секция
        if (isalpha(buffer[0])) {
            for (int8_t i = 0; i < 4; ++i) {
                new_section.sect_name += buffer[i];
            }

            // В противном случае, считаем, что это нумерованная секция
        } else {
            uint32_t tmp_section_name = 0;
            new_section.sect_name = std::to_string(getSomeInt(tmp_section_name, 4, true));
        }

        if (!check_scheme_version) {
            if (new_section.sect_name != "ARM ") {
                lae::PrintLog("Парсер схемы: Старая версия схемы", true);
                return false;
            }
            check_scheme_version = true;
        }

        // Запоминаем стартовую позицию секции
        new_section.start_pos = SchemeFile.tellg();

        // Добавляем новую секцию в стек
        sections_stack.push_back(new_section);

        lae::WriteLog(LogsFile, "section scheme_name: ");
        for (uint16_t _section = 1; _section < sections_stack.size() - 1; ++_section) {
            lae::WriteLog(LogsFile, sections_stack[_section].sect_name);
            lae::WriteLog(LogsFile, ".");
        }
        lae::WriteLog(LogsFile, new_section.sect_name);

        lae::WriteLog(LogsFile, " section size: ");
        lae::WriteLog(LogsFile, sections_stack.back().sect_size, true);

        // Вызываем функцию парса содержимого секции
        parseSectionData();
        return true;
    }

    // Функция для парса информации секции
    void parseSectionData();

    // Функция для получения размера блока
    uint32_t getBlockSize();

    // Функция чтения информации из блока
    void printBlockData(const uint32_t block_size);

    // Функции парса основных секций схемы

    void parseSchm();

    void parseCash();

    void parseLink();

    void parseSect();

    void parseObjs();

    void parseExtd();

    void parseSch2();

    void parseFont();

    void parseUnknown();

    void parseObjectInfo();

    // Функция парса параметров объекта схемы
    void parseObject();

    // Функция парса параметров кэш объекта схемы
    void parseCashObject();

    void getLogFilePath() {
        size_t filename_start_index = schemefile_path.rfind('/') + 1;
        size_t filename_end_index = schemefile_path.rfind('.') - 1;

        uint8_t filename_size = filename_end_index - filename_start_index + 1;

        // Get the current time
        std::time_t now = std::time(0);

        // Convert the current time to a tm struct
        std::tm *timeinfo = std::localtime(&now);

        std::string date;
        date += std::to_string(timeinfo->tm_year + 1900) + "-";
        date += std::to_string(timeinfo->tm_mon + 1) + "-";
        date += std::to_string(timeinfo->tm_mday);

        std::string dir_name = "../parser_lib/logs/" + date;

        mkdir(dir_name.c_str(), 0777);

        logsfile_path = dir_name + '/'
                        + schemefile_path.substr(filename_start_index, filename_size)
                        + ".log";
    }

    // Функция открытия рабочих файлов
    bool openWorkFiles() {
        SchemeFile.open(schemefile_path, std::ios_base::binary);

        getLogFilePath();
        LogsFile.open(logsfile_path);

        if (!SchemeFile) {
            lae::PrintLog("Парсер схемы: Файл схемы не был открыт", true, 12);
            return false;
        }

        scheme_params->file_path = schemefile_path;

        if (!LogsFile) {
            lae::PrintLog("Парсер схемы: Файл логов не был открыт", true, 12);
            return false;
        }

        lae::PrintLog("Парсер схемы: Файлы схемы и логов открыты", true, 2);

        getFileSize();

        return true;

    }

public:
    // Конутруктор класса, принимающий в себя параметры схемы,
    // куда будет записываться полученная из файла информация
    explicit SchemeFileParser(Scheme::SchemeParams &_scheme_params) {
        scheme_params = &_scheme_params;
    }

    ~SchemeFileParser() {
        delete[] buffer;
    }

    // Главная функция парсера схемы
    bool parse(const std::string &schemefile_path);
};

bool SchemeFileParser::parse(const std::string &_schemefile_path) {

    size_t filename_end_index = _schemefile_path.rfind('.') + 1;
    std::string file_format_check_string = _schemefile_path.substr(filename_end_index);
    if (file_format_check_string != file_format) {
        lae::PrintLog("Неправильный формат файла", true);
        return false;
    }
    schemefile_path = _schemefile_path;

    if (!openWorkFiles())
        return false;

    objectParser.set_params(scheme_params);

    while (SchemeFile.get(byte)) {
        // Если дошли до границ открытой секции, закрываем её
        while (!sections_stack.empty() &&
               (SchemeFile.tellg() >= sections_stack.back().start_pos + sections_stack.back().sect_size)) {
            closeSection();
        }

        // Если обнаружили флаг секции, открываем её
        if (byte == scheme_flags.section_flag) {
            if (!enterSection()) {
                return false;
            }
        }


    }

    // Если остались незакрытые секции, закрываем их
    while (!sections_stack.empty()) {
        closeSection();
    }

    // Закрываем файлы
    SchemeFile.close();
    LogsFile.close();

    lae::PrintLog("Парсер схемы: Парсер отработал", true, 2);

    return true;
}


void SchemeFileParser::parseSchm() {

    uint32_t tmp_value;

    uint8_t data_counter = 0;
    uint32_t block_size;

    // Пока не дошли до конца секции, считываем данные
    while (SchemeFile.tellg() < sections_stack.back().start_pos + sections_stack.back().sect_size) {
        SchemeFile.get(byte);

        // Если нашли флаг блока, открываем его
        if ((static_cast<uint8_t>(byte) & scheme_flags.block_flag) == scheme_flags.block_flag) {
            // Получаем размер блока
            block_size = getBlockSize();
            ++data_counter;

            switch (data_counter) {
                case schm_data.version_flag:
                    tmp_value = getSomeInt(tmp_value, block_size);
                    lae::WriteLog(LogsFile, "Version: ");
                    lae::WriteLog(LogsFile, tmp_value, true);
                    break;
                case schm_data.name_length_flag:
                    getSomeInt(0, block_size);
                    break;
                case schm_data.scheme_name_flag:
                    for (uint32_t digit = 0; digit < block_size; ++digit) {
                        SchemeFile.get(byte);
                        scheme_params->name_scheme += byte;
                    }
                    lae::WriteLog(LogsFile, "Name: ");
                    lae::WriteLog(LogsFile, scheme_params->name_scheme, true);
                    break;
                case schm_data.DBIP_length_flag:
                    tmp_value = getSomeInt(tmp_value, block_size);
                    if (tmp_value == 0)
                        ++data_counter;
                    break;
                case schm_data.DBIP_flag:
                    for (uint32_t digit = 0; digit < block_size; ++digit) {
                        SchemeFile.get(byte);
                        scheme_params->name_bd += byte;
                    }
                    lae::WriteLog(LogsFile, "DBIP: ");
                    lae::WriteLog(LogsFile, scheme_params->name_bd, true);
                    break;
                case schm_data.DBAlias_length_flag:
                    tmp_value = getSomeInt(tmp_value, block_size);
                    if (tmp_value == 0)
                        ++data_counter;
                    break;
                case schm_data.DBAlias_flag:
                    for (uint32_t digit = 0; digit < block_size; ++digit) {
                        SchemeFile.get(byte);
                        scheme_params->server += byte;
                    }
                    lae::WriteLog(LogsFile, "DBAlias: ");
                    lae::WriteLog(LogsFile, scheme_params->server, true);
                    break;
                case schm_data.width_flag:
                    scheme_params->width = getSomeInt(scheme_params->width, block_size);
                    lae::WriteLog(LogsFile, "width: ");
                    lae::WriteLog(LogsFile, scheme_params->width, true);
                    break;
                case schm_data.height_flag:
                    scheme_params->height = getSomeInt(scheme_params->height, block_size);
                    lae::WriteLog(LogsFile, "height: ");
                    lae::WriteLog(LogsFile, scheme_params->height, true);
                    break;
                case schm_data.reserved_1_flag:
                    getSomeInt(0, block_size);
                    break;
                case schm_data.reserved_2_flag:
                    getSomeInt(0, block_size);
                    break;
                case schm_data.work_scale_flag:
                    SchemeFile.read(buffer, block_size);
                    lae::WriteLog(LogsFile, "work_scale: ");
                    lae::WriteLog(LogsFile, NULL, true);
                    break;
                case schm_data.bg_color_flag:
                    SchemeFile.read(buffer, block_size);
                    scheme_params->bgColor.blue = static_cast<uint8_t>(buffer[0]);
                    scheme_params->bgColor.green = static_cast<uint8_t>(buffer[1]);
                    scheme_params->bgColor.red = static_cast<uint8_t>(buffer[2]);
                    lae::WriteLog(LogsFile, "bg_color: ");
                    lae::WriteLog(LogsFile, "b: ");
                    lae::WriteLog(LogsFile, (int) scheme_params->bgColor.blue);
                    lae::WriteLog(LogsFile, " g: ");
                    lae::WriteLog(LogsFile, (int) scheme_params->bgColor.green);
                    lae::WriteLog(LogsFile, " r: ");
                    lae::WriteLog(LogsFile, (int) scheme_params->bgColor.red, true);
                    break;
                case schm_data.net_color_flag:
                    SchemeFile.read(buffer, block_size);
                    scheme_params->setColor.blue = static_cast<uint8_t>(buffer[0]);
                    scheme_params->setColor.green = static_cast<uint8_t>(buffer[1]);
                    scheme_params->setColor.red = static_cast<uint8_t>(buffer[2]);
                    lae::WriteLog(LogsFile, "setColor: ");
                    lae::WriteLog(LogsFile, "b: ");
                    lae::WriteLog(LogsFile, (int) scheme_params->setColor.blue);
                    lae::WriteLog(LogsFile, " g: ");
                    lae::WriteLog(LogsFile, (int) scheme_params->setColor.green);
                    lae::WriteLog(LogsFile, " r: ");
                    lae::WriteLog(LogsFile, (int) scheme_params->setColor.red, true);
                    break;
                case schm_data.BitDepth_flag:
                    SchemeFile.get(byte);
                    lae::WriteLog(LogsFile, "BitDepth: ");
                    lae::WriteLog(LogsFile, NULL, true);
                    break;
                case schm_data.count_of_objects_flag:
                    objects_amount = getSomeInt(objects_amount, block_size);
                    lae::WriteLog(LogsFile, "count_of_objects: ");
                    lae::WriteLog(LogsFile, objects_amount, true);
                    break;
                case schm_data.windowsSize_x_flag:
                    getSomeInt(0, block_size);
                    lae::WriteLog(LogsFile, "windowsSize_x: ");
                    lae::WriteLog(LogsFile, NULL, true);
                    break;
                case schm_data.windowsSize_y_flag:
                    getSomeInt(0, block_size);
                    lae::WriteLog(LogsFile, "windowsSize_y: ");
                    lae::WriteLog(LogsFile, NULL, true);
                    break;
            }
        } else if (byte == scheme_flags.section_flag)
            enterSection();
    }
}

void SchemeFileParser::parseCash() {

    uint32_t tmp_value;

    uint8_t data_counter = 1;
    uint32_t block_size;

    // Пока не дошли до конца секции, считываем данные
    while (SchemeFile.tellg() < sections_stack.back().start_pos + sections_stack.back().sect_size) {
        SchemeFile.get(byte);

        // Если нашли флаг блока, открываем его
        if ((static_cast<uint8_t>(byte) & scheme_flags.block_flag) == scheme_flags.block_flag) {
            // Получаем размер блока
            block_size = getBlockSize();

            switch (data_counter) {
                case cach_data.cache_count_flag:
                    tmp_value = getSomeInt(tmp_value, block_size);
                    ++data_counter;

                    lae::WriteLog(LogsFile, "cache_count: ");
                    lae::WriteLog(LogsFile, tmp_value, true);
                    break;
                default:
                    printBlockData(block_size);
                    break;
            }
        } else if (byte == scheme_flags.section_flag)
            enterSection();
    }
}

void SchemeFileParser::parseLink() {

    uint32_t tmp_value;

    uint8_t data_counter = 1;
    uint32_t block_size;

    // Пока не дошли до конца секции, считываем данные
    while (SchemeFile.tellg() < sections_stack.back().start_pos + sections_stack.back().sect_size) {
        SchemeFile.get(byte);

        // Если нашли флаг блока, открываем его
        if ((static_cast<uint8_t>(byte) & scheme_flags.block_flag) == scheme_flags.block_flag) {
            // Получаем размер блока
            block_size = getBlockSize();

            switch (data_counter) {
                case link_data.links_count_flag:
                    tmp_value = getSomeInt(tmp_value, block_size);
                    ++data_counter;

                    lae::WriteLog(LogsFile, "links_count: ");
                    lae::WriteLog(LogsFile, tmp_value, true);
                    break;
                default:
                    printBlockData(block_size);
                    break;
            }
        } else if (byte == scheme_flags.section_flag)
            enterSection();
    }
}

void SchemeFileParser::parseSect() {

    uint32_t tmp_value;

    uint8_t data_counter = 1;
    uint32_t block_size;

    // Пока не дошли до конца секции, считываем данные
    while (SchemeFile.tellg() < sections_stack.back().start_pos + sections_stack.back().sect_size) {
        SchemeFile.get(byte);

        // Если нашли флаг блока, открываем его
        if ((static_cast<uint8_t>(byte) & scheme_flags.block_flag) == scheme_flags.block_flag) {
            // Получаем размер блока
            block_size = getBlockSize();

            switch (data_counter) {
                case sect_data.next_section_number_flag:
                    tmp_value = getSomeInt(tmp_value, block_size);
                    ++data_counter;

                    lae::WriteLog(LogsFile, "next_section_number: ");
                    lae::WriteLog(LogsFile, tmp_value, true);
                    break;
                case sect_data.sect_count_flag:
                    tmp_value = getSomeInt(tmp_value, block_size);
                    ++data_counter;

                    lae::WriteLog(LogsFile, "sect_count: ");
                    lae::WriteLog(LogsFile, tmp_value, true);
                    break;
                default:
                    printBlockData(block_size);
                    break;
            }
        } else if (byte == scheme_flags.section_flag)
            enterSection();
    }
}

void SchemeFileParser::parseObjs() {

    uint32_t tmp_value;

    uint8_t data_counter = 1;
    uint32_t block_size;

    // Пока не дошли до конца секции, считываем данные
    while (SchemeFile.tellg() < sections_stack.back().start_pos + sections_stack.back().sect_size) {
        SchemeFile.get(byte);

        // Если нашли флаг блока, открываем его
        if ((static_cast<uint8_t>(byte) & scheme_flags.block_flag) == scheme_flags.block_flag) {
            // Получаем размер блока
            block_size = getBlockSize();

            switch (data_counter) {
                case objs_data.objs_count_flag:
                    tmp_value = getSomeInt(tmp_value, block_size);
                    ++data_counter;

                    lae::WriteLog(LogsFile, "objs_count: ");
                    lae::WriteLog(LogsFile, tmp_value, true);
                    break;
                default:
                    printBlockData(block_size);
                    break;
            }
        } else if (byte == scheme_flags.section_flag)
            enterSection();
    }
}

void SchemeFileParser::parseExtd() {

    uint32_t tmp_value;

    uint8_t data_counter = 1;
    uint32_t block_size;

    // Пока не дошли до конца секции, считываем данные
    while (SchemeFile.tellg() < sections_stack.back().start_pos + sections_stack.back().sect_size) {
        SchemeFile.get(byte);

        // Если нашли флаг блока, открываем его
        if ((static_cast<uint8_t>(byte) & scheme_flags.block_flag) == scheme_flags.block_flag) {
            // Получаем размер блока
            block_size = getBlockSize();

            switch (data_counter) {
                case extd_data.f_work_variable_flag:
                    getSomeInt(0, block_size);
                    ++data_counter;

                    lae::WriteLog(LogsFile, "f_work_variable: ");
                    lae::WriteLog(LogsFile, NULL, true);
                    break;
            }
        } else if (byte == scheme_flags.section_flag)
            enterSection();
    }
}

void SchemeFileParser::parseSch2() {

    uint32_t tmp_value;

    uint8_t data_counter = 0;
    uint32_t block_size;

    // Пока не дошли до конца секции, считываем данные
    while (SchemeFile.tellg() < sections_stack.back().start_pos + sections_stack.back().sect_size) {
        SchemeFile.get(byte);
        // Если нашли флаг блока, открываем его
        if ((static_cast<uint8_t>(byte) & scheme_flags.block_flag) == scheme_flags.block_flag) {
            // Получаем размер блока
            block_size = getBlockSize();
            ++data_counter;

            switch (data_counter) {
                case sch2_data.window_size_X_flag:
                    getSomeInt(0, block_size);
                    lae::WriteLog(LogsFile, "window_size_X: ");
                    lae::WriteLog(LogsFile, NULL, true);
                    break;
                case sch2_data.window_size_Y_flag:
                    getSomeInt(0, block_size);
                    lae::WriteLog(LogsFile, "window_size_Y: ");
                    lae::WriteLog(LogsFile, NULL, true);
                    break;
                case sch2_data.tmpbool_flag:
                    SchemeFile.get(byte);
                    tmp_value = byte;
                    if (tmp_value == 0) {
                        data_counter += 2;
                    }
                    break;
                case sch2_data.MS_size_flag:
                    getSomeInt(0, block_size);
                    lae::WriteLog(LogsFile, "MS_size: ");
                    lae::WriteLog(LogsFile, NULL, true);
                    break;
                case sch2_data.back_bitmap_info_flag:
                    getSomeInt(0, block_size);
                    lae::WriteLog(LogsFile, "back_bitmap_info: ");
                    lae::WriteLog(LogsFile, NULL, true);
                    break;
                case sch2_data.pixels_per_inch_X_flag:
                    getSomeInt(0, block_size);
                    lae::WriteLog(LogsFile, "pixels_per_inch_X: ");
                    lae::WriteLog(LogsFile, NULL, true);
                    break;
                case sch2_data.pixels_per_inch_Y_flag:
                    getSomeInt(0, block_size);
                    lae::WriteLog(LogsFile, "pixels_per_inch_Y: ");
                    lae::WriteLog(LogsFile, NULL, true);
                    break;

            }
        } else if (byte == scheme_flags.section_flag)
            enterSection();
    }
}

void SchemeFileParser::parseFont() {
    ;
}


void SchemeFileParser::parseUnknown() {
    // Пока не дошли до конца секции, считываем данные
    while (SchemeFile.tellg() < sections_stack.back().start_pos + sections_stack.back().sect_size) {
        SchemeFile.get(byte);

        uint32_t block_size;
        // Если нашли флаг блока, открываем его
        if ((static_cast<uint8_t>(byte) & scheme_flags.block_flag) == scheme_flags.block_flag) {
            // Получаем размер блока
            block_size = getBlockSize();

            printBlockData(block_size);

        } else if (byte == scheme_flags.section_flag)
            enterSection();
    }
}

void SchemeFileParser::parseCashObject() {

    uint32_t block_size;

    if (sections_stack.back().sect_name != "1")
        parseUnknown();
    else {
        SchemeFile.get(byte);
        // Получаем размер блока
        block_size = getBlockSize();
        uint32_t cache_size;
        cache_size = getSomeInt(cache_size, types_sizes._32bits);

        SchemeFile.get(byte);
        // Получаем размер блока
        block_size = getBlockSize();

        int32_t actual_cursor_pos = SchemeFile.tellg();

        SchemeFile.close();
        LogsFile.close();

        int32_t cache_index = std::stoi(sections_stack.back().parrent_sect->sect_name);

        objectParser.parse(actual_cursor_pos, schemefile_path, logsfile_path, cache_index, false, 1, true, cache_size);

        SchemeFile.open(schemefile_path, std::ios_base::binary);

        SchemeFile.clear();
        SchemeFile.seekg(actual_cursor_pos + block_size);

        LogsFile.open(logsfile_path, std::ios_base::app);
    }
}

void SchemeFileParser::parseObjectInfo() {
    uint32_t block_size;

    SchemeFile.get(byte);
    block_size = getBlockSize();

    SchemeFile.get(byte);

    is_object = static_cast<bool>(byte);

    SchemeFile.get(byte);
    block_size = getBlockSize();

    actual_nesting_level = getSomeInt(actual_nesting_level, block_size);

    SchemeFile.get(byte);
    block_size = getBlockSize();

    printBlockData(block_size);

    SchemeFile.get(byte);
    block_size = getBlockSize();

    printBlockData(block_size);

    SchemeFile.get(byte);
    enterSection();

}

void SchemeFileParser::parseObject() {

    uint32_t block_size;

    if (sections_stack.back().sect_name != "1")
        parseUnknown();
    else {

        SchemeFile.get(byte);
        // Получаем размер блока
        block_size = getBlockSize();
        int32_t lib_index = 0;

        if (block_size == 1) {
            SchemeFile.get(byte);
            bool tmp_bool = static_cast<bool>(byte);

            if (tmp_bool) {
                SchemeFile.get(byte);
                // Получаем размер блока
                block_size = getBlockSize();
                lib_index = getSomeInt(lib_index, types_sizes._32bits);
            }

            SchemeFile.get(byte);
            // Получаем размер блока
            block_size = getBlockSize();
        }

        printBlockData(block_size);

        SchemeFile.get(byte);
        // Получаем размер блока
        block_size = getBlockSize();

        uint32_t actual_cursor_pos = SchemeFile.tellg();

        SchemeFile.close();
        LogsFile.close();

        objectParser.parse(actual_cursor_pos, schemefile_path, logsfile_path, lib_index, is_object,
                           actual_nesting_level);
        actual_nesting_level = 1;
        is_object = true;

        SchemeFile.open(schemefile_path, std::ios_base::binary);

        SchemeFile.clear();
        SchemeFile.seekg(actual_cursor_pos + block_size);

        LogsFile.open(logsfile_path, std::ios_base::app);
    }

}


void SchemeFileParser::parseSectionData() {
    if (sections_stack.back().sect_name == "schm")
        parseSchm();
    else if (sections_stack.back().sect_name == "cach")
        parseCash();
    else if (sections_stack.back().sect_name == "link")
        parseLink();
    else if (sections_stack.back().sect_name == "sect")
        parseSect();
    else if (sections_stack.back().sect_name == "objs")
        parseObjs();
    else if (sections_stack.back().sect_name == "extd")
        parseExtd();
    else if (sections_stack.back().sect_name == "sch2")
        parseSch2();
    else if (sections_stack.back().sect_name == "font")
        parseUnknown();
    else if (sections_stack.size() == 3 and sections_stack[1].sect_name == "objs")
        parseObjectInfo();
    else if (sections_stack.size() == 4 and sections_stack[1].sect_name == "objs")
        parseObject();
    else if (sections_stack.size() == 4 and sections_stack[1].sect_name == "cach")
        parseCashObject();
    else
        parseUnknown();
}

// Функция чтения блока байтов в схеме
uint32_t SchemeFileParser::getBlockSize() {


    int8_t bytes_for_blocksize = 0;
    uint32_t block_size = 0;

    // По признаку блока определяем его размер
    if ((static_cast<uint8_t>(byte) & scheme_flags.size_6_bit) == scheme_flags.size_6_bit) {
        block_size |= (static_cast<uint8_t>(byte) & 0b00111111);
    } else {
        // Если размер блока не уместился в 6 бит, берём его исходя из нужного признака
        switch (static_cast<uint8_t>(byte)) {
            case scheme_flags.size_8_bit:
                bytes_for_blocksize = 1;
                break;
            case scheme_flags.size_16_bit:
                bytes_for_blocksize = 2;
                break;
            case scheme_flags.size_32_bit:
                bytes_for_blocksize = 4;
                break;
            default:
                bytes_for_blocksize = 4;
                break;
        }
        block_size = getSomeInt(block_size, bytes_for_blocksize);
    }

    return block_size;
}

// Функция чтения информации из блока
void SchemeFileParser::printBlockData(const uint32_t block_size) {

    lae::WriteLog(LogsFile, "BLOCK OPENED ");
    lae::WriteLog(LogsFile, "block size: ");
    lae::WriteLog(LogsFile, block_size, true);

    std::bitset<8> print_byte;
    uint32_t bytes_counter = 0;

    while (bytes_counter < block_size) {
        SchemeFile.get(byte);
        ++bytes_counter;

        print_byte = byte;
        lae::WriteLog(LogsFile, print_byte);

        if (bytes_counter % 4 == 0) {
            lae::WriteLog(LogsFile, "\n");
        } else {
            lae::WriteLog(LogsFile, ' ');
        }

    }


    lae::WriteLog(LogsFile, "BLOCK CLOSED", true);

};