#include <iostream>
#include <fstream>
#include <cinttypes>
#include <locale>
#include <windows.h>
#include <bitset>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
std::ofstream LogFile;

// выводит в консоль какая секция была открыта
void PrintLogSectOpen(bool is_scheme_section, bool is_section_in_main) {
    SetConsoleTextAttribute(hConsole, 2);

    if (is_scheme_section) {
        std::cout << '\n' << "MAIN SECTION OPENED ";
        LogFile << '\n' << '\n' << "MAIN SECTION OPENED ";
    } else if (is_section_in_main) {
        SetConsoleTextAttribute(hConsole, 7);
        std::cout << '\n' << "----";
        LogFile << '\n' << "----";
        SetConsoleTextAttribute(hConsole, 2);
        std::cout << " INTER SECTION OPENED ";
        LogFile << " INTER SECTION OPENED ";
    } else {
        std::cout << '\n' << "SECTION OPENED ";
        LogFile << '\n' << "SECTION OPENED ";
    }
}

// выводит в консоль имя секции
void PrintSectName(char* buffer, bool is_section_in_main) {
    SetConsoleTextAttribute(hConsole, 12);
    std::cout << "section name: ";
    LogFile << "section name: ";

    SetConsoleTextAttribute(hConsole, 1);
    for (uint32_t i = 0; i < 4; ++i) {
        std::cout << buffer[i];
        LogFile << buffer[i];
    }

    SetConsoleTextAttribute(hConsole, 12);
    if (!is_section_in_main) {
        std::cout << '\n' << "section data: ";
        LogFile << '\n' << "section data: ";
    } else {
        SetConsoleTextAttribute(hConsole, 7);
        std::cout << '\n' << "----";
        LogFile << '\n' << "----";
        SetConsoleTextAttribute(hConsole, 12);
        std::cout << " section data: ";
        LogFile << " section data: ";
    }
}

// выводит в консоль размер секции
void PrintSectSize(const uint32_t& section_size) {
    SetConsoleTextAttribute(hConsole, 12);
    std::cout << "section size: ";
    LogFile << "section size: ";

    SetConsoleTextAttribute(hConsole, 1);
    std::cout << section_size << ' ';
    LogFile << section_size << ' ';
}

// выводит в консоль размер файла
void PrintFileSize(const uint32_t& file_size) {
    SetConsoleTextAttribute(hConsole, 12);
    std::cout << '\n' << "file size: ";
    LogFile << '\n' << "file size: ";
    SetConsoleTextAttribute(hConsole, 1);
    std::cout << file_size << " bytes \n";
    LogFile << file_size << " bytes \n";
}


int main() {

    // setlocale(LC_ALL, "rus");

    std::ifstream SchemeFile;

    SchemeFile.open(L"Линия.схема", std::ios_base::binary);
    LogFile.open("logs\\SchemeLogs.txt", std::ios_base::binary);

    if (!SchemeFile or !SchemeFile) {
        std::cout << "File wasn't open\n";
    }

    SchemeFile.seekg(0, std::ios::end);
    uint32_t file_size = SchemeFile.tellg();
    SchemeFile.seekg(0, std::ios::beg);

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

    std::bitset<8> print_byte;
    std::bitset<32> print_four_bytes;

    bool is_main_section = true;
    bool is_section_in_main = false;

    bool is_in_setion = true;

    uint32_t main_section_size;

    // выводит в консоль размер файла
    PrintFileSize(file_size);

    while (!SchemeFile.eof() and SchemeFile.get(byte)) {

        if (!section_opened && byte == section_flag) {
            section_opened = true;

            uint32_t curr_pos = SchemeFile.tellg();
            if (is_section_in_main && (curr_pos > main_section_size)) {
                is_section_in_main = false;
            }

            // выводит в консоль какая секция была открыта
            PrintLogSectOpen(is_main_section, is_section_in_main);

            if (buffer != nullptr) {
                delete[] buffer;
            }
            buffer = new char[4];

            SchemeFile.read(buffer, 4);

            section_size = 0;
            for (int8_t i = 3; i >= 0; --i) {
                section_size |= static_cast<uint8_t>(buffer[i]);

                if (i != 0)
                    section_size <<= 8;
            }

            // выводит в консоль размер секции
            PrintSectSize(section_size);

            delete[] buffer;
            buffer = new char[4];

            SchemeFile.read(buffer, 4);

            // выводит в консоль имя секции
            PrintSectName(buffer, is_section_in_main);

            if (!is_main_section) {
                delete[] buffer;
                buffer = new char[section_size];

                SchemeFile.read(buffer, section_size);

                SetConsoleTextAttribute(hConsole, 15);
                for (uint32_t i = 0; i < section_size; ++i) {
                    print_byte = buffer[i];
                    std::cout << print_byte << ' ';
                    LogFile << print_byte << ' ';
                }
            } else {
                is_main_section = false;
                is_section_in_main = true;
                main_section_size = section_size;
            }

            section_opened = false;
            section_size = 0;

        }

    }

    SchemeFile.close();
    LogFile.close();

    return 0;
}