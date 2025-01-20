#pragma once    // Сообщаем препроцессору, что данный заголовочный файл может быть подключен только 1 раз

#include <iostream>
#include <locale>
#include <bitset>

#include <sys/stat.h>

#include "SchemeObjectParser.h"
#include "SchemeFileNS.h"

// Главный класс парсера схемы
class SchemeSectionsParser : public SchemeObjectParser
{
    bool check_scheme_version_ = false;

    // Структуры содержащие флаги параметров секций
    static sce::schm schm_data_; // Параметры секции schm
    static sce::cach cach_data_; // Параметры секции cach
    static sce::link link_data_; // Параметры секции link
    static sce::sect sect_data_; // Параметры секции sect
    static sce::objs objs_data_; // Параметры секции objs
    static sce::extd extd_data_; // Параметры секции extd
    static sce::sch2 sch2_data_; // Параметры секции sch2
    static sce::font font_data_; // Параметры секции font

    static sce::SchemeFlags scheme_flags_; // Флаги необходимые для парса секций и блоков схемы

    // Структура секции
    struct Section
    {
        Section* parrent_sect{nullptr};

        uint32_t sect_size; // Размер секции
        uint32_t start_pos; // Номер стартового байта секции

        std::string sect_name; // Имя секции
        //      uint32_t sect_number;        // Номер секции (пустой, если есть имя)
    };

    // Стек открытых секций
    std::vector<Section> sections_stack_;

    uint64_t objects_amount_{0}; // Кол-во объектов в схеме

    int32_t actual_nesting_level_{1};
    bool is_object;

    // Функция закрытия секции
    void closeSection()
    {
        // Если размер стека секция больше 1, то секция считается вложенной
        if (sections_stack_.size() > 1)
        {
            for (uint16_t _section = 1; _section < sections_stack_.size(); ++_section)
                lae::writeLog(logs_file_, "- ");
            lae::writeLog(logs_file_, "INTER ");
        }

        lae::writeLog(logs_file_, "SECTION CLOSED ");

        lae::writeLog(logs_file_, "section scheme_name: ");
        for (uint16_t _section = 1; _section < sections_stack_.size() - 1; ++_section)
        {
            lae::writeLog(logs_file_, sections_stack_[_section].sect_name);
            lae::writeLog(logs_file_, ".");
        }
        lae::writeLog(logs_file_, sections_stack_.back().sect_name, true);

        sections_stack_.pop_back();
    }

    // Функция чтения заголовка секции схемы
    bool enterSection()
    {
        // Новый экземпляр структуры секции
        Section new_section;

        // Если стек секции не пустой, секция считается вложенной
        if (!sections_stack_.empty())
        {
            new_section.parrent_sect = &sections_stack_.back();

            for (uint16_t _section = 0; _section < sections_stack_.size(); ++_section)
                lae::writeLog(logs_file_, "- ");
            lae::writeLog(logs_file_, "INTER ");
        }

        lae::writeLog(logs_file_, "SECTION OPENED ");

        // Считаем размер секции
        getSomeInt(scheme_file_, new_section.sect_size);

        // Находим имя или номер секции
        scheme_file_.read(buffer_, 4);

        // Если первый байт это буква, то считаем, что это именованная секция
        if (isalpha(buffer_[0]))
        {
            for (int8_t i = 0; i < 4; ++i)
            {
                new_section.sect_name += buffer_[i];
            }
            // В противном случае, считаем, что это нумерованная секция
        }
        else
        {
            buffer_[4] = '\0';
            new_section.sect_name = std::to_string(*reinterpret_cast<uint32_t*>(buffer_));
        }

        if (!check_scheme_version_)
        {
            if (new_section.sect_name != "ARM ")
            {
                lae::printLog("Парсер схемы: Старая версия схемы", true);
                return false;
            }
            check_scheme_version_ = true;
        }

        // Запоминаем стартовую позицию секции
        new_section.start_pos = scheme_file_.tellg();

        // Добавляем новую секцию в стек
        sections_stack_.push_back(new_section);

        lae::writeLog(logs_file_, "section scheme_name: ");
        for (uint16_t _section = 1; _section < sections_stack_.size() - 1; ++_section)
        {
            lae::writeLog(logs_file_, sections_stack_[_section].sect_name);
            lae::writeLog(logs_file_, ".");
        }
        lae::writeLog(logs_file_, new_section.sect_name);

        lae::writeLog(logs_file_, " section size: ");
        lae::writeLog(logs_file_, sections_stack_.back().sect_size, true);

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

    void parseDefault();

    void parseObjectInfo();

    // Функция парса параметров объекта схемы
    void parseObject();

    // Функция парса параметров кэш объекта схемы
    void parseCashObject();

protected:
    explicit SchemeSectionsParser() = default;

    ~SchemeSectionsParser() = default;

    // Главная функция парсера схемы
    bool parse() override;
};
