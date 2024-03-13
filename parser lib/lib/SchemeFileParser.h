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

    std::string schemefile_path;
    std::string logsfile_path;

    uint64_t file_size;             // Размер файла схемы

    // Параметры схемы, экземпляр передаётся из-вне
    Scheme::SchemeParams* scheme_params;

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
        Section* parrent_sect{nullptr};

        uint32_t sect_size{0};          // Размер секции
        uint32_t start_pos;             // Номер стартового байта секции

        std::string sect_name;          // Имя секции
//      uint32_t sect_number{0};        // Номер секции (пустой, если есть имя)
    };

    // Стек открытых секций
    std::vector<Section> sections_stack;

    char byte;      // Переменная для работы с байтами

    static constexpr uint16_t buffer_size{4096};    // Фиксированный размер буфера
    char* buffer = new char[buffer_size];           // Буффер, для работы с байтами

    SchemeObjectParser objectParser;                // Экземпляр парсера объектов схемы
    static sce::SchemeObjectsTypes objects_types;   // Экземпляр структуры с типами объектов схемы
    uint64_t objects_amount{0};                      // Кол-во объектов в схеме

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
    }

    // Функция для парса информации секции
    void parseSectionData();

    // Функция для получения размера блока
    uint32_t getBlockSize();

    // Функция чтения информации из блока
    void printBlockData(const uint32_t& block_size, const bool is_buffer_filled = false, uint32_t start_index = 0);

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

    // Функция парса параметров кэш объекта схемы
    void parseCashObject();

    void getLogFilePath() {
        size_t filename_start_index = schemefile_path.rfind('/') + 1;
        size_t filename_end_index = schemefile_path.rfind('.') - 1;

        uint8_t filename_size = filename_end_index - filename_start_index + 1;

        logsfile_path = "../parser lib/logs/"
                       + schemefile_path.substr(filename_start_index, filename_size)
                       + ".slog";
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

        lae::PrintLog("Парсер схемы: Файлы схемы и логов успешно открыты", true, 2);

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
    virtual bool parse(const std::string& schemefile_path);
};

bool SchemeFileParser::parse(const std::string& _schemefile_path) {
    schemefile_path = _schemefile_path;

    if (!openWorkFiles())
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

    lae::PrintLog("Парсер схемы: Парсер отработал", true, 2);

    return true;
}
