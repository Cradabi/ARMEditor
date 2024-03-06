#include "SchemeFileParser.h"


void SchemeFileParser::parseSchm() {

    int32_t reserved{0};

    int32_t name_length{0};

    int32_t DBIP_length{0};

    int32_t DBAlias_length{0};

    double work_scale{0};

    ssp::BGRColor bg_color;
    ssp::BGRColor net_color;
    bool BitDepth{false};

    char* tmp_work_scale = new char[9];

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
                    reserved = getSomeInt(reserved, block_size);
                    lae::WriteLog(LogsFile, "Version: ");
                    lae::WriteLog(LogsFile, reserved, true);
                    reserved = 0;
                    break;
                case schm_data.name_length_flag:
                    name_length = getSomeInt(name_length, block_size);
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
                    DBIP_length = getSomeInt(DBIP_length, block_size);
                    if (DBIP_length == 0)
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
                    DBAlias_length = getSomeInt(DBAlias_length, block_size);
                    if (DBAlias_length == 0)
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
                    reserved = getSomeInt(reserved, block_size);
                    reserved = 0;
                    break;
                case schm_data.reserved_2_flag:
                    reserved = getSomeInt(reserved, block_size);
                    reserved = 0;
                    break;
                case schm_data.work_scale_flag:
                    SchemeFile.read(tmp_work_scale, block_size);
                    work_scale = *reinterpret_cast<double*>(tmp_work_scale);
                    delete[] tmp_work_scale;
                    lae::WriteLog(LogsFile, "work_scale: ");
                    lae::WriteLog(LogsFile, work_scale, true);
                    break;
                case schm_data.bg_color_flag:
                    SchemeFile.read(buffer, block_size);
                    bg_color.blue = static_cast<uint8_t>(buffer[0]);
                    bg_color.green = static_cast<uint8_t>(buffer[1]);
                    bg_color.red = static_cast<uint8_t>(buffer[2]);
                    // schm_data.bg_color.reserved = static_cast<uint8_t>(buffer[4]);
                    lae::WriteLog(LogsFile, "bg_color: ");
                    lae::WriteLog(LogsFile, "blue: ");
                    lae::WriteLog(LogsFile, static_cast<short>(bg_color.blue));
                    lae::WriteLog(LogsFile, " green: ");
                    lae::WriteLog(LogsFile, static_cast<short>(bg_color.green));
                    lae::WriteLog(LogsFile, " red: ");
                    lae::WriteLog(LogsFile, static_cast<short>(bg_color.red), true);
                    break;
                case schm_data.net_color_flag:
                    SchemeFile.read(buffer, block_size);
                    net_color.blue = static_cast<uint8_t>(buffer[0]);
                    net_color.green = static_cast<uint8_t>(buffer[1]);
                    net_color.red = static_cast<uint8_t>(buffer[2]);
                    // schm_data.bg_color.reserved = static_cast<uint8_t>(buffer[4]);
                    lae::WriteLog(LogsFile, "net_color: ");
                    lae::WriteLog(LogsFile, "blue: ");
                    lae::WriteLog(LogsFile, static_cast<short>(net_color.blue));
                    lae::WriteLog(LogsFile, " green: ");
                    lae::WriteLog(LogsFile, static_cast<short>(net_color.green));
                    lae::WriteLog(LogsFile, " red: ");
                    lae::WriteLog(LogsFile, static_cast<short>(net_color.red), true);
                    break;
                case schm_data.BitDepth_flag:
                    SchemeFile.get(byte);
                    BitDepth = static_cast<bool>(byte);
                    lae::WriteLog(LogsFile, "BitDepth: ");
                    lae::WriteLog(LogsFile, BitDepth, true);
                    break;
                case schm_data.count_of_objects_flag:
                    reserved = getSomeInt(reserved, block_size);
                    lae::WriteLog(LogsFile, "count_of_objects: ");
                    lae::WriteLog(LogsFile, reserved, true);
                    reserved = 0;
                    break;
                case schm_data.windowsSize_x_flag:
                    reserved = getSomeInt(reserved, block_size);
                    lae::WriteLog(LogsFile, "windowsSize_x: ");
                    lae::WriteLog(LogsFile, reserved, true);
                    reserved = 0;
                    break;
                case schm_data.windowsSize_y_flag:
                    reserved = getSomeInt(reserved, block_size);
                    lae::WriteLog(LogsFile, "windowsSize_y: ");
                    lae::WriteLog(LogsFile, reserved, true);
                    reserved = 0;
                    break;
            }
        } else if (byte == scheme_flags.section_flag)
            enterSection();
    }
}

