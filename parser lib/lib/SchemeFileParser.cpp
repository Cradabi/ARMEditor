#include "SchemeFileParser.h"

void SchemeFileParser::parseSchm() {

    uint32_t tmp_value;

    uint8_t data_counter = 0;
    uint32_t block_size;

    // Пока не дошли до конца секции, считываем данные
    while (SchemeFile.tellg() < sections_stack.back().start_pos + sections_stack.back().sect_size) {
        SchemeFile.get(byte);

        // Если нашли флаг блока, открываем его
        if ((static_cast<uint8_t>(byte) & scheme_flags.block_flag) == scheme_flags.block_flag) {
            // Получаем размер блока
            block_size = getBlockSize();
            ++data_counter;

            switch (data_counter) {
                case schm_data.version_flag:
                    tmp_value = getSomeInt(tmp_value, block_size);
                    lae::WriteLog(LogsFile, "Version: ");
                    lae::WriteLog(LogsFile, tmp_value, true);
                    break;
                case schm_data.name_length_flag:
                    getSomeInt(0, block_size);
                    break;
                case schm_data.scheme_name_flag:
                    for (uint32_t digit = 0; digit < block_size; ++digit) {
                        SchemeFile.get(byte);
                        scheme_params->name_scheme += byte;
                    }
                    lae::WriteLog(LogsFile, "Name: ");
                    lae::WriteLog(LogsFile, scheme_params->name_scheme, true);
                    break;
                case schm_data.DBIP_length_flag:
                    tmp_value = getSomeInt(tmp_value, block_size);
                    if (tmp_value == 0)
                        ++data_counter;
                    break;
                case schm_data.DBIP_flag:
                    for (uint32_t digit = 0; digit < block_size; ++digit) {
                        SchemeFile.get(byte);
                        scheme_params->name_bd += byte;
                    }
                    lae::WriteLog(LogsFile, "DBIP: ");
                    lae::WriteLog(LogsFile, scheme_params->name_bd, true);
                    break;
                case schm_data.DBAlias_length_flag:
                    tmp_value = getSomeInt(tmp_value, block_size);
                    if (tmp_value == 0)
                        ++data_counter;
                    break;
                case schm_data.DBAlias_flag:
                    for (uint32_t digit = 0; digit < block_size; ++digit) {
                        SchemeFile.get(byte);
                        scheme_params->server += byte;
                    }
                    lae::WriteLog(LogsFile, "DBAlias: ");
                    lae::WriteLog(LogsFile, scheme_params->server, true);
                    break;
                case schm_data.width_flag:
                    scheme_params->width = getSomeInt(scheme_params->width, block_size);
                    lae::WriteLog(LogsFile, "width: ");
                    lae::WriteLog(LogsFile, scheme_params->width, true);
                    break;
                case schm_data.height_flag:
                    scheme_params->height = getSomeInt(scheme_params->height, block_size);
                    lae::WriteLog(LogsFile, "height: ");
                    lae::WriteLog(LogsFile, scheme_params->height, true);
                    break;
                case schm_data.reserved_1_flag:
                    getSomeInt(0, block_size);
                    break;
                case schm_data.reserved_2_flag:
                    getSomeInt(0, block_size);
                    break;
                case schm_data.work_scale_flag:
                    SchemeFile.read(buffer, block_size);
                    lae::WriteLog(LogsFile, "work_scale: ");
                    lae::WriteLog(LogsFile, NULL, true);
                    break;
                case schm_data.bg_color_flag:
                    SchemeFile.read(buffer, block_size);
                    scheme_params->bgColor.blue = static_cast<uint8_t>(buffer[0]);
                    scheme_params->bgColor.green = static_cast<uint8_t>(buffer[1]);
                    scheme_params->bgColor.red = static_cast<uint8_t>(buffer[2]);
                    lae::WriteLog(LogsFile, "bg_color: ");
                    lae::WriteLog(LogsFile, "b: ");
                    lae::WriteLog(LogsFile, (int)scheme_params->bgColor.blue);
                    lae::WriteLog(LogsFile, " g: ");
                    lae::WriteLog(LogsFile, (int)scheme_params->bgColor.green);
                    lae::WriteLog(LogsFile, " r: ");
                    lae::WriteLog(LogsFile, (int)scheme_params->bgColor.red, true);
                    break;
                case schm_data.net_color_flag:
                    SchemeFile.read(buffer, block_size);
                    scheme_params->setColor.blue = static_cast<uint8_t>(buffer[0]);
                    scheme_params->setColor.green = static_cast<uint8_t>(buffer[1]);
                    scheme_params->setColor.red = static_cast<uint8_t>(buffer[2]);
                    lae::WriteLog(LogsFile, "setColor: ");
                    lae::WriteLog(LogsFile, "b: ");
                    lae::WriteLog(LogsFile, (int)scheme_params->setColor.blue);
                    lae::WriteLog(LogsFile, " g: ");
                    lae::WriteLog(LogsFile, (int)scheme_params->setColor.green);
                    lae::WriteLog(LogsFile, " r: ");
                    lae::WriteLog(LogsFile, (int)scheme_params->setColor.red, true);
                    break;
                case schm_data.BitDepth_flag:
                    SchemeFile.get(byte);
                    lae::WriteLog(LogsFile, "BitDepth: ");
                    lae::WriteLog(LogsFile, NULL, true);
                    break;
                case schm_data.count_of_objects_flag:
                    objects_amount = getSomeInt(objects_amount, block_size);
                    lae::WriteLog(LogsFile, "count_of_objects: ");
                    lae::WriteLog(LogsFile, objects_amount, true);
                    break;
                case schm_data.windowsSize_x_flag:
                    getSomeInt(0, block_size);
                    lae::WriteLog(LogsFile, "windowsSize_x: ");
                    lae::WriteLog(LogsFile, NULL, true);
                    break;
                case schm_data.windowsSize_y_flag:
                    getSomeInt(0, block_size);
                    lae::WriteLog(LogsFile, "windowsSize_y: ");
                    lae::WriteLog(LogsFile, NULL, true);
                    break;
            }
        } else if (byte == scheme_flags.section_flag)
            enterSection();
    }
}

