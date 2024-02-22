#include <iostream>
#include <fstream>
#include <locale>
#include <bitset>
#include <stack>
#include <vector>
#include <bitset>

#include "SchemeFileNS.h"

#pragma once    // Сообщаем препроцессору, что данный заголовочный файл может быть подключен только 1 раз


// Главный класс парсера схемы
class SchemeFileParser {
protected:
    std::ofstream LogsFile;         // Файл логов
    std::ifstream SchemeFile;       // Файл схемы

    uint64_t file_size;             // Размер файла схемы

    static sce::SchemeFlags scheme_flags;              // Флаги схемы
    static sce::SchemeDataTypes scheme_data_types;     // Типы данных в схеме

    // Структура секции
    struct Section {
        Section* parrent_sect{nullptr};

        uint32_t sect_size{0};          // Размер секции
        uint32_t start_pos;             // Номер стартового байта секции

        std::string sect_name;          // Имя секции
//      uint32_t sect_number{0};        // Номер секции (пустой, если есть имя)
    };

    // Стек открытых секций
    std::vector<Section> sections_stack;

    char byte;                      // Переменная для работы с байтами
    char* buffer = new char[4096];  // Массив байт

    // Шаблон получения числового значения из файла (some_int ОБЯЗАТЕЛЬНО должен иметь нулевое значение!)
    template<class IntType>
    IntType GetSomeInt(IntType some_int, int8_t block_size, bool is_buffer_filled = false) {

        // Если буффер не заполнен, то заполняем его
        if (!is_buffer_filled) {
            SchemeFile.read(buffer, block_size);
        }

        for (int8_t i = block_size - 1; i >= 0; --i) {
            some_int |= static_cast<uint8_t>(buffer[i]);

            if (i != 0)
                some_int <<= 8;
        }

        return some_int;
    }

private:
    // Функция получения размера файла
    void GetFileSize() {

        SchemeFile.seekg(0, std::ios::end);    // Курсор ставится в конец файла
        file_size = SchemeFile.tellg();        // Записывается позиция курсора

        SchemeFile.seekg(0, std::ios::beg);    // Курсор возвращается в начало файла
        SchemeFile.clear();                    // С файла сбрасываются возможные ошибки чтения

        lae::PrintLog("Размер файла схемы: ", false, 2);
        lae::PrintLog(file_size, false, 2);
        lae::PrintLog(" байт", true, 2);

        lae::WriteLog(LogsFile, "\nFile size: ");
        lae::WriteLog(LogsFile, file_size);
        lae::WriteLog(LogsFile, " bytes\n", true);
    }

    // Функция закрытия секции
    void CloseSection() {
        // Если размер стека секция больше 1, то секция считается вложенной
        if (sections_stack.size() > 1) {
            for (uint16_t _section = 1; _section < sections_stack.size(); ++_section)
                lae::WriteLog(LogsFile, "- ");
            lae::WriteLog(LogsFile, "INTER ");
        }

        lae::WriteLog(LogsFile, "SECTION CLOSED ");

        lae::WriteLog(LogsFile, "section name: ");
        for (uint16_t _section = 1; _section < sections_stack.size() - 1; ++_section) {
            lae::WriteLog(LogsFile, sections_stack[_section].sect_name);
            lae::WriteLog(LogsFile, ".");
        }
        lae::WriteLog(LogsFile, sections_stack.back().sect_name, true);

        sections_stack.pop_back();

    }

    // Функция чтения заголовка секции схемы
    void EnterSection() {
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
        new_section.sect_size = GetSomeInt(new_section.sect_size, 4);

        // Находим имя или номер секции
        SchemeFile.read(buffer, 4);

        // Если байт это буква, то считаем, что это именованная секция
        if (isalpha(buffer[0])) {
            for (int8_t i = 0; i < 4; ++i) {
                new_section.sect_name = buffer[i];
            }

            // В противном случае, считаем, что это нумерованная секция
        } else {
            uint32_t tmp_section_name = 0;
            new_section.sect_name = std::to_string(GetSomeInt(tmp_section_name, 4, true));
        }

        // Запоминаем стартовую позицию секции
        new_section.start_pos = SchemeFile.tellg();
        ++new_section.start_pos;

        // Добавляем новую секцию в стек
        sections_stack.push_back(new_section);

        lae::WriteLog(LogsFile, "section name: ");
        for (uint16_t _section = 1; _section < sections_stack.size() - 1; ++_section) {
            lae::WriteLog(LogsFile, sections_stack[_section].sect_name);
            lae::WriteLog(LogsFile, ".");
        }
        lae::WriteLog(LogsFile, new_section.sect_name);

        lae::WriteLog(LogsFile, " section size: ");
        lae::WriteLog(LogsFile, sections_stack.back().sect_size, true);
    }

