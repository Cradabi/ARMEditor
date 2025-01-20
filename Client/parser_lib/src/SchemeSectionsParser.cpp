#include "SchemeSectionsParser.h"

bool SchemeSectionsParser::parse() {

    // lae::printLog("Парсер секций: начал работу", true);

    qDebug() << "Парсер секций: начал работу";

    while (scheme_file_.get(byte_)) {
        // Если дошли до границ открытой секции, закрываем её
        while (!sections_stack_.empty() &&
               (scheme_file_.tellg() >= sections_stack_.back().start_pos + sections_stack_.back().sect_size)) {
            closeSection();
        }

        // Если обнаружили флаг секции, открываем её
        if (byte_ == scheme_flags_.section_flag) {
            if (!enterSection()) {
                return false;
            }
        }
    }

    // Если остались незакрытые секции, закрываем их
    while (!sections_stack_.empty()) {
        closeSection();
    }

    //lae::printLog("Парсер секций: отработал", true);

    qDebug() << "Парсер секций: отработал";

    return true;
}


void SchemeSectionsParser::parseSchm() {

    uint32_t tmp_value;

    uint8_t data_counter = 0;
    uint32_t block_size;

    // Пока не дошли до конца секции, считываем данные
    while (scheme_file_.tellg() < sections_stack_.back().start_pos + sections_stack_.back().sect_size) {
        scheme_file_.get(byte_);

        // Если нашли флаг блока, открываем его
        if ((static_cast<uint8_t>(byte_) & scheme_flags_.block_flag) == scheme_flags_.block_flag) {
            // Получаем размер блока
            block_size = getBlockSize();
            ++data_counter;

            switch (data_counter) {
                case schm_data_.version_flag:
                    getSomeInt(scheme_file_, tmp_value, block_size);
                    lae::writeLog(logs_file_, "Version: ");
                    lae::writeLog(logs_file_, tmp_value, true);
                    break;
                case schm_data_.name_length_flag:
                    getSomeInt(scheme_file_, tmp_value, block_size);
                    break;
                case schm_data_.scheme_name_flag:
                    for (uint32_t digit = 0; digit < block_size; ++digit) {
                        scheme_file_.get(byte_);
                        scheme_params_->name_scheme += byte_;
                    }
                    lae::writeLog(logs_file_, "Name: ");
                    lae::writeLog(logs_file_, scheme_params_->name_scheme, true);
                    break;
                case schm_data_.DBIP_length_flag:
                    getSomeInt(scheme_file_, tmp_value, block_size);
                    if (tmp_value == 0)
                        ++data_counter;
                    break;
                case schm_data_.DBIP_flag:
                    for (uint32_t digit = 0; digit < block_size; ++digit) {
                        scheme_file_.get(byte_);
                        scheme_params_->name_bd += byte_;
                    }
                    lae::writeLog(logs_file_, "DBIP: ");
                    lae::writeLog(logs_file_, scheme_params_->name_bd, true);
                    break;
                case schm_data_.DBAlias_length_flag:
                    getSomeInt(scheme_file_, tmp_value, block_size);
                    if (tmp_value == 0)
                        ++data_counter;
                    break;
                case schm_data_.DBAlias_flag:
                    for (uint32_t digit = 0; digit < block_size; ++digit) {
                        scheme_file_.get(byte_);
                        scheme_params_->server += byte_;
                    }
                    lae::writeLog(logs_file_, "DBAlias: ");
                    lae::writeLog(logs_file_, scheme_params_->server, true);
                    break;
                case schm_data_.width_flag:
                    getSomeInt(scheme_file_, scheme_params_->width, block_size);
                    lae::writeLog(logs_file_, "width: ");
                    lae::writeLog(logs_file_, scheme_params_->width, true);
                    break;
                case schm_data_.height_flag:
                    getSomeInt(scheme_file_, scheme_params_->height, block_size);
                    lae::writeLog(logs_file_, "height: ");
                    lae::writeLog(logs_file_, scheme_params_->height, true);
                    break;
                case schm_data_.reserved_1_flag:
                    getSomeInt(scheme_file_, tmp_value, block_size);
                    break;
                case schm_data_.reserved_2_flag:
                    getSomeInt(scheme_file_, tmp_value, block_size);
                    break;
                case schm_data_.work_scale_flag:
                    scheme_file_.read(buffer_, block_size);
                    lae::writeLog(logs_file_, "work_scale: ");
                    lae::writeLog(logs_file_, NULL, true);
                    break;
                case schm_data_.bg_color_flag:
                    scheme_file_.read(buffer_, block_size);
                    scheme_params_->bgColor.blue = static_cast<uint8_t>(buffer_[0]);
                    scheme_params_->bgColor.green = static_cast<uint8_t>(buffer_[1]);
                    scheme_params_->bgColor.red = static_cast<uint8_t>(buffer_[2]);
                    lae::writeLog(logs_file_, "bg_color: ");
                    lae::writeLog(logs_file_, "b: ");
                    lae::writeLog(logs_file_, (int) scheme_params_->bgColor.blue);
                    lae::writeLog(logs_file_, " g: ");
                    lae::writeLog(logs_file_, (int) scheme_params_->bgColor.green);
                    lae::writeLog(logs_file_, " r: ");
                    lae::writeLog(logs_file_, (int) scheme_params_->bgColor.red, true);
                    break;
                case schm_data_.net_color_flag:
                    scheme_file_.read(buffer_, block_size);
                    scheme_params_->setColor.blue = static_cast<uint8_t>(buffer_[0]);
                    scheme_params_->setColor.green = static_cast<uint8_t>(buffer_[1]);
                    scheme_params_->setColor.red = static_cast<uint8_t>(buffer_[2]);
                    lae::writeLog(logs_file_, "setColor: ");
                    lae::writeLog(logs_file_, "b: ");
                    lae::writeLog(logs_file_, (int) scheme_params_->setColor.blue);
                    lae::writeLog(logs_file_, " g: ");
                    lae::writeLog(logs_file_, (int) scheme_params_->setColor.green);
                    lae::writeLog(logs_file_, " r: ");
                    lae::writeLog(logs_file_, (int) scheme_params_->setColor.red, true);
                    break;
                case schm_data_.BitDepth_flag:
                    scheme_file_.get(byte_);
                    lae::writeLog(logs_file_, "BitDepth: ");
                    lae::writeLog(logs_file_, byte_, true);
                    break;
                case schm_data_.count_of_objects_flag:
                    getSomeInt(scheme_file_, objects_amount_, block_size);
                    lae::writeLog(logs_file_, "count_of_objects: ");
                    lae::writeLog(logs_file_, objects_amount_, true);
                    break;
                case schm_data_.windowsSize_x_flag:
                    getSomeInt(scheme_file_, tmp_value, block_size);
                    lae::writeLog(logs_file_, "windowsSize_x: ");
                    lae::writeLog(logs_file_, tmp_value, true);
                    break;
                case schm_data_.windowsSize_y_flag:
                    getSomeInt(scheme_file_, tmp_value, block_size);
                    lae::writeLog(logs_file_, "windowsSize_y: ");
                    lae::writeLog(logs_file_, tmp_value, true);
                    break;
            }
        } else if (byte_ == scheme_flags_.section_flag)
            enterSection();
    }
}

