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

    uint8_t section_flag = 0b00000000;      // Признак секции
    uint8_t block_flag = 0b10000000;        // Признак блока

    uint8_t size_6_bit = 0b11000000;        // Признак блока с длиной 6 бит "1 1 xxxxxx", xxxxxx - размер блока
    uint8_t size_8_bit = 0b10000000;        // Признак блока с длиной 8 бит
    uint8_t size_16_bit = 0b10000001;       // Признак блока с длиной 16 бит
    uint8_t size_32_bit = 0b10000010;       // Признак блока с длиной 32 бит

#pragma pack(push, 1)
    // Структура секции
    struct Section {
        uint32_t sect_size{0};          // Размер секции
        uint32_t start_pos;             // Номер стартового байта секции

        std::string sect_name;          // Имя секции (пустое, если есть номер)
        uint32_t sect_number{0};        // Номер секции (пустой, если есть имя)
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

    // Функция записи в файл логов
    template<class LogType>
    void WriteLog(const LogType& report, bool new_string = false, int8_t colour = 15) {
        SetConsoleTextAttribute(hConsole, colour);

        LogsFile << report << ' ';
        //std::cout << report << ' ';

        if (new_string) {
            LogsFile << '\n';
            // std::cout << '\n';
        }
    }

    // шаблон получения числового значения из файла (some_int ОБЯЗАТЕЛЬНО должен иметь нулевое значение!)
    template<class IntType>
    IntType GetSomeInt(IntType some_int, int8_t block_size, bool is_buffer_filled = false) {

        if (!is_buffer_filled) {
            ClearBuffer();
            buffer = new char[block_size];
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
        SetConsoleTextAttribute(hConsole, 2);
        std::cout << "Файлы схемы и логов успешно открыты\n";

        SchemeFile.seekg(0, std::ios::end);    // Курсор ставится в конец файла
        file_size = SchemeFile.tellg();        // Записывается позиция курсора

        SchemeFile.seekg(0, std::ios::beg);    // Курсор возвращается в начало файла
        SchemeFile.clear();                    // С файла сбрасываются возможные ошибки чтения

        std::cout << "Размер файла схемы: " << file_size << '\n';

        WriteLog("\nFile size: ", false, 12);
        WriteLog(file_size, false, 1);
        WriteLog(" bytes\n", true, 12);
    }

    // Функция закрытия секции
    void CloseSection() {
        // Если размер стека секция больше 1, то секция считается вложенной
        if (sections_stack.size() > 1) {
            for (int16_t i = 1; i < sections_stack.size(); ++i)
                WriteLog("- ", false, 7);
            WriteLog("INTER ", false, 2);
        }

        WriteLog("SECTION CLOSED ", false, 2);

        // Если имя секции пустое, выводися её номер
        if (sections_stack.back().sect_name.empty()) {
            WriteLog("section id: ", false, 4);
            WriteLog(sections_stack.back().sect_number, true, 1);
            sections_stack.pop_back();
            // В противном случае выводится имя секции
        } else {
            WriteLog("section name: ", false, 4);
            WriteLog(sections_stack.back().sect_name, true, 1);
            sections_stack.pop_back();
        }

    }

    // Функция чтения заголовка секции схемы
    void EnterSection() {
        // Если стек секции не пустой, секция считается вложенной
        if (!sections_stack.empty()) {
            for (int16_t i = 0; i < sections_stack.size(); ++i)
                WriteLog("- ", false, 7);
            WriteLog("INTER ", false, 2);
        }
        WriteLog("SECTION OPENED ", false, 2);

        // Новый экземпляр структуры секции
        Section new_section;

        // Считаем размер секции
        new_section.sect_size = GetSomeInt(new_section.sect_size, 4);
        // new_section.sect_size = tmp_section_size;

        // Находим имя или номер секции
        buffer = new char[4];
        SchemeFile.read(buffer, 4);

        // Если байт это буква, то считаем, что это именнованная секция
        if (isalpha(buffer[0])) {
            char tmp_section_name[5];
            GetSectName(tmp_section_name);

            new_section.sect_name = tmp_section_name;
            WriteLog("section name: ", false, 4);
            WriteLog(new_section.sect_name, false, 1);

            // В противном случае, считаем, что это нумерованная секция
        } else {
            new_section.sect_number = GetSomeInt(new_section.sect_number, 4, true);

            WriteLog(" section number: ", false, 4);
            WriteLog(new_section.sect_number, false, 1);
        }

        // Запоминаем стартовую позицию секции
        new_section.start_pos = SchemeFile.tellg();
        ++new_section.start_pos;

        // Добавляем новую секцию в стек
        sections_stack.push_back(new_section);

        WriteLog(" section size: ", false, 4);
        WriteLog(sections_stack.back().sect_size, true, 1);

        ClearBuffer();
    }

    // Функция чтения блока байтов в схеме
    void EnterBlock() {
        int8_t tmp_bytes_for_blocksize = 0;
        uint32_t tmp_block_size = 0;

        // По признаку блока определяем его размер
        if ((static_cast<uint8_t>(byte) & size_6_bit) == size_6_bit)
            tmp_block_size |= (static_cast<uint8_t>(byte) & 0b00111111);

        else if (static_cast<uint8_t>(byte) == size_8_bit)
            tmp_bytes_for_blocksize = 1;
        else if (static_cast<uint8_t>(byte) == size_16_bit)
            tmp_bytes_for_blocksize = 2;
        else if (static_cast<uint8_t>(byte) == size_32_bit)
            tmp_bytes_for_blocksize = 4;

        // Если размер блока не уместился в 6 бит, берём его исходя из нужного признака
        if (tmp_bytes_for_blocksize != 0 || tmp_block_size != 0) {
            if (tmp_block_size == 0) {
                tmp_block_size = GetSomeInt(tmp_block_size, tmp_bytes_for_blocksize);
            }

            ClearBuffer();
            buffer = new char[tmp_block_size];

            ReadInfoInBlock(tmp_block_size);

        }
    }

    void ReadInfoInBlock(const uint32_t& block_size);

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
                SetConsoleTextAttribute(hConsole, 12);
                std::cout << "Ошибка при чтении файла, нарушена структура байтов\n";
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
            std::cout << "Файл схемы не был открыт\n";
            return false;
        }

        if (!LogsFile) {
            std::cout << "Файл логов не был открыт\n";
            return false;
        }

        GetFileSize();

        return true;

    }

};


