#include <iostream>
#include <fstream>
#include <cinttypes>
#include <locale>
#include <windows.h>
#include <bitset>
#include <stack>
#include <vector>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

struct SCHM_ITEM{
    std::string name;
    char type;
};

std::string current_named_section;

char schm_obj_counter = 0;
std::vector<SCHM_ITEM> schm_items {{"Version", 0},
                                   {"name[1].length", 2},
                                   {"name[1]", 1},
                                   {"DBIP[1].length", 2},
                                   {"DBIP[1]", 1},
                                   {"DBAlias[1].length", 2},
                                   {"DBAlias", 1},
                                   {"width", 0},
                                   {"height", 0},
                                   {"tmp (none)", 0},
                                   {"tmp (none)", 0},
                                   {"WorkScale", 0},
                                   {"TColorToMColor(TColor(tmp))(BGColor):", 0},
                                   {"TColorToMColor(TColor(tmp))(NetColor):", 0},
                                   {"BitDepth", 0},
                                   {"Count Of Objects", 0},
                                   {"WindowsSize.x", 0},
                                   {"WindowsSize.y", 0}
};
char cach_obj_counter = 0;
std::vector<SCHM_ITEM> cach_items {{"CacheObject.Count", 0}
};
char link_obj_counter = 0;
std::vector<SCHM_ITEM> link_items {{"Links.Count", 0}
};
char sect_obj_counter = 0;
std::vector<SCHM_ITEM> sect_items {{"NextSectionNumber", 0},
                                   {"tmp1(counter of sections)", 0}
};
char objs_obj_counter = 0;
std::vector<SCHM_ITEM> objs_items {{"Object.Count", 0}
};
char extd_obj_counter = 0;
std::vector<SCHM_ITEM> extd_items {{"FWorkVariable", 0}
};
char sch2_obj_counter = 0;
std::vector<SCHM_ITEM> sch2_items {{"WindowSize.X", 0},
                                   {"WindowSize.Y", 0},
                                   {"tmpbool", 2},
                                   {"MS.SetSize(tmp)", 0},
                                   {"BackBitmap.LoadFromStream(MS)", 0},
                                   {"PixelsPerInchX", 0},
                                   {"PixelsPerInchY", 0}

};

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
            //std::cout << report;
        } else {
            LogsFile << report << *value << ' ';
            //std::cout << report << *value << ' ';
        }

        if (new_string) {
            LogsFile << '\n';
            //std::cout << '\n';
        }
    }

    void EnterSection() {
        if (!sections_stack.empty()) {
            for (int16_t i = 0; i < sections_stack.size(); ++i)
                WriteLog("- ", 7);
            WriteLog("INTER ", 2);
        }

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



        } else if ((static_cast<uint8_t>(byte) & 0b00111111) == size_8_bit) {
            tmp_bytes_for_blocksize = 1;
        } else if ((static_cast<uint8_t>(byte) & 0b00111111) == size_16_bit) {
            tmp_bytes_for_blocksize = 2;
        } else if ((static_cast<uint8_t>(byte) & 0b00111111) == size_32_bit) {
            tmp_bytes_for_blocksize = 4;
        }

        if (tmp_bytes_for_blocksize != 0 || tmp_block_size != 0) {
            if (tmp_block_size == 0){
                delete[] buffer;
                buffer = new char[tmp_bytes_for_blocksize + 1];

                SchemeFile.read(buffer, tmp_bytes_for_blocksize);
                for (int8_t i = tmp_bytes_for_blocksize - 1; i >= 0; --i) {
                    tmp_block_size |= static_cast<uint8_t>(buffer[i]);

                    if (i != 0)
                        tmp_block_size <<= 8;
                }
            }


            if (block != nullptr) {
                delete[] block;
            }


            block = new char[tmp_block_size]; //TODO место

            if(sections_stack.top().sect_name == "schm"){
                SchemeFile.read(block, tmp_block_size);
                WriteLog(schm_items[schm_obj_counter].name + ": ");
                if(schm_items[schm_obj_counter].type == 0 || schm_items[schm_obj_counter].type == 2){ //чтение типа 0/2 (число)
                    uint32_t block_value = 0;
                    for (int32_t i = tmp_block_size-1; i >= 0; --i) {
                        block_value |= static_cast<uint8_t>(block[i]);
                        if (i != 0){
                            block_value <<= 8;
                        }
                    }
                    if(schm_items[schm_obj_counter].type == 2){ //проверка размера (если = 0, отсутсвует вхождение)
                        if (block_value == 0){
                            schm_obj_counter += 1;
                        }
                    }
                    WriteLog(block_value);
                } else{ //чтение типа 1 (строка)
                    for (uint32_t i = 0; i < tmp_block_size; ++i) {
                        WriteLog(block[i]);
                    }
                }
                WriteLog("\n");
                schm_obj_counter += 1;
            }
            else if(sections_stack.top().sect_name == "cach") {
                SchemeFile.read(block, tmp_block_size);
                WriteLog(cach_items[cach_obj_counter].name + ": ");
                if(cach_items[cach_obj_counter].type == 0 || cach_items[cach_obj_counter].type == 2){ //чтение типа 0/2 (число)
                    uint32_t block_value = 0;
                    for (int32_t i = tmp_block_size-1; i >= 0; --i) {
                        block_value |= static_cast<uint8_t>(block[i]);
                        if (i != 0){
                            block_value <<= 8;
                        }
                    }
                    if(cach_items[cach_obj_counter].type == 2){ //проверка размера (если = 0, отсутсвует вхождение)
                        if (block_value == 0){
                            cach_obj_counter += 1;
                        }
                    }
                    WriteLog(block_value);
                } else{ //чтение типа 1 (строка)
                    for (uint32_t i = 0; i < tmp_block_size; ++i) {
                        WriteLog(block[i]);
                    }
                }
                WriteLog("\n");
                cach_obj_counter += 1;
            }
            else if (sections_stack.top().sect_name == "link"){
                SchemeFile.read(block, tmp_block_size);
                WriteLog(link_items[link_obj_counter].name + ": ");
                if(link_items[link_obj_counter].type == 0 || link_items[link_obj_counter].type == 2){ //чтение типа 0/2 (число)
                    uint32_t block_value = 0;
                    for (int32_t i = tmp_block_size-1; i >= 0; --i) {
                        block_value |= static_cast<uint8_t>(block[i]);
                        if (i != 0){
                            block_value <<= 8;
                        }
                    }
                    if(link_items[link_obj_counter].type == 2){ //проверка размера (если = 0, отсутсвует вхождение)
                        if (block_value == 0){
                            link_obj_counter += 1;
                        }
                    }
                    WriteLog(block_value);
                } else{ //чтение типа 1 (строка)
                    for (uint32_t i = 0; i < tmp_block_size; ++i) {
                        WriteLog(block[i]);
                    }
                }
                WriteLog("\n");
                link_obj_counter += 1;
            }
            else if (sections_stack.top().sect_name == "sect"){
                SchemeFile.read(block, tmp_block_size);
                WriteLog(sect_items[sect_obj_counter].name + ": ");
                if(sect_items[sect_obj_counter].type == 0 || sect_items[sect_obj_counter].type == 2){ //чтение типа 0/2 (число)
                    uint32_t block_value = 0;
                    for (int32_t i = tmp_block_size-1; i >= 0; --i) {
                        block_value |= static_cast<uint8_t>(block[i]);
                        if (i != 0){
                            block_value <<= 8;
                        }
                    }
                    if(sect_items[sect_obj_counter].type == 2){ //проверка размера (если = 0, отсутсвует вхождение)
                        if (block_value == 0){
                            sect_obj_counter += 1;
                        }
                    }
                    WriteLog(block_value);
                } else{ //чтение типа 1 (строка)
                    for (uint32_t i = 0; i < tmp_block_size; ++i) {
                        WriteLog(block[i]);
                    }
                }
                WriteLog("\n");
                sect_obj_counter += 1;
            }
            else if (sections_stack.top().sect_name == "objs"){
                SchemeFile.read(block, tmp_block_size);
                WriteLog(objs_items[objs_obj_counter].name + ": ");
                if(objs_items[objs_obj_counter].type == 0 || objs_items[objs_obj_counter].type == 2){ //чтение типа 0/2 (число)
                    uint32_t block_value = 0;
                    for (int32_t i = tmp_block_size-1; i >= 0; --i) {
                        block_value |= static_cast<uint8_t>(block[i]);
                        if (i != 0){
                            block_value <<= 8;
                        }
                    }
                    if(objs_items[objs_obj_counter].type == 2){ //проверка размера (если = 0, отсутсвует вхождение)
                        if (block_value == 0){
                            objs_obj_counter += 1;
                        }
                    }
                    WriteLog(block_value);
                } else{ //чтение типа 1 (строка)
                    for (uint32_t i = 0; i < tmp_block_size; ++i) {
                        WriteLog(block[i]);
                    }
                }
                WriteLog("\n");
                objs_obj_counter += 1;
            }
            else if (sections_stack.top().sect_name == "extd"){ //TODO эта секция может вызывать ошибки чтения (нереализованные функции, но нигде не используются)
                SchemeFile.read(block, tmp_block_size);
                WriteLog(extd_items[extd_obj_counter].name + ": ");
                if(extd_items[extd_obj_counter].type == 0 || extd_items[extd_obj_counter].type == 2){ //чтение типа 0/2 (число)
                    uint32_t block_value = 0;
                    for (int32_t i = tmp_block_size-1; i >= 0; --i) {
                        block_value |= static_cast<uint8_t>(block[i]);
                        if (i != 0){
                            block_value <<= 8;
                        }
                    }
                    if(extd_items[extd_obj_counter].type == 2){ //проверка размера (если = 0, отсутсвует вхождение)
                        if (block_value == 0){
                            extd_obj_counter += 1;
                        }
                    }
                    WriteLog(block_value);
                } else{ //чтение типа 1 (строка)
                    for (uint32_t i = 0; i < tmp_block_size; ++i) {
                        WriteLog(block[i]);
                    }
                }
                WriteLog("\n");
                extd_obj_counter += 1;
            }
            else if (sections_stack.top().sect_name == "sch2"){
                SchemeFile.read(block, tmp_block_size);
                WriteLog(sch2_items[sch2_obj_counter].name + ": ");
                if(sch2_items[sch2_obj_counter].type == 0 || sch2_items[sch2_obj_counter].type == 2){ //чтение типа 0/2 (число)
                    uint32_t block_value = 0;
                    for (int32_t i = tmp_block_size-1; i >= 0; --i) {
                        block_value |= static_cast<uint8_t>(block[i]);
                        if (i != 0){
                            block_value <<= 8;
                        }
                    }
                    if(sch2_items[sch2_obj_counter].type == 2){ //проверка размера (если = 0, отсутсвует вхождение)
                        if (block_value == 0){
                            sch2_obj_counter += 2;
                        }
                    }
                    WriteLog(block_value);
                } else{ //чтение типа 1 (строка)
                    for (uint32_t i = 0; i < tmp_block_size; ++i) {
                        WriteLog(block[i]);
                    }
                }
                WriteLog("\n");
                sch2_obj_counter += 1;
            }
            else {SchemeFile.read(block, tmp_block_size);
                for (uint32_t i = 0; i < tmp_block_size; ++i) {
                    print_byte = block[i];
                    WriteLog(print_byte, 6, " ");
                }
                WriteLog(": ");

                if(tmp_block_size < 5){
                    uint32_t block_value = 0;
                    for (int32_t i = tmp_block_size-1; i >= 0; --i) {
                        block_value |= static_cast<uint8_t>(block[i]);
                        if (i != 0){
                            block_value <<= 8;
                        }
                    }
                    WriteLog(block_value);
                } else{
                    for (uint32_t i = 0; i < tmp_block_size; ++i) {
                        WriteLog(block[i]);
                        WriteLog(' ');
                    }
                }
                WriteLog("\n");}



            delete[] block;
            block = nullptr;
        }
    }

    void CloseSection() {
        if (!sections_stack.empty() && sections_stack.size() > 1) {
            for (int16_t i = 1; i < sections_stack.size(); ++i)
                WriteLog("- ", 7);
            WriteLog("INTER ", 2);
        }

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