void SchemeSectionsParser::parseCash() {

    uint32_t tmp_value;

    uint8_t data_counter = 1;
    uint32_t block_size;

    // Пока не дошли до конца секции, считываем данные
    while (scheme_file_.tellg() < sections_stack_.back().start_pos + sections_stack_.back().sect_size) {
        scheme_file_.get(byte_);

        // Если нашли флаг блока, открываем его
        if ((static_cast<uint8_t>(byte_) & scheme_flags_.block_flag) == scheme_flags_.block_flag) {
            // Получаем размер блока
            block_size = getBlockSize();

            switch (data_counter) {
                case cach_data_.cache_count_flag:
                    getSomeInt(scheme_file_, tmp_value, block_size);
                    ++data_counter;

                    lae::writeLog(logs_file_, "cache_count: ");
                    lae::writeLog(logs_file_, tmp_value, true);
                    break;
                default:
                    printBlockData(block_size);
                    break;
            }
        } else if (byte_ == scheme_flags_.section_flag)
            enterSection();
    }
}

void SchemeSectionsParser::parseLink() {

    uint32_t tmp_value;

    uint8_t data_counter = 1;
    uint32_t block_size;

    // Пока не дошли до конца секции, считываем данные
    while (scheme_file_.tellg() < sections_stack_.back().start_pos + sections_stack_.back().sect_size) {
        scheme_file_.get(byte_);

        // Если нашли флаг блока, открываем его
        if ((static_cast<uint8_t>(byte_) & scheme_flags_.block_flag) == scheme_flags_.block_flag) {
            // Получаем размер блока
            block_size = getBlockSize();

            switch (data_counter) {
                case link_data_.links_count_flag:
                    getSomeInt(scheme_file_, tmp_value, block_size);
                    ++data_counter;

                    lae::writeLog(logs_file_, "links_count: ");
                    lae::writeLog(logs_file_, tmp_value, true);
                    break;
                default:
                    printBlockData(block_size);
                    break;
            }
        } else if (byte_ == scheme_flags_.section_flag)
            enterSection();
    }
}

