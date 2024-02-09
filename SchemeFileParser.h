#include <iostream>
#include <fstream>
#include <cinttypes>
#include <locale>
#include <windows.h>
#include <bitset>
#include <stack>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

class SchemeFileParser {
private:
    std::ofstream LogsFile;
    std::ifstream SchemeFile;

    uint32_t file_size;

    //Признак блока "1 xxxxxxx"
    uint8_t block_flag = 0b10000000;
    //Признак блока с длиной 6 бит "1 xxxxxx", xxxxxx - размер блока
    uint8_t size_6_bit = 0b11000000;

    //Признак блока с длиной 8 бит "0 000000"
    uint8_t size_8_bit = 0b00;
    //Признак блока с длиной 16 бит "0 000001"
    uint8_t size_16_bit = 0b01;
    //Признак блока с длиной 32 бит "0 000010"
    uint8_t size_32_bit = 0b10;

    //Признак секции "0000 0000"
    uint8_t section_flag = 0b0;

#pragma pack(push, 1)

    struct SectionNode {
        uint32_t sect_size;
        uint32_t start_pos;

        std::string sect_name;
        uint32_t sect_id;
    };

#pragma pack(pop)

    std::stack<SectionNode> sections_stack;

    char byte;
    char* buffer = nullptr;
    char* block = nullptr;

    std::string check_name;

    std::bitset<8> print_byte;
    std::bitset<32> print_four_bytes;

    template<class LogFirstType, class LogSecondType = uint32_t>
    void WriteLog(const LogFirstType& report, int8_t colour = 15, const LogSecondType* value = nullptr,
                  bool new_string = false) {
        SetConsoleTextAttribute(hConsole, colour);

        if (value == nullptr) {
            LogsFile << report;
            std::cout << report;
        } else {
            LogsFile << report << *value << ' ';
            std::cout << report << *value << ' ';
        }

        if (new_string) {
            LogsFile << '\n';
            std::cout << '\n';
        }
    }

    void EnterSection() {
        WriteLog("SECTION OPENED ", 2);

        SectionNode new_section;

        if (buffer != nullptr) {
            delete[] buffer;
        }
        buffer = new char[5];
        SchemeFile.read(buffer, 4);

        uint32_t tmp_section_size = 0;
        for (int8_t i = 3; i >= 0; --i) {
            tmp_section_size |= static_cast<uint8_t>(buffer[i]);

            if (i != 0)
                tmp_section_size <<= 8;
        }

        new_section.sect_size = tmp_section_size;

        delete[] buffer;
        buffer = new char[5];
        SchemeFile.read(buffer, 4);

        char tmp_section_name[5] = "    ";
        uint32_t tmp_section_id = 0;
        if (isalnum(buffer[0])) {

            for (int8_t i = 0; i < 4; ++i) {
                tmp_section_name[i] = buffer[i];
            }

            new_section.sect_name = tmp_section_name;
            WriteLog("section name: ", 4);
            WriteLog(new_section.sect_name, 1, &" ");

        } else {
            for (int8_t i = 3; i >= 0; --i) {
                tmp_section_id |= static_cast<uint8_t>(buffer[i]);

                if (i != 0)
                    tmp_section_id <<= 8;
            }

            new_section.sect_id = tmp_section_id;
            WriteLog("section id: ", 4);
            WriteLog(new_section.sect_id, 1, &" ");
        }

        new_section.start_pos = SchemeFile.tellg();
        ++new_section.start_pos;

        sections_stack.push(new_section);

        WriteLog("section size: ", 4);
        WriteLog(sections_stack.top().sect_size, 1, &"", true);
    }

    void EnterBlock() {
        int8_t tmp_bytes_for_blocksize = 0;
        uint32_t tmp_block_size = 0;

        if ((static_cast<uint8_t>(byte) & 0b11000000) == size_6_bit) {

            tmp_block_size |= (static_cast<uint8_t>(byte) << 2);
            tmp_block_size >>= 2;
            tmp_block_size &= 0b00111111;

            if (block != nullptr) {
                delete[] block;
            }
            block = new char[tmp_block_size + 1];

            SchemeFile.read(block, tmp_block_size);
            for (uint32_t i = 0; i < tmp_block_size; ++i) {
                print_byte = block[i];
                WriteLog(print_byte, 15, " ");
            }
            WriteLog("\n");

            delete[] block;
            block = nullptr;

        } else if ((static_cast<uint8_t>(byte) & 0b00111111) == size_8_bit) {
            tmp_bytes_for_blocksize = 1;
        } else if ((static_cast<uint8_t>(byte) & 0b00111111) == size_16_bit) {
            tmp_bytes_for_blocksize = 2;
        } else if ((static_cast<uint8_t>(byte) & 0b00111111) == size_32_bit) {
            tmp_bytes_for_blocksize = 4;
        }

        if (tmp_bytes_for_blocksize != 0) {
            delete[] buffer;
            buffer = new char[tmp_bytes_for_blocksize + 1];

            SchemeFile.read(buffer, tmp_bytes_for_blocksize);
            for (int8_t i = tmp_bytes_for_blocksize - 1; i >= 0; --i) {
                tmp_block_size |= static_cast<uint8_t>(buffer[i]);

                if (i != 0)
                    tmp_block_size <<= 8;
            }

            if (block != nullptr) {
                delete[] block;
            }
            block = new char[tmp_block_size];

            SchemeFile.read(block, tmp_block_size);
            for (uint32_t i = 0; i < tmp_block_size; ++i) {
                print_byte = block[i];
                WriteLog(print_byte, 15, " ");
            }
            WriteLog("\n");

            delete[] block;
            block = nullptr;
        }
    }

    void CloseSection() {
        WriteLog("SECTION CLOSED ", 2);
        if (sections_stack.top().sect_name.empty()) {
            WriteLog("section id: ", 4);
            WriteLog(sections_stack.top().sect_id, 1, &"", true);
            sections_stack.pop();
        } else {
            WriteLog("section name: ", 4);
            WriteLog(sections_stack.top().sect_name, 1, &"", true);
            sections_stack.pop();
        }

    }

public:
    bool OpenWorkFiles(const std::wstring& schemefile_path, const std::string& logfile_path) {
        SchemeFile.open(schemefile_path.c_str(), std::ios_base::binary);
        LogsFile.open(logfile_path, std::ios_base::binary);

        if (!SchemeFile) {
            std::cout << "SchemeFile wasn't open\n";
            return false;
        }

        if (!LogsFile) {
            std::cout << "LogsFile wasn't open\n";
            return false;
        }

        SchemeFile.seekg(0, std::ios::end);
        file_size = SchemeFile.tellg();
        SchemeFile.seekg(0, std::ios::beg);

        SchemeFile.clear();

        WriteLog("\nFile size: ", 12);
        WriteLog(file_size, 1);
        WriteLog(" bytes\n", 12, &"", true);

        return true;

    }

    bool Parsing() {
        while (SchemeFile.get(byte)) {
            while (!sections_stack.empty() &&
                   (SchemeFile.tellg() >= sections_stack.top().start_pos + sections_stack.top().sect_size)) {
                CloseSection();
            }

            if (block == nullptr && byte == section_flag) {
                EnterSection();

            } else if (block == nullptr and (static_cast<uint8_t>(byte) & 0b10000000) == block_flag) {
                EnterBlock();

            }
        }

        while (!sections_stack.empty()) {
            CloseSection();
        }

        SchemeFile.close();
        LogsFile.close();

        return true;

    }

};