void SchemeFileParser::parseCash() {

    uint32_t tmp_value;

    uint8_t data_counter = 1;
    uint32_t block_size;

    // Пока не дошли до конца секции, считываем данные
    while (SchemeFile.tellg() < sections_stack.back().start_pos + sections_stack.back().sect_size) {
        SchemeFile.get(byte);

        // Если нашли флаг блока, открываем его
        if ((static_cast<uint8_t>(byte) & scheme_flags.block_flag) == scheme_flags.block_flag) {
            // Получаем размер блока
            block_size = getBlockSize();

            switch (data_counter) {
                case cach_data.cache_count_flag:
                    tmp_value = getSomeInt(tmp_value, block_size);
                    ++data_counter;

                    lae::WriteLog(LogsFile, "cache_count: ");
                    lae::WriteLog(LogsFile, tmp_value, true);
                    break;
                default:
                    printBlockData(block_size);
                    break;
            }
        } else if (byte == scheme_flags.section_flag)
            enterSection();
    }
}

void SchemeFileParser::parseLink() {

    uint32_t tmp_value;

    uint8_t data_counter = 1;
    uint32_t block_size;

    // Пока не дошли до конца секции, считываем данные
    while (SchemeFile.tellg() < sections_stack.back().start_pos + sections_stack.back().sect_size) {
        SchemeFile.get(byte);

        // Если нашли флаг блока, открываем его
        if ((static_cast<uint8_t>(byte) & scheme_flags.block_flag) == scheme_flags.block_flag) {
            // Получаем размер блока
            block_size = getBlockSize();

            switch (data_counter) {
                case link_data.links_count_flag:
                    tmp_value = getSomeInt(tmp_value, block_size);
                    ++data_counter;

                    lae::WriteLog(LogsFile, "links_count: ");
                    lae::WriteLog(LogsFile, tmp_value, true);
                    break;
                default:
                    printBlockData(block_size);
                    break;
            }
        } else if (byte == scheme_flags.section_flag)
            enterSection();
    }
}

void SchemeFileParser::parseSect() {

    uint32_t tmp_value;

    uint8_t data_counter = 1;
    uint32_t block_size;

    // Пока не дошли до конца секции, считываем данные
    while (SchemeFile.tellg() < sections_stack.back().start_pos + sections_stack.back().sect_size) {
        SchemeFile.get(byte);

        // Если нашли флаг блока, открываем его
        if ((static_cast<uint8_t>(byte) & scheme_flags.block_flag) == scheme_flags.block_flag) {
            // Получаем размер блока
            block_size = getBlockSize();

            switch (data_counter) {
                case sect_data.next_section_number_flag:
                    tmp_value = getSomeInt(tmp_value, block_size);
                    ++data_counter;

                    lae::WriteLog(LogsFile, "next_section_number: ");
                    lae::WriteLog(LogsFile, tmp_value, true);
                    break;
                case sect_data.sect_count_flag:
                    tmp_value = getSomeInt(tmp_value, block_size);
                    ++data_counter;

                    lae::WriteLog(LogsFile, "sect_count: ");
                    lae::WriteLog(LogsFile, tmp_value, true);
                    break;
                default:
                    printBlockData(block_size);
                    break;
            }
        } else if (byte == scheme_flags.section_flag)
            enterSection();
    }
}

