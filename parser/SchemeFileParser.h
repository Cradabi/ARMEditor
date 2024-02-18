#include <iostream>
#include <fstream>
#include <cinttypes>
#include <locale>
#include <windows.h>
#include <bitset>
#include <stack>
#include <vector>

#pragma once

class SchemeFileParser {
private:
    // Настройка вывода консоли
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    std::ofstream LogsFile;       // Файл логов
    std::ifstream SchemeFile;     // Файл схемы

    uint64_t file_size;           // Размер файла схемы

    static constexpr uint8_t section_flag = 0b00000000;      // Признак секции
    static constexpr uint8_t block_flag = 0b10000000;        // Признак блока

    static constexpr uint8_t size_6_bit = 0b11000000;        // Признак блока с длиной 6 бит "1 1 xxxxxx", xxxxxx - размер блока
    static constexpr uint8_t size_8_bit = 0b10000000;        // Признак блока с длиной 8 бит
    static constexpr uint8_t size_16_bit = 0b10000001;       // Признак блока с длиной 16 бит
    static constexpr uint8_t size_32_bit = 0b10000010;       // Признак блока с длиной 32 бит

#pragma pack(push, 1)
    // Структура секции
    struct Section {
        Section* parrent_sect{nullptr};

        uint32_t sect_size{0};          // Размер секции
        uint32_t start_pos;             // Номер стартового байта секции

        std::string sect_name;          // Имя секции (пустое, если есть номер)
        uint32_t sect_number{0};        // Номер секции (пустой, если есть имя)
    };

    // Структура, хранящяя типы данных используемые в схеме
    struct TSchemeDataType {
        static constexpr uint8_t dtUnknown = 0x00;   // Неизвестный тип данных, нужен для поиска ошибок

        // Записи фиксированной длины
        static constexpr uint8_t dtInteger = 0x01;       // rtInteger (Целое число)
        static constexpr uint8_t dtFloat = 0x02;         // rtFloat (Вещественное число)
        static constexpr uint8_t dtPoint = 0x03;         // rtPoint (Точка)
        static constexpr uint8_t dtFont = 0x04;          // rtFont (Шрифт)
        static constexpr uint8_t dtByte = 0x05;          // rtByte (Байт)
        static constexpr uint8_t dtRectangle = 0x06;     // rtRect (Прямоугольник)

        // Записи переменной длины
        static constexpr uint8_t dtString = 0x0A;        // rtString (Строка)
        static constexpr uint8_t dtList = 0x1E;          // rtList (Список)
        static constexpr uint8_t dtObject = 0x64;        // rtObject (Объект)
        static constexpr uint8_t dtRecord = 0x65;        // rtRecord (Запись)
        static constexpr uint8_t dtElement = 0x66;       // rtElement (Элемент контейнера)
        static constexpr uint8_t dtLibraryObject = 0x67; // (Библиотечный объект)
        static constexpr uint8_t dtLibrary = 0x96;       // rtLibrary (Библиотека (без сигнатуры))
        static constexpr uint8_t dtBitmap = 0xC8;        // rtBitmap (Bitmap graphic)
        static constexpr uint8_t dtJPEGImage = 0xC9;     // rtJPEG (JPEG graphic)
    };
#pragma pack(pop)

    // Стек открытых секций
    std::vector<Section> sections_stack;

    char byte;                    // Байт, для работы с файлами
    char* buffer = nullptr;       // Буффер байтов, для работы с файлами

    // Функция очистки буфера
    void ClearBuffer() {
        if (buffer != nullptr) {
            delete[] buffer;
            buffer = nullptr;
        }
    }

    // Функция выделения памяти под нужный объем
    void UpdateBuffer(const uint32_t& new_size) {
        ClearBuffer();
        buffer = new char[new_size];
    }

    // Функция записи в файл логов
    template<typename LogType>
    void WriteLog(const LogType& report, bool new_string = false) {

        LogsFile << report << ' ';

        if (new_string) {
            LogsFile << '\n';
        }
    }

    // Функция выввода логов в консоль
    template<typename LogType>
    void PrintLog(const LogType& report, bool new_string = false, int8_t colour = 15) {
        SetConsoleTextAttribute(hConsole, colour);

        std::cout << report << ' ';

        if (new_string) {
            std::cout << '\n';
        }
    }

    // Шаблон получения числового значения из файла (some_int ОБЯЗАТЕЛЬНО должен иметь нулевое значение!)
    template<class IntType>
    IntType GetSomeInt(IntType some_int, int8_t block_size, bool is_buffer_filled = false) {

        // Если буффер заполнен, не заполняем его
        if (!is_buffer_filled) {
            UpdateBuffer(block_size);
            SchemeFile.read(buffer, block_size);
        }

        for (int8_t i = block_size - 1; i >= 0; --i) {
            some_int |= static_cast<uint8_t>(buffer[i]);

            if (i != 0)
                some_int <<= 8;
        }

        ClearBuffer();
        return some_int;
    }

    // Функция получения имени секции
    void GetSectName(char sect_name[5]) {
        for (int8_t i = 0; i < 4; ++i) {
            sect_name[i] = buffer[i];
        }
    }

    // Функция получения размера файла
    void GetFileSize() {

        SchemeFile.seekg(0, std::ios::end);    // Курсор ставится в конец файла
        file_size = SchemeFile.tellg();        // Записывается позиция курсора

        SchemeFile.seekg(0, std::ios::beg);    // Курсор возвращается в начало файла
        SchemeFile.clear();                    // С файла сбрасываются возможные ошибки чтения

        PrintLog("Размер файла схемы: ", false, 2);
        PrintLog(file_size, false, 2);
        PrintLog(" байт", true, 2);

        WriteLog("\nFile size: ");
        WriteLog(file_size);
        WriteLog(" bytes\n", true);
    }

