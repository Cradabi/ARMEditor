#include <iostream>
#include <locale>
#include <bitset>
#include <stack>

#include "SchemeObjectParser.cpp"

#pragma once    // Сообщаем препроцессору, что данный заголовочный файл может быть подключен только 1 раз


// Главный класс парсера схемы
class SchemeFileParser {
private:
    std::ofstream LogsFile;         // Файл логов
    std::ifstream SchemeFile;       // Файл схемы

    // Параметры схемы, экземпляр передаётся из-вне
    Scheme::SchemeParams* scheme_params;

    // Структуры содержащие флаги параметров секций

    static ssp::schm schm_data;
    static ssp::cach cash_data;
    static ssp::link link_data;
    static ssp::sect sect_data;
    static ssp::objs objs_data;
    static ssp::extd extd_data;
    static ssp::sch2 sch2_data;
    static ssp::font font_data;

    uint64_t file_size;             // Размер файла схемы

    static sce::SchemeFlags scheme_flags;              // Флаги схемы
//    static sce::SchemeDataTypes scheme_data_types;     // Типы данных в схеме

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
    char* buffer = new char[464340];  // Массив байт

    SchemeObjectParser objectParser;        // Экземпляр парсера объектов схемы
    static sce::SchemeObjectsTypes objects_types;  // Экземпляр структуры с типами объектов схемы

    // Шаблон получения числового значения из файла (some_int ОБЯЗАТЕЛЬНО должен иметь нулевое значение!)
    template<typename IntType>
    IntType getSomeInt(IntType some_int, uint8_t block_size, bool is_buffer_filled = false, uint32_t start_index = 0) {

        // Если буффер не заполнен, то заполняем его
        if (!is_buffer_filled) {
            SchemeFile.read(buffer, block_size);
        }

        for (int8_t i = block_size - 1; i >= 0; --i) {
            some_int |= static_cast<uint8_t>(buffer[start_index + i]);

            if (i != 0)
                some_int <<= 8;
        }

        return some_int;
    }

    //функция для поиска начала описания объекта внутри итерированной секции объекта номер 1
    int findStartOfObject(char* buffer, const std::string& id) {
        uint32_t id_num = 1;

        char sequence[9] = {0};

        for (int8_t i = 0; i < 4; ++i) {
            sequence[i] = (id_num >> (8 * i)) & 0xFF;
            sequence[i + 4] = (id_num >> (8 * i)) & 0xFF;
        }

        char* ptr = buffer;
        int shift = 0;
        while (true) {
            if (*(ptr + shift) == sequence[0]) {
                char* temp = ptr;
                bool match = true;
                for (int i = 1; i < 8; ++i) {
                    if (*(temp + i + shift) != sequence[i]) {
                        match = false;
                        break;
                    }
                }
                if (match) {
                    return shift;
                }
            }
            ++shift;
        }
    }

    // Функция получения размера файла
    void getFileSize() {

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
    void enterSection() {
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

        // Если байт это буква, то считаем, что это именованная секция
        if (isalpha(buffer[0])) {
            for (int8_t i = 0; i < 4; ++i) {
                new_section.sect_name += buffer[i];
            }

            // В противном случае, считаем, что это нумерованная секция
        } else {
            uint32_t tmp_section_name = 0;
            new_section.sect_name = std::to_string(getSomeInt(tmp_section_name, 4, true));
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

        parseSectionData();
    }

    // Функция для парса информации секции
    void parseSectionData();

    // Функция для получения размера блока
    uint32_t getBlockSize();

    // Функция чтения информации из блока
    void printBlockData(const uint32_t& block_size);

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

    // Функция парса параметров объекта схемы
    void parseObject();

    // Функция открытия рабочих файлов
    bool openWorkFiles(const std::string& schemefile_path, const std::string& logfile_path) {
        SchemeFile.open(schemefile_path, std::ios_base::binary);
        LogsFile.open(logfile_path);

        if (!SchemeFile) {
            lae::PrintLog("Файл схемы не был открыт", true, 12);
            return false;
        }

        scheme_params->file_path = schemefile_path;

        if (!LogsFile) {
            lae::PrintLog("Файл логов не был открыт", true, 12);
            return false;
        }

        lae::PrintLog("Файлы схемы и логов успешно открыты", true, 2);
        getFileSize();

        return true;

    }

public:
    // Конутруктор класса, принимающий в себя параметры схемы,
    // куда будет записываться полученная из файла информация
    explicit SchemeFileParser(Scheme::SchemeParams& _scheme_params) {
        scheme_params = &_scheme_params;
    }

    // Главная функция парсера схемы
    virtual bool parse(const std::string& schemefile_path, const std::string& logfile_path);
};

bool SchemeFileParser::parse(const std::string& schemefile_path, const std::string& logfile_path) {
    if (!openWorkFiles(schemefile_path, logfile_path))
        return false;

    while (SchemeFile.get(byte)) {
        // Если дошли до границ открытой секции, закрываем её
        while (!sections_stack.empty() &&
               (SchemeFile.tellg() >= sections_stack.back().start_pos + sections_stack.back().sect_size)) {
            closeSection();
        }

        // Если обнаружили флаг секции, открываем её
        if (byte == scheme_flags.section_flag)
            enterSection();

    }

    // Если остались незакрытые секции, закрываем их
    while (!sections_stack.empty()) {
        closeSection();
    }

    // Очищаем буффер
    delete[] buffer;

    // Закрываем файлы
    SchemeFile.close();
    LogsFile.close();

    lae::PrintLog("Парсер отработал", true, 2);

    return true;
}
