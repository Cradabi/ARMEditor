#include "SchemeFileParser.h"


void SchemeFileParser::ParseSCHM() {
    // Пока не дошли до конца секции, считываем данные
    while (SchemeFile.tellg() < sections_stack.back().start_pos + sections_stack.back().sect_size) {
        SchemeFile.get(byte);

        uint8_t data_counter{0};
        uint32_t block_size;
        // Если нашли флаг блока, открываем его
        if ((static_cast<uint8_t>(byte) & scheme_flags.block_flag) == scheme_flags.block_flag) {
            // Получаем размер блока
            block_size = GetBlockSize();
            ++data_counter;

            std::string tmp_work_scale = "";
            switch (data_counter) {
                case schm_data.version_flag:
                    schm_data.version = GetSomeInt(schm_data.version, block_size);
                    break;
                case schm_data.name_length_flag:
                    schm_data.name_length = GetSomeInt(schm_data.name_length, block_size);
                    break;
                case schm_data.scheme_name_flag:
                    for (uint32_t digit = 0; digit < block_size; ++block_size) {
                        SchemeFile.get(byte);
                        schm_data.scheme_name += byte;
                    }
                    break;
                case schm_data.DBIP_length_flag:
                    schm_data.DBIP_length = GetSomeInt(schm_data.DBIP_length, block_size);
                    if (schm_data.DBIP_length == 0)
                        ++data_counter;
                    break;
                case schm_data.DBIP_flag:
                    for (uint32_t digit = 0; digit < block_size; ++block_size) {
                        SchemeFile.get(byte);
                        schm_data.DBIP += byte;
                    }
                    break;
                case schm_data.DBAlias_length_flag:
                    schm_data.DBAlias_length = GetSomeInt(schm_data.DBAlias_length, block_size);
                    if (schm_data.DBAlias_length == 0)
                        ++data_counter;
                    break;
                case schm_data.DBAlias_flag:
                    for (uint32_t digit = 0; digit < block_size; ++block_size) {
                        SchemeFile.get(byte);
                        schm_data.DBAlias += byte;
                    }
                    break;
                case schm_data.width_flag:
                    schm_data.width = GetSomeInt(schm_data.width, block_size);
                    break;
                case schm_data.height_flag:
                    schm_data.height = GetSomeInt(schm_data.height, block_size);
                    break;
                case schm_data.reserved_1_flag:
                    schm_data.reserved_1 = GetSomeInt(schm_data.reserved_1, block_size);
                    break;
                case schm_data.reserved_2_flag:
                    schm_data.reserved_2 = GetSomeInt(schm_data.reserved_2, block_size);
                    break;
                case schm_data.work_scale_flag:
                    for (uint32_t digit = 0; digit < block_size; ++block_size) {
                        SchemeFile.get(byte);
                        tmp_work_scale += byte;
                    }
                    schm_data.work_scale = std::stod(tmp_work_scale);
                    break;
                case schm_data.bg_color_flag:
                    SchemeFile.read(buffer, block_size);
                    schm_data.bg_color.blue = static_cast<uint8_t>(buffer[0]);
                    schm_data.bg_color.blue = static_cast<uint8_t>(buffer[1]);
                    schm_data.bg_color.blue = static_cast<uint8_t>(buffer[2]);
                    // schm_data.bg_color.reserved = static_cast<uint8_t>(buffer[4]);
                    break;
                case schm_data.net_color_flag:
                    SchemeFile.read(buffer, block_size);
                    schm_data.net_color.blue = static_cast<uint8_t>(buffer[0]);
                    schm_data.net_color.blue = static_cast<uint8_t>(buffer[1]);
                    schm_data.net_color.blue = static_cast<uint8_t>(buffer[2]);
                    // schm_data.bg_color.reserved = static_cast<uint8_t>(buffer[4]);
                    break;
                case schm_data.BitDepth_flag:
                    SchemeFile.get(byte);
                    schm_data.BitDepth = static_cast<bool>(byte);
                    break;
                case schm_data.count_of_objects_flag:
                    schm_data.count_of_objects = GetSomeInt(schm_data.count_of_objects, block_size);
                    break;
                case schm_data.windowsSize_x_flag:
                    schm_data.windowsSize_x = GetSomeInt(schm_data.windowsSize_x, block_size);
                    break;
                case schm_data.windowsSize_y_flag:
                    schm_data.windowsSize_y = GetSomeInt(schm_data.windowsSize_y, block_size);
                    break;
            }
        }
    }
}


void SchemeFileParser::ParseSectionData() {
    if (sections_stack.back().sect_name == "schm")
        ParseSCHM();
    else if (sections_stack.back().sect_name == "cash")
        ParseCASH();
    else if (sections_stack.back().sect_name == "link")
        ParseLINK();
    else if (sections_stack.back().sect_name == "sect")
        ParseSECT();
    else if (sections_stack.back().sect_name == "objs")
        ParseOBJS();
    else if (sections_stack.back().sect_name == "extd")
        ParseEXTD();
    else if (sections_stack.back().sect_name == "sch2")
        ParseSCH2();
    else if (sections_stack.back().sect_name == "font")
        ParseFONT();
    else
        while (SchemeFile.tellg() < sections_stack.back().start_pos + sections_stack.back().sect_size) {
            SchemeFile.get(byte);
        }
}

// Функция чтения блока байтов в схеме
uint32_t SchemeFileParser::GetBlockSize() {
    int8_t bytes_for_blocksize = 0;
    uint32_t block_size = 0;

    // По признаку блока определяем его размер
    if ((static_cast<uint8_t>(byte) & scheme_flags.size_6_bit) == scheme_flags.size_6_bit)
        block_size |= (static_cast<uint8_t>(byte) & 0b00111111);
    else {
        // Если размер блока не уместился в 6 бит, берём его исходя из нужного признака
        switch (static_cast<uint8_t>(byte)) {
            case scheme_flags.size_8_bit:
                bytes_for_blocksize = 1;
                break;
            case scheme_flags.size_16_bit:
                bytes_for_blocksize = 2;
                break;
            case scheme_flags.size_32_bit:
                bytes_for_blocksize = 4;
                break;
        }
        block_size = GetSomeInt(block_size, bytes_for_blocksize);
    }

    return block_size;
}

// Функция чтения информации из блока
void SchemeFileParser::ParseBlockData(const uint32_t& block_size) {

    lae::WriteLog(LogsFile, "BLOCK OPENED ");
    lae::WriteLog(LogsFile, "block size: ");
    lae::WriteLog(LogsFile, block_size, true);

    uint32_t bytes_counter = 0;
    while (bytes_counter < block_size) {
        SchemeFile.get(byte);
        ++bytes_counter;
        lae::WriteLog(LogsFile, byte);
        lae::WriteLog(LogsFile, ' ');
    }
    lae::WriteLog(LogsFile, ' ', true);

    lae::WriteLog(LogsFile, "BLOCK CLOSED", true);

};