void SchemeFileParser::parseCash() {

    int32_t cache_count{0};

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
                case cash_data.cache_count_flag:
                    cache_count = getSomeInt(cache_count, block_size);
                    ++data_counter;

                    lae::WriteLog(LogsFile, "cache_count: ");
                    lae::WriteLog(LogsFile, cache_count, true);
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

    int32_t links_count{0};

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
                    links_count = getSomeInt(links_count, block_size);
                    ++data_counter;

                    lae::WriteLog(LogsFile, "links_count: ");
                    lae::WriteLog(LogsFile, links_count, true);
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

    int32_t next_section_number{0};
    int32_t sect_count{0};

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
                    next_section_number = getSomeInt(next_section_number, block_size);
                    ++data_counter;

                    lae::WriteLog(LogsFile, "next_section_number: ");
                    lae::WriteLog(LogsFile, next_section_number, true);
                    break;
                case sect_data.sect_count_flag:
                    sect_count = getSomeInt(sect_count, block_size);
                    ++data_counter;

                    lae::WriteLog(LogsFile, "sect_count: ");
                    lae::WriteLog(LogsFile, sect_count, true);
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

    int32_t objs_count{0};

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
                    objs_count = getSomeInt(objs_count, block_size);
                    ++data_counter;

                    lae::WriteLog(LogsFile, "objs_count: ");
                    lae::WriteLog(LogsFile, objs_count, true);
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

    int32_t f_work_variable{0};

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
                    f_work_variable = getSomeInt(f_work_variable, block_size);
                    ++data_counter;

                    lae::WriteLog(LogsFile, "f_work_variable: ");
                    lae::WriteLog(LogsFile, f_work_variable, true);
                    break;
            }
        } else if (byte == scheme_flags.section_flag)
            enterSection();
    }
}

