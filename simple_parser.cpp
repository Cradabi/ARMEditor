#include <iostream>
#include <fstream>
#include <cinttypes>
#include <locale>
#include <windows.h>
#include <bitset>

int main() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // setlocale(LC_ALL, "rus");

    std::ifstream file;

    file.open(L"Новая схема.схема", std::ios_base::binary);

    if (!file) {
        std::cout << "File wasn't open\n";
    }

    file.seekg(0, std::ios::end);
    uint32_t file_size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::string section_names[10] = {"ARM ", "lib", "schm",
                                     "cach", "link", "sect",
                                     "objs", "extd", "sch2",
                                     "font"};

    //Признак блока "1 xxxxxxx"
    uint8_t raw_data_flag = 0x80;

    //Признак блока с длиной 6 бит "1 xxxxxx", xxxxxx - размер блока
    uint8_t internal_size_flag = 0x40;
    //Признак блока с длиной 8 бит "0 000000"
    uint8_t size_8_bit = 0x00;
    //Признак блока с длиной 16 бит "0 000001"
    uint8_t size_16_bit = 0x01;
    //Признак блока с длиной 32 бит "0 000010"
    uint8_t size_32_bit = 0x02;

    //Признак секции "0000 0000"
    uint8_t section_flag = 0;

    bool section_opened = false;
    uint32_t section_size = 0;

    char byte;
    char* buffer = nullptr;

    std::string check_name;

    std::bitset<8> print_binary;

    bool is_scheme_section = true;
    bool is_section_in_main = false;

    uint32_t main_section_size;

    while (!file.eof() and file.get(byte)) {

        if (!section_opened && byte == section_flag) {
            section_opened = true;

            uint32_t curr_pos = file.tellg();
            if (is_section_in_main && (curr_pos == main_section_size - 4)) {
                is_section_in_main = false;
            }

            SetConsoleTextAttribute(hConsole, 2);

            if (is_scheme_section)
                std::cout << '\n' << "MAIN SECTION OPENED ";
            else if (is_section_in_main) {
                SetConsoleTextAttribute(hConsole, 7);
                std::cout << '\n' << "----";
                SetConsoleTextAttribute(hConsole, 2);
                std::cout << " INTER SECTION OPENED ";
            } else
                std::cout << '\n' << "SECTION OPENED ";

            if (buffer != nullptr) {
                delete[] buffer;
            }
            buffer = new char[4];

            file.read(buffer, 4);
            for (uint8_t i = 0; i < 4; ++i) {
                if (buffer[i] != 0) {
                    section_size = (section_size << 8) | (static_cast<uint8_t>(buffer[i]));
                }
            }

            SetConsoleTextAttribute(hConsole, 12);
            std::cout << "section size: ";

            SetConsoleTextAttribute(hConsole, 1);
            std::cout << section_size << ' ';

            SetConsoleTextAttribute(hConsole, 12);
            std::cout << "section name: ";

            delete[] buffer;
            buffer = new char[4];

            file.read(buffer, 4);

            SetConsoleTextAttribute(hConsole, 1);
            for (uint32_t i = 0; i < 4; ++i) {
                std::cout << buffer[i];
            }

            SetConsoleTextAttribute(hConsole, 12);
            if (!is_section_in_main)
                std::cout << '\n' << "section data: ";
            else {
                SetConsoleTextAttribute(hConsole, 7);
                std::cout << '\n' << "----";
                SetConsoleTextAttribute(hConsole, 12);
                std::cout << " section data: ";
            }

            if (!is_scheme_section) {
                delete[] buffer;
                buffer = new char[section_size];

                file.read(buffer, section_size);

                SetConsoleTextAttribute(hConsole, 15);
                for (uint32_t i = 0; i < section_size; ++i) {
                    print_binary = buffer[i];
                    std::cout << print_binary << ' ';
                }
            } else {
                is_scheme_section = false;
                is_section_in_main = true;
                main_section_size = section_size;
            }

            section_opened = false;
            section_size = 0;

        }

    }

    file.close();

    SetConsoleTextAttribute(hConsole, 12);
    std::cout << '\n' << '\n';
    std::cout << "file size: ";
    SetConsoleTextAttribute(hConsole, 1);
    std::cout << file_size;
    SetConsoleTextAttribute(hConsole, 12);
    std::cout << " bytes \n";

    return 0;
}