    // Функция открытия рабочих файлов
    bool OpenWorkFiles(const std::wstring& schemefile_path, const std::string& logfile_path) {
        SchemeFile.open(schemefile_path.c_str(), std::ios_base::binary);
        LogsFile.open(logfile_path);

        if (!SchemeFile) {
            lae::PrintLog("Файл схемы не был открыт", true, 12);
            return false;
        }

        if (!LogsFile) {
            lae::PrintLog("Файл логов не был открыт", true, 12);
            return false;
        }

        lae::PrintLog("Файлы схемы и логов успешно открыты", true, 2);
        GetFileSize();

        return true;

    }

public:
    // Главная функция парсера схемы
    virtual bool parse(const std::wstring& schemefile_path, const std::string& logfile_path);
};

bool SchemeFileParser::parse(const std::wstring& schemefile_path, const std::string& logfile_path) {
    if (!OpenWorkFiles(schemefile_path, logfile_path))
        return false;

    while (SchemeFile.get(byte)) {
        // Если дошли до границ открытой секции, закрываем её
        while (!sections_stack.empty() &&
               (SchemeFile.tellg() >= sections_stack.back().start_pos + sections_stack.back().sect_size)) {
            CloseSection();
        }

        // Если обнаружили флаг секции, открываем её
        if (byte == scheme_flags.section_flag)
            EnterSection();

    }

    // Если остались незакрытые секции, закрываем их
    while (!sections_stack.empty()) {
        CloseSection();
    }

    SchemeFile.close();
    LogsFile.close();

    return true;
}

class SchemeSectionParser : private SchemeFileParser {
private:

    // Функция чтения блока байтов в схеме
    void EnterBlock() {
        int8_t tmp_bytes_for_blocksize = 0;
        uint32_t tmp_block_size = 0;

        // По признаку блока определяем его размер
        if ((static_cast<uint8_t>(byte) & scheme_flags.size_6_bit) == scheme_flags.size_6_bit)
            tmp_block_size |= (static_cast<uint8_t>(byte) & 0b00111111);
        else {
            // Если размер блока не уместился в 6 бит, берём его исходя из нужного признака
            switch (static_cast<uint8_t>(byte)) {
                case scheme_flags.size_8_bit:
                    tmp_bytes_for_blocksize = 1;
                    break;
                case scheme_flags.size_16_bit:
                    tmp_bytes_for_blocksize = 2;
                    break;
                case scheme_flags.size_32_bit:
                    tmp_bytes_for_blocksize = 4;
                    break;
            }
            tmp_block_size = GetSomeInt(tmp_block_size, tmp_bytes_for_blocksize);
        }

        // Вызываем функцию парса информации в блоке
        ParseBlockData(tmp_block_size);
    }

// Функция чтения информации из блока
    void ParseBlockData(const uint32_t& block_size);

public:

    SchemeSectionParser(const std::wstring& schemefile_path, const std::string& logfile_path,
                        const std::vector<Section>& _sections_stack) {
        SchemeFile.open(schemefile_path.c_str(), std::ios_base::binary);
        LogsFile.open(logfile_path, std::ios_base::app);

        sections_stack = _sections_stack;
    }

    virtual bool parse() {

        while (SchemeFile.tellg() < sections_stack.back().start_pos + sections_stack.back().sect_size) {
            SchemeFile.get(byte);
            // Если обнаружили флаг блока, открываем его
            if ((static_cast<uint8_t>(byte) & scheme_flags.block_flag) == scheme_flags.block_flag)
                EnterBlock();
        }
    }

};