void SchemeSectionsParser::parseSect() {

    uint32_t tmp_value;

    uint8_t data_counter = 1;
    uint32_t block_size;

    // Пока не дошли до конца секции, считываем данные
    while (scheme_file_.tellg() < sections_stack_.back().start_pos + sections_stack_.back().sect_size) {
        scheme_file_.get(byte_);

        // Если нашли флаг блока, открываем его
        if ((static_cast<uint8_t>(byte_) & scheme_flags_.block_flag) == scheme_flags_.block_flag) {
            // Получаем размер блока
            block_size = getBlockSize();

            switch (data_counter) {
                case sect_data_.next_section_number_flag:
                    getSomeInt(scheme_file_, tmp_value, block_size);
                    ++data_counter;

                    lae::writeLog(logs_file_, "next_section_number: ");
                    lae::writeLog(logs_file_, tmp_value, true);
                    break;
                case sect_data_.sect_count_flag:
                    getSomeInt(scheme_file_, tmp_value, block_size);
                    ++data_counter;

                    lae::writeLog(logs_file_, "sect_count: ");
                    lae::writeLog(logs_file_, tmp_value, true);
                    break;
                default:
                    printBlockData(block_size);
                    break;
            }
        } else if (byte_ == scheme_flags_.section_flag)
            enterSection();
    }
}

void SchemeSectionsParser::parseObjs() {

    uint32_t tmp_value;

    uint8_t data_counter = 1;
    uint32_t block_size;

    // Пока не дошли до конца секции, считываем данные
    while (scheme_file_.tellg() < sections_stack_.back().start_pos + sections_stack_.back().sect_size) {
        scheme_file_.get(byte_);

        // Если нашли флаг блока, открываем его
        if ((static_cast<uint8_t>(byte_) & scheme_flags_.block_flag) == scheme_flags_.block_flag) {
            // Получаем размер блока
            block_size = getBlockSize();

            switch (data_counter) {
                case objs_data_.objs_count_flag:
                     getSomeInt(scheme_file_, tmp_value, block_size);
                    ++data_counter;

                    lae::writeLog(logs_file_, "objs_count: ");
                    lae::writeLog(logs_file_, tmp_value, true);
                    break;
                default:
                    printBlockData(block_size);
                    break;
            }
        } else if (byte_ == scheme_flags_.section_flag)
            enterSection();
    }
}

void SchemeSectionsParser::parseExtd() {

    uint32_t tmp_value;

    uint8_t data_counter = 1;
    uint32_t block_size;

    // Пока не дошли до конца секции, считываем данные
    while (scheme_file_.tellg() < sections_stack_.back().start_pos + sections_stack_.back().sect_size) {
        scheme_file_.get(byte_);

        // Если нашли флаг блока, открываем его
        if ((static_cast<uint8_t>(byte_) & scheme_flags_.block_flag) == scheme_flags_.block_flag) {
            // Получаем размер блока
            block_size = getBlockSize();

            switch (data_counter) {
                case extd_data_.f_work_variable_flag:
                    getSomeInt(scheme_file_, tmp_value, block_size);
                    ++data_counter;

                    lae::writeLog(logs_file_, "f_work_variable: ");
                    lae::writeLog(logs_file_, tmp_value, true);
                    break;
            }
        } else if (byte_ == scheme_flags_.section_flag)
            enterSection();
    }
}

void SchemeSectionsParser::parseSch2() {

    uint32_t tmp_value;

    uint8_t data_counter = 0;
    uint32_t block_size;

    // Пока не дошли до конца секции, считываем данные
    while (scheme_file_.tellg() < sections_stack_.back().start_pos + sections_stack_.back().sect_size) {
        scheme_file_.get(byte_);
        // Если нашли флаг блока, открываем его
        if ((static_cast<uint8_t>(byte_) & scheme_flags_.block_flag) == scheme_flags_.block_flag) {
            // Получаем размер блока
            block_size = getBlockSize();
            ++data_counter;

            switch (data_counter) {
                case sch2_data_.window_size_X_flag:
                    getSomeInt(scheme_file_, tmp_value, block_size);
                    lae::writeLog(logs_file_, "window_size_X: ");
                    lae::writeLog(logs_file_, tmp_value, true);
                    break;
                case sch2_data_.window_size_Y_flag:
                    getSomeInt(scheme_file_, tmp_value, block_size);
                    lae::writeLog(logs_file_, "window_size_Y: ");
                    lae::writeLog(logs_file_, tmp_value, true);
                    break;
                case sch2_data_.tmpbool_flag:
                    scheme_file_.get(byte_);
                    tmp_value = byte_;
                    if (tmp_value == 0) {
                        data_counter += 2;
                    }
                    break;
                case sch2_data_.MS_size_flag:
                    getSomeInt(scheme_file_, tmp_value, block_size);
                    lae::writeLog(logs_file_, "MS_size: ");
                    lae::writeLog(logs_file_, tmp_value, true);
                    break;
                case sch2_data_.back_bitmap_info_flag:
                    getSomeInt(scheme_file_, tmp_value, block_size);
                    lae::writeLog(logs_file_, "back_bitmap_info: ");
                    lae::writeLog(logs_file_, tmp_value, true);
                    break;
                case sch2_data_.pixels_per_inch_X_flag:
                    getSomeInt(scheme_file_, tmp_value, block_size);
                    lae::writeLog(logs_file_, "pixels_per_inch_X: ");
                    lae::writeLog(logs_file_, tmp_value, true);
                    break;
                case sch2_data_.pixels_per_inch_Y_flag:
                    getSomeInt(scheme_file_, tmp_value, block_size);
                    lae::writeLog(logs_file_, "pixels_per_inch_Y: ");
                    lae::writeLog(logs_file_, tmp_value, true);
                    break;

            }
        } else if (byte_ == scheme_flags_.section_flag)
            enterSection();
    }
}

void SchemeSectionsParser::parseFont() {
    ;
}


void SchemeSectionsParser::parseDefault() {
    // Пока не дошли до конца секции, считываем данные
    while (scheme_file_.tellg() < sections_stack_.back().start_pos + sections_stack_.back().sect_size) {
        scheme_file_.get(byte_);

        uint32_t block_size;
        // Если нашли флаг блока, открываем его
        if ((static_cast<uint8_t>(byte_) & scheme_flags_.block_flag) == scheme_flags_.block_flag) {
            // Получаем размер блока
            block_size = getBlockSize();

            printBlockData(block_size);

        } else if (byte_ == scheme_flags_.section_flag)
            enterSection();
    }
}

void SchemeSectionsParser::parseCashObject() {

    uint32_t block_size;

    if (sections_stack_.back().sect_name != "1")
        parseDefault();
    else {
        scheme_file_.get(byte_);
        // Получаем размер блока
        block_size = getBlockSize();
        uint32_t cache_size;
        getSomeInt(scheme_file_, cache_size);

        scheme_file_.get(byte_);
        // Получаем размер блока
        block_size = getBlockSize();

        int32_t cache_index = std::stoi(sections_stack_.back().parrent_sect->sect_name);

        SchemeObjectParser::parse(cache_index, false, 1, true, cache_size);

    }
}

void SchemeSectionsParser::parseObjectInfo() {
    uint32_t block_size;

    scheme_file_.get(byte_);
    block_size = getBlockSize();

    scheme_file_.get(byte_);

    is_object = static_cast<bool>(byte_);

    scheme_file_.get(byte_);
    block_size = getBlockSize();

    getSomeInt(scheme_file_, actual_nesting_level_, block_size);

    scheme_file_.get(byte_);
    block_size = getBlockSize();

    printBlockData(block_size);

    scheme_file_.get(byte_);
    block_size = getBlockSize();

    printBlockData(block_size);

    scheme_file_.get(byte_);
    enterSection();

}

void SchemeSectionsParser::parseObject() {

    uint32_t block_size;

    if (sections_stack_.back().sect_name != "1")
        parseDefault();
    else {

        scheme_file_.get(byte_);
        // Получаем размер блока
        block_size = getBlockSize();
        int32_t lib_index = 0;

        if (block_size == 1) {
            scheme_file_.get(byte_);
            bool tmp_bool = static_cast<bool>(byte_);

            if (tmp_bool) {
                scheme_file_.get(byte_);
                // Получаем размер блока
                block_size = getBlockSize();
                getSomeInt(scheme_file_, lib_index);
            }

            scheme_file_.get(byte_);
            // Получаем размер блока
            block_size = getBlockSize();
        }

        printBlockData(block_size);

        scheme_file_.get(byte_);
        // Получаем размер блока
        block_size = getBlockSize();

        uint32_t actual_cursor_pos = scheme_file_.tellg();

        SchemeObjectParser::parse(lib_index, is_object, actual_nesting_level_);
        actual_nesting_level_ = 1;
        is_object = true;

        scheme_file_.clear();
        scheme_file_.seekg(actual_cursor_pos + block_size);
    }

}


void SchemeSectionsParser::parseSectionData() {
    if (sections_stack_.back().sect_name == "schm")
        parseSchm();
    else if (sections_stack_.back().sect_name == "cach")
        parseCash();
    else if (sections_stack_.back().sect_name == "link")
        parseLink();
    else if (sections_stack_.back().sect_name == "sect")
        parseSect();
    else if (sections_stack_.back().sect_name == "objs")
        parseObjs();
    else if (sections_stack_.back().sect_name == "extd")
        parseExtd();
    else if (sections_stack_.back().sect_name == "sch2")
        parseSch2();
    else if (sections_stack_.back().sect_name == "font")
        parseDefault();
    else if (sections_stack_.size() == 3 and sections_stack_[1].sect_name == "objs")
        parseObjectInfo();
    else if (sections_stack_.size() == 4 and sections_stack_[1].sect_name == "objs")
        parseObject();
    else if (sections_stack_.size() == 4 and sections_stack_[1].sect_name == "cach")
        parseCashObject();
    else
        parseDefault();
}

// Функция чтения блока байтов в схеме
uint32_t SchemeSectionsParser::getBlockSize() {

    int8_t bytes_for_blocksize = 0;
    uint32_t block_size = 0;

    // По признаку блока определяем его размер
    if ((static_cast<uint8_t>(byte_) & scheme_flags_.size_6_bit) == scheme_flags_.size_6_bit) {
        block_size |= (static_cast<uint8_t>(byte_) & 0b00111111);
    } else {
        // Если размер блока не уместился в 6 бит, берём его исходя из нужного признака
        switch (static_cast<uint8_t>(byte_)) {
            case scheme_flags_.size_8_bit:
                bytes_for_blocksize = 1;
                break;
            case scheme_flags_.size_16_bit:
                bytes_for_blocksize = 2;
                break;
            case scheme_flags_.size_32_bit:
                bytes_for_blocksize = 4;
                break;
            default:
                bytes_for_blocksize = 4;
                break;
        }
        getSomeInt(scheme_file_, block_size, bytes_for_blocksize);
    }

    return block_size;
}

// Функция чтения информации из блока
void SchemeSectionsParser::printBlockData(const uint32_t block_size) {

    lae::writeLog(logs_file_, "BLOCK OPENED ");
    lae::writeLog(logs_file_, "block size: ");
    lae::writeLog(logs_file_, block_size, true);

    std::bitset<8> print_byte_;
    uint32_t byte_s_counter = 0;

    while (byte_s_counter < block_size) {
        scheme_file_.get(byte_);
        ++byte_s_counter;

        print_byte_ = byte_;
        lae::writeLog(logs_file_, print_byte_);

        if (byte_s_counter % 4 == 0) {
            lae::writeLog(logs_file_, "\n");
        } else {
            lae::writeLog(logs_file_, ' ');
        }

    }

    lae::writeLog(logs_file_, "BLOCK CLOSED", true);

};