void SchemeFileParser::parseSch2() {

    int32_t window_size_X{0};
    int32_t window_size_Y{0};
    bool tmpbool{0};
    int32_t MS_size{0};
    int32_t back_bitmap_info{0};
    int32_t pixels_per_inch_X{0};
    int32_t pixels_per_inch_Y{0};

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
                    window_size_X = getSomeInt(window_size_X, block_size);
                    lae::WriteLog(LogsFile, "window_size_X: ");
                    lae::WriteLog(LogsFile, window_size_X, true);
                    break;
                case sch2_data.window_size_Y_flag:
                    window_size_Y = getSomeInt(window_size_Y, block_size);
                    lae::WriteLog(LogsFile, "window_size_Y: ");
                    lae::WriteLog(LogsFile, window_size_Y, true);
                    break;
                case sch2_data.tmpbool_flag:
                    SchemeFile.get(byte);
                    tmpbool = static_cast<bool>(byte);
                    if (tmpbool == false) {
                        data_counter += 2;
                    }
                    break;
                case sch2_data.MS_size_flag:
                    MS_size = getSomeInt(MS_size, block_size);
                    lae::WriteLog(LogsFile, "MS_size: ");
                    lae::WriteLog(LogsFile, MS_size, true);
                    break;
                case sch2_data.back_bitmap_info_flag:
                    back_bitmap_info = getSomeInt(back_bitmap_info, block_size);
                    lae::WriteLog(LogsFile, "back_bitmap_info: ");
                    lae::WriteLog(LogsFile, back_bitmap_info, true);
                    break;
                case sch2_data.pixels_per_inch_X_flag:
                    pixels_per_inch_X = getSomeInt(pixels_per_inch_X, block_size);
                    lae::WriteLog(LogsFile, "pixels_per_inch_X: ");
                    lae::WriteLog(LogsFile, pixels_per_inch_X, true);
                    break;
                case sch2_data.pixels_per_inch_Y_flag:
                    pixels_per_inch_Y = getSomeInt(pixels_per_inch_Y, block_size);
                    lae::WriteLog(LogsFile, "pixels_per_inch_Y: ");
                    lae::WriteLog(LogsFile, pixels_per_inch_Y, true);
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

void SchemeFileParser::parseObject() {

    uint8_t data_counter = 0;
    uint32_t block_size;

    if (sections_stack.back().sect_name != "1")
        parseUnknown();
    else {
        SchemeFile.get(byte);
        // Получаем размер блока
        block_size = getBlockSize();
        printBlockData(block_size);

        SchemeFile.get(byte);
        // Получаем размер блока
        block_size = getBlockSize();
        printBlockData(block_size);

        SchemeFile.get(byte);
        // Получаем размер блока
        block_size = getBlockSize();

        SchemeFile.read(buffer, block_size);

        int id_pos = findSequence(buffer, sections_stack.back().parrent_sect->sect_name);
        int dots_count = getSomeInt(0, 4, true, id_pos + 8);
        uint8_t PrType = static_cast<uint8_t>(buffer[id_pos+12+dots_count*8]);

        switch (PrType) {
            case objects_types.ptEllipse:
                lae::WriteLog(LogsFile, "\nptEllipse\n", true);
                objectParser.parseEllips(buffer, *scheme_params, block_size, id_pos);
                break;
            case objects_types.ptRectangle:
                lae::WriteLog(LogsFile, "\nptRectangle\n", true);
                objectParser.parseRectangle(buffer, *scheme_params, block_size, id_pos);
                break;
            case objects_types.ptGoPoint:
                lae::WriteLog(LogsFile, "\nptGoPoint\n", true);
                objectParser.parseGoPoint(buffer, *scheme_params, block_size, id_pos);
                break;
            case objects_types.ptGoBtn:
                lae::WriteLog(LogsFile, "\nptGoBtn\n", true);
                objectParser.parseGoBtn(buffer, *scheme_params, block_size, id_pos);
                break;
            case objects_types.ptText:
                lae::WriteLog(LogsFile, "\nptText\n", true);
                objectParser.parseText(buffer, *scheme_params, block_size, id_pos);
                break;
            case objects_types.ptTeleupr:
                lae::WriteLog(LogsFile, "\nptTeleupr\n", true);
                objectParser.parseTelecontrol(buffer, *scheme_params, block_size, id_pos);
                break;
            case objects_types.ptTeleizm:
                lae::WriteLog(LogsFile, "\nptTeleizm\n", true);
                objectParser.parseTelemeasure(buffer, *scheme_params, block_size, id_pos);
                break;
            case objects_types.ptSignal:
                lae::WriteLog(LogsFile, "\nptSignal\n", true);
                objectParser.parseSignal(buffer, *scheme_params, block_size, id_pos);
                break;
            case objects_types.ptLine:
                lae::WriteLog(LogsFile, "\nptLine\n", true);
                objectParser.parseLine(buffer, *scheme_params, block_size, id_pos);
                break;
            case objects_types.ptPolygon:
                lae::WriteLog(LogsFile, "\nptPolygon\n", true);
                objectParser.parsePolygon(buffer, *scheme_params, block_size, id_pos);
                break;
            case objects_types.ptDuga:
                lae::WriteLog(LogsFile, "\nptDuga\n", true);
                objectParser.parseArc(buffer, *scheme_params, block_size, id_pos);
                break;
            case objects_types.ptPicture:
                lae::WriteLog(LogsFile, "\nptPicture\n", true);
                objectParser.parsePicture(buffer, *scheme_params, block_size, id_pos);
                break;

            default:
                lae::WriteLog(LogsFile, "Unknown object", true);
                lae::WriteLog(LogsFile, "BLOCK OPENED ");
                lae::WriteLog(LogsFile, "block size: ");
                lae::WriteLog(LogsFile, block_size);
                lae::WriteLog(LogsFile, ' ');

                std::bitset<8> print_byte;

                uint32_t bytes_counter = 0;
                while (bytes_counter < block_size) {
                    print_byte = buffer[bytes_counter];
                    ++bytes_counter;
                    lae::WriteLog(LogsFile, print_byte);
                    if (bytes_counter % 4 == 0) {
                        lae::WriteLog(LogsFile, "\n");
                    } else {
                        lae::WriteLog(LogsFile, ' ');
                    }

                }

                lae::WriteLog(LogsFile, "BLOCK CLOSED", true);

        }


    }

}


void SchemeFileParser::parseSectionData() {
    if (sections_stack.back().sect_name == "schm")
        parseSchm();
    else if (sections_stack.back().sect_name == "cash")
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
        parseUnknown();     // TODO Заменить на ParseFONT
    else if (sections_stack.size() == 4 and sections_stack[1].sect_name == "objs") {
        parseObject();
    } else
        parseUnknown();

}

// Функция чтения блока байтов в схеме
uint32_t SchemeFileParser::getBlockSize() {
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
        block_size = getSomeInt(block_size, bytes_for_blocksize);
    }

    return block_size;
}

// Функция чтения информации из блока
void SchemeFileParser::printBlockData(const uint32_t& block_size) {

    lae::WriteLog(LogsFile, "BLOCK OPENED ");
    lae::WriteLog(LogsFile, "block size: ");
    lae::WriteLog(LogsFile, block_size);
    lae::WriteLog(LogsFile, ' ');

    std::bitset<8> print_byte;

    uint32_t bytes_counter = 0;
    while (bytes_counter < block_size) {
        SchemeFile.get(byte);
        print_byte = byte;
        ++bytes_counter;
        lae::WriteLog(LogsFile, print_byte);
        if (bytes_counter % 4 == 0) {
            lae::WriteLog(LogsFile, "\n");
        } else {
            lae::WriteLog(LogsFile, ' ');
        }

    }

    lae::WriteLog(LogsFile, "BLOCK CLOSED", true);

};