void SchemeFileParser::parseObjs() {

    uint32_t tmp_value;

    uint8_t data_counter = 1;
    uint32_t block_size;

    // Пока не дошли до конца секции, считываем данные
    while (SchemeFile.tellg() < sections_stack.back().start_pos + sections_stack.back().sect_size) {
        SchemeFile.get(byte);

        // Если нашли флаг блока, открываем его
        if ((static_cast<uint8_t>(byte) & scheme_flags.block_flag) == scheme_flags.block_flag) {
            // Получаем размер блока
            block_size = getBlockSize();

            switch (data_counter) {
                case objs_data.objs_count_flag:
                    tmp_value = getSomeInt(tmp_value, block_size);
                    ++data_counter;

                    lae::WriteLog(LogsFile, "objs_count: ");
                    lae::WriteLog(LogsFile, tmp_value, true);
                    break;
                default:
                    printBlockData(block_size);
                    break;
            }
        } else if (byte == scheme_flags.section_flag)
            enterSection();
    }
}

void SchemeFileParser::parseExtd() {

    uint32_t tmp_value;

    uint8_t data_counter = 1;
    uint32_t block_size;

    // Пока не дошли до конца секции, считываем данные
    while (SchemeFile.tellg() < sections_stack.back().start_pos + sections_stack.back().sect_size) {
        SchemeFile.get(byte);

        // Если нашли флаг блока, открываем его
        if ((static_cast<uint8_t>(byte) & scheme_flags.block_flag) == scheme_flags.block_flag) {
            // Получаем размер блока
            block_size = getBlockSize();

            switch (data_counter) {
                case extd_data.f_work_variable_flag:
                    getSomeInt(0, block_size);
                    ++data_counter;

                    lae::WriteLog(LogsFile, "f_work_variable: ");
                    lae::WriteLog(LogsFile, NULL, true);
                    break;
            }
        } else if (byte == scheme_flags.section_flag)
            enterSection();
    }
}

void SchemeFileParser::parseSch2() {

    uint32_t tmp_value;

    uint8_t data_counter = 0;
    uint32_t block_size;

    // Пока не дошли до конца секции, считываем данные
    while (SchemeFile.tellg() < sections_stack.back().start_pos + sections_stack.back().sect_size) {
        SchemeFile.get(byte);
        // Если нашли флаг блока, открываем его
        if ((static_cast<uint8_t>(byte) & scheme_flags.block_flag) == scheme_flags.block_flag) {
            // Получаем размер блока
            block_size = getBlockSize();
            ++data_counter;

            switch (data_counter) {
                case sch2_data.window_size_X_flag:
                    getSomeInt(0, block_size);
                    lae::WriteLog(LogsFile, "window_size_X: ");
                    lae::WriteLog(LogsFile, NULL, true);
                    break;
                case sch2_data.window_size_Y_flag:
                    getSomeInt(0, block_size);
                    lae::WriteLog(LogsFile, "window_size_Y: ");
                    lae::WriteLog(LogsFile, NULL, true);
                    break;
                case sch2_data.tmpbool_flag:
                    SchemeFile.get(byte);
                    tmp_value = byte;
                    if (tmp_value == 0) {
                        data_counter += 2;
                    }
                    break;
                case sch2_data.MS_size_flag:
                    getSomeInt(0, block_size);
                    lae::WriteLog(LogsFile, "MS_size: ");
                    lae::WriteLog(LogsFile, NULL, true);
                    break;
                case sch2_data.back_bitmap_info_flag:
                    getSomeInt(0, block_size);
                    lae::WriteLog(LogsFile, "back_bitmap_info: ");
                    lae::WriteLog(LogsFile, NULL, true);
                    break;
                case sch2_data.pixels_per_inch_X_flag:
                    getSomeInt(0, block_size);
                    lae::WriteLog(LogsFile, "pixels_per_inch_X: ");
                    lae::WriteLog(LogsFile, NULL, true);
                    break;
                case sch2_data.pixels_per_inch_Y_flag:
                    getSomeInt(0, block_size);
                    lae::WriteLog(LogsFile, "pixels_per_inch_Y: ");
                    lae::WriteLog(LogsFile, NULL, true);
                    break;

            }
        } else if (byte == scheme_flags.section_flag)
            enterSection();
    }
}

void SchemeFileParser::parseFont() {
    ;
}


void SchemeFileParser::parseUnknown() {
    // Пока не дошли до конца секции, считываем данные
    while (SchemeFile.tellg() < sections_stack.back().start_pos + sections_stack.back().sect_size) {
        SchemeFile.get(byte);

        uint32_t block_size;
        // Если нашли флаг блока, открываем его
        if ((static_cast<uint8_t>(byte) & scheme_flags.block_flag) == scheme_flags.block_flag) {
            // Получаем размер блока
            block_size = getBlockSize();

            printBlockData(block_size);

        } else if (byte == scheme_flags.section_flag)
            enterSection();
    }
}

void SchemeFileParser::parseCashObject() {

    uint32_t block_size;

    if (sections_stack.back().sect_name != "1")
        parseUnknown();
    else {
        SchemeFile.get(byte);
        // Получаем размер блока
        block_size = getBlockSize();
        uint32_t cache_size;
        cache_size = getSomeInt(cache_size, types_sizes._32bits);

        SchemeFile.get(byte);
        // Получаем размер блока
        block_size = getBlockSize();

        int32_t actual_cursor_pos = SchemeFile.tellg();

        SchemeFile.close();
        LogsFile.close();

        int32_t cache_index = std::stoi(sections_stack.back().parrent_sect->sect_name);

        objectParser.parse(actual_cursor_pos, schemefile_path, logsfile_path, cache_index, true, cache_size);

        SchemeFile.open(schemefile_path, std::ios_base::binary);

        SchemeFile.clear();
        SchemeFile.seekg(actual_cursor_pos + block_size);

        LogsFile.open(logsfile_path, std::ios_base::app);
    }
}

void SchemeFileParser::parseObject() {

    uint32_t block_size;

    if (sections_stack.back().sect_name != "1")
        parseUnknown();
    else {
        SchemeFile.get(byte);
        // Получаем размер блока
        block_size = getBlockSize();
        int32_t lib_index = 0;

        if(block_size!=1){
            SchemeFile.seekg(sections_stack.back().start_pos+sections_stack.back().sect_size);
            return;
        }
        SchemeFile.get(byte);
        bool tmp_bool = static_cast<bool>(byte);

        if (tmp_bool) {
            SchemeFile.get(byte);
            // Получаем размер блока
            block_size = getBlockSize();
            lib_index = getSomeInt(lib_index, types_sizes._32bits);
        }

        SchemeFile.get(byte);
        // Получаем размер блока
        block_size = getBlockSize();




        printBlockData(block_size);

        SchemeFile.get(byte);
        // Получаем размер блока
        block_size = getBlockSize();

        uint32_t actual_cursor_pos = SchemeFile.tellg();

        SchemeFile.close();
        LogsFile.close();

        objectParser.parse(actual_cursor_pos, schemefile_path, logsfile_path, lib_index);

        SchemeFile.open(schemefile_path, std::ios_base::binary);

        SchemeFile.clear();
        SchemeFile.seekg(actual_cursor_pos + block_size);

        LogsFile.open(logsfile_path, std::ios_base::app);
    }

}


void SchemeFileParser::parseSectionData() {
    if (sections_stack.back().sect_name == "schm")
        parseSchm();
    else if (sections_stack.back().sect_name == "cach")
        parseCash();
    else if (sections_stack.back().sect_name == "link")
        parseLink();
    else if (sections_stack.back().sect_name == "sect")
        parseSect();
    else if (sections_stack.back().sect_name == "objs")
        parseObjs();
    else if (sections_stack.back().sect_name == "extd")
        parseExtd();
    else if (sections_stack.back().sect_name == "sch2")
        parseSch2();
    else if (sections_stack.back().sect_name == "font")
        parseUnknown();
    else if (sections_stack.size() == 4 and sections_stack[1].sect_name == "objs")
        parseObject();
    else if (sections_stack.size() == 4 and sections_stack[1].sect_name == "cach") {
        parseCashObject();
    } else
        parseUnknown();
}

// Функция чтения блока байтов в схеме
uint32_t SchemeFileParser::getBlockSize() {


    int8_t bytes_for_blocksize = 0;
    uint32_t block_size = 0;

    // По признаку блока определяем его размер
    if ((static_cast<uint8_t>(byte) & scheme_flags.size_6_bit) == scheme_flags.size_6_bit){
        block_size |= (static_cast<uint8_t>(byte) & 0b00111111);
    }
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
            default:
                bytes_for_blocksize = 4;
                break;
        }
        block_size = getSomeInt(block_size, bytes_for_blocksize);
    }

    return block_size;
}

// Функция чтения информации из блока
void SchemeFileParser::printBlockData(const uint32_t block_size) {

    lae::WriteLog(LogsFile, "BLOCK OPENED ");
    lae::WriteLog(LogsFile, "block size: ");
    lae::WriteLog(LogsFile, block_size, true);

    std::bitset<8> print_byte;
    uint32_t bytes_counter = 0;

    while (bytes_counter < block_size) {
        SchemeFile.get(byte);
        ++bytes_counter;

        print_byte = byte;
        lae::WriteLog(LogsFile, print_byte);

        if (bytes_counter % 4 == 0) {
            lae::WriteLog(LogsFile, "\n");
        } else {
            lae::WriteLog(LogsFile, ' ');
        }

    }


    lae::WriteLog(LogsFile, "BLOCK CLOSED", true);

};