    // Функция закрытия секции
    void CloseSection() {
        // Если размер стека секция больше 1, то секция считается вложенной
        if (sections_stack.size() > 1) {
            for (int16_t i = 1; i < sections_stack.size(); ++i)
                WriteLog("- ");
            WriteLog("INTER");
        }

        WriteLog("SECTION CLOSED");

        // Если имя секции пустое, выводися её номер
        if (sections_stack.back().sect_name.empty()) {
            WriteLog("section number: ");
            WriteLog(sections_stack.back().sect_number, true);
            sections_stack.pop_back();

            // В противном случае выводится имя секции
        } else {
            WriteLog("section name: ");
            WriteLog(sections_stack.back().sect_name, true);
            sections_stack.pop_back();
        }

    }

    // Функция чтения заголовка секции схемы
    void EnterSection() {
        // Новый экземпляр структуры секции
        Section new_section;

        // Если стек секции не пустой, секция считается вложенной
        if (!sections_stack.empty()) {
            new_section.parrent_sect = &sections_stack.back();

            for (int16_t i = 0; i < sections_stack.size(); ++i)
                WriteLog("- ");
            WriteLog("INTER");
        }
        WriteLog("SECTION OPENED");

        // Считаем размер секции
        new_section.sect_size = GetSomeInt(new_section.sect_size, 4);

        // Находим имя или номер секции
        UpdateBuffer(4);
        SchemeFile.read(buffer, 4);

        // Если байт это буква, то считаем, что это именнованная секция
        if (isalpha(buffer[0])) {
            char tmp_section_name[5];
            GetSectName(tmp_section_name);

            new_section.sect_name = tmp_section_name;
            WriteLog("section name: ");
            WriteLog(new_section.sect_name);

            // В противном случае, считаем, что это нумерованная секция
        } else {
            new_section.sect_number = GetSomeInt(new_section.sect_number, 4, true);

            WriteLog("section number: ");
            WriteLog(new_section.sect_number);
        }

        // Запоминаем стартовую позицию секции
        new_section.start_pos = SchemeFile.tellg();
        ++new_section.start_pos;

        // Добавляем новую секцию в стек
        sections_stack.push_back(new_section);

        WriteLog(" section size: ");
        WriteLog(sections_stack.back().sect_size);

        if (new_section.parrent_sect != nullptr) {
            WriteLog(" parent section: ");
            if (!new_section.parrent_sect->sect_name.empty())
                WriteLog(new_section.parrent_sect->sect_name, true);
            else
                WriteLog(new_section.parrent_sect->sect_number, true);
        } else
            WriteLog('\n');

        ClearBuffer();
    }

    // Функция чтения блока байтов в схеме
    void EnterBlock() {
        int8_t tmp_bytes_for_blocksize = 0;
        uint32_t tmp_block_size = 0;

        // По признаку блока определяем его размер
        if ((static_cast<uint8_t>(byte) & size_6_bit) == size_6_bit)
            tmp_block_size |= (static_cast<uint8_t>(byte) & 0b00111111);
        else {
            // Если размер блока не уместился в 6 бит, берём его исходя из нужного признака
            switch (static_cast<uint8_t>(byte)) {
                case size_8_bit:
                    tmp_bytes_for_blocksize = 1;
                    break;
                case size_16_bit:
                    tmp_bytes_for_blocksize = 2;
                    break;
                case size_32_bit:
                    tmp_bytes_for_blocksize = 4;
                    break;
            }

            tmp_block_size = GetSomeInt(tmp_block_size, tmp_bytes_for_blocksize);
        }

        ParseBlockData(tmp_block_size);
    }

    // Функция чтения информации из блока
    void ParseBlockData(const uint32_t& block_size);

public:
    // Главная функция парсера схемы
    bool Parsing() {
        while (SchemeFile.get(byte)) {
            // Если дошли до границ открытой секции, закрываем её
            while (!sections_stack.empty() &&
                   (SchemeFile.tellg() >= sections_stack.back().start_pos + sections_stack.back().sect_size)) {
                CloseSection();
            }

            // Если обнаружили флаг секции, открываем её
            if (buffer == nullptr && byte == section_flag)
                EnterSection();

                // Если обнаружили флаг блока, открываем его
            else if (buffer == nullptr && (static_cast<uint8_t>(byte) & block_flag) == block_flag)
                EnterBlock();

                // Если буффер не пустой, а мы не находимся ни в секции, ни в блоке, значит что-то сломалось :/
            else {
                PrintLog("Ошибка при чтении файла, нарушена структура байтов", true, 12);
                return false;
            }
        }

        // Если остались незакрытые секции, закрываем их
        while (!sections_stack.empty()) {
            CloseSection();
        }

        SchemeFile.close();
        LogsFile.close();

        return true;

    }

    // Функция открытия рабочих файлов
    bool OpenWorkFiles(const std::wstring& schemefile_path, const std::string& logfile_path) {
        SchemeFile.open(schemefile_path.c_str(), std::ios_base::binary);
        LogsFile.open(logfile_path, std::ios_base::binary);

        if (!SchemeFile) {
            PrintLog("Файл схемы не был открыт", true, 12);
            return false;
        }

        if (!LogsFile) {
            PrintLog("Файл логов не был открыт", true, 12);
            return false;
        }

        PrintLog("Файлы схемы и логов успешно открыты", true, 2);
        GetFileSize();

        return true;

    }

};


