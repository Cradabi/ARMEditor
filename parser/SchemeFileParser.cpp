#include "SchemeFileParser.h"

struct SCHM_ITEM {
    std::string name;
    char type;
};

std::string current_named_section;

char schm_obj_counter = 0;
std::vector<SCHM_ITEM> schm_items{{"Version",                                0},
                                  {"name[1].length",                         2},
                                  {"name[1]",                                1},
                                  {"DBIP[1].length",                         2},
                                  {"DBIP[1]",                                1},
                                  {"DBAlias[1].length",                      2},
                                  {"DBAlias",                                1},
                                  {"width",                                  0},
                                  {"height",                                 0},
                                  {"tmp (none)",                             0},
                                  {"tmp (none)",                             0},
                                  {"WorkScale",                              0},
                                  {"TColorToMColor(TColor(tmp))(BGColor):",  0},
                                  {"TColorToMColor(TColor(tmp))(NetColor):", 0},
                                  {"BitDepth",                               0},
                                  {"Count Of Objects",                       0},
                                  {"WindowsSize.x",                          0},
                                  {"WindowsSize.y",                          0}
};
char cach_obj_counter = 0;
std::vector<SCHM_ITEM> cach_items{{"CacheObject.Count", 0}
};
char link_obj_counter = 0;
std::vector<SCHM_ITEM> link_items{{"Links.Count", 0}
};
char sect_obj_counter = 0;
std::vector<SCHM_ITEM> sect_items{{"NextSectionNumber",         0},
                                  {"tmp1(counter of sections)", 0}
};
char objs_obj_counter = 0;
std::vector<SCHM_ITEM> objs_items{{"Object.Count", 0}
};
char extd_obj_counter = 0;
std::vector<SCHM_ITEM> extd_items{{"FWorkVariable", 0}
};
char sch2_obj_counter = 0;
std::vector<SCHM_ITEM> sch2_items{{"WindowSize.X",                  0},
                                  {"WindowSize.Y",                  0},
                                  {"tmpbool",                       2},
                                  {"MS.SetSize(tmp)",               0},
                                  {"BackBitmap.LoadFromStream(MS)", 0},
                                  {"PixelsPerInchX",                0},
                                  {"PixelsPerInchY",                0}

};

void SchemeFileParser::ReadInfoInBlock(const uint32_t& block_size) {
    if (sections_stack.back().sect_name == "schm") {
        SchemeFile.read(buffer, block_size);
        WriteLog(schm_items[schm_obj_counter].name + ": ");
        if (schm_items[schm_obj_counter].type == 0 ||
            schm_items[schm_obj_counter].type == 2) { //чтение типа 0/2 (число)
            uint32_t block_value = 0;
            for (int32_t i = block_size - 1; i >= 0; --i) {
                block_value |= static_cast<uint8_t>(buffer[i]);
                if (i != 0) {
                    block_value <<= 8;
                }
            }
            if (schm_items[schm_obj_counter].type == 2) { //проверка размера (если = 0, отсутсвует вхождение)
                if (block_value == 0) {
                    schm_obj_counter += 1;
                }
            }
            WriteLog(block_value);
        } else { //чтение типа 1 (строка)
            for (uint32_t i = 0; i < block_size; ++i) {
                WriteLog(buffer[i]);
            }
        }
        WriteLog("\n");
        schm_obj_counter += 1;
    } else if (sections_stack.back().sect_name == "cach") {
        SchemeFile.read(buffer, block_size);
        WriteLog(cach_items[cach_obj_counter].name + ": ");
        if (cach_items[cach_obj_counter].type == 0 ||
            cach_items[cach_obj_counter].type == 2) { //чтение типа 0/2 (число)
            uint32_t block_value = 0;
            for (int32_t i = block_size - 1; i >= 0; --i) {
                block_value |= static_cast<uint8_t>(buffer[i]);
                if (i != 0) {
                    block_value <<= 8;
                }
            }
            if (cach_items[cach_obj_counter].type == 2) { //проверка размера (если = 0, отсутсвует вхождение)
                if (block_value == 0) {
                    cach_obj_counter += 1;
                }
            }
            WriteLog(block_value);
        } else { //чтение типа 1 (строка)
            for (uint32_t i = 0; i < block_size; ++i) {
                WriteLog(buffer[i]);
            }
        }
        WriteLog("\n");
        cach_obj_counter += 1;
    } else if (sections_stack.back().sect_name == "link") {
        SchemeFile.read(buffer, block_size);
        WriteLog(link_items[link_obj_counter].name + ": ");
        if (link_items[link_obj_counter].type == 0 ||
            link_items[link_obj_counter].type == 2) { //чтение типа 0/2 (число)
            uint32_t block_value = 0;
            for (int32_t i = block_size - 1; i >= 0; --i) {
                block_value |= static_cast<uint8_t>(buffer[i]);
                if (i != 0) {
                    block_value <<= 8;
                }
            }
            if (link_items[link_obj_counter].type == 2) { //проверка размера (если = 0, отсутсвует вхождение)
                if (block_value == 0) {
                    link_obj_counter += 1;
                }
            }
            WriteLog(block_value);
        } else { //чтение типа 1 (строка)
            for (uint32_t i = 0; i < block_size; ++i) {
                WriteLog(buffer[i]);
            }
        }
        WriteLog("\n");
        link_obj_counter += 1;
    } else if (sections_stack.back().sect_name == "sect") {
        SchemeFile.read(buffer, block_size);
        WriteLog(sect_items[sect_obj_counter].name + ": ");
        if (sect_items[sect_obj_counter].type == 0 ||
            sect_items[sect_obj_counter].type == 2) { //чтение типа 0/2 (число)
            uint32_t block_value = 0;
            for (int32_t i = block_size - 1; i >= 0; --i) {
                block_value |= static_cast<uint8_t>(buffer[i]);
                if (i != 0) {
                    block_value <<= 8;
                }
            }
            if (sect_items[sect_obj_counter].type == 2) { //проверка размера (если = 0, отсутсвует вхождение)
                if (block_value == 0) {
                    sect_obj_counter += 1;
                }
            }
            WriteLog(block_value);
        } else { //чтение типа 1 (строка)
            for (uint32_t i = 0; i < block_size; ++i) {
                WriteLog(buffer[i]);
            }
        }
        WriteLog("\n");
        sect_obj_counter += 1;
    } else if (sections_stack.back().sect_name == "objs") {
        SchemeFile.read(buffer, block_size);
        WriteLog(objs_items[objs_obj_counter].name + ": ");
        if (objs_items[objs_obj_counter].type == 0 ||
            objs_items[objs_obj_counter].type == 2) { //чтение типа 0/2 (число)
            uint32_t block_value = 0;
            for (int32_t i = block_size - 1; i >= 0; --i) {
                block_value |= static_cast<uint8_t>(buffer[i]);
                if (i != 0) {
                    block_value <<= 8;
                }
            }
            if (objs_items[objs_obj_counter].type == 2) { //проверка размера (если = 0, отсутсвует вхождение)
                if (block_value == 0) {
                    objs_obj_counter += 1;
                }
            }
            WriteLog(block_value);
        } else { //чтение типа 1 (строка)
            for (uint32_t i = 0; i < block_size; ++i) {
                WriteLog(buffer[i]);
            }
        }
        WriteLog("\n");
        objs_obj_counter += 1;
    } else if (sections_stack.back().sect_name ==
               "extd") { //TODO эта секция может вызывать ошибки чтения (нереализованные функции, но нигде не используются)
        SchemeFile.read(buffer, block_size);
        WriteLog(extd_items[extd_obj_counter].name + ": ");
        if (extd_items[extd_obj_counter].type == 0 ||
            extd_items[extd_obj_counter].type == 2) { //чтение типа 0/2 (число)
            uint32_t block_value = 0;
            for (int32_t i = block_size - 1; i >= 0; --i) {
                block_value |= static_cast<uint8_t>(buffer[i]);
                if (i != 0) {
                    block_value <<= 8;
                }
            }
            if (extd_items[extd_obj_counter].type == 2) { //проверка размера (если = 0, отсутсвует вхождение)
                if (block_value == 0) {
                    extd_obj_counter += 1;
                }
            }
            WriteLog(block_value);
        } else { //чтение типа 1 (строка)
            for (uint32_t i = 0; i < block_size; ++i) {
                WriteLog(buffer[i]);
            }
        }
        WriteLog("\n");
        extd_obj_counter += 1;
    } else if (sections_stack.back().sect_name == "sch2") {
        SchemeFile.read(buffer, block_size);
        WriteLog(sch2_items[sch2_obj_counter].name + ": ");
        if (sch2_items[sch2_obj_counter].type == 0 ||
            sch2_items[sch2_obj_counter].type == 2) { //чтение типа 0/2 (число)
            uint32_t block_value = 0;
            for (int32_t i = block_size - 1; i >= 0; --i) {
                block_value |= static_cast<uint8_t>(buffer[i]);
                if (i != 0) {
                    block_value <<= 8;
                }
            }
            if (sch2_items[sch2_obj_counter].type == 2) { //проверка размера (если = 0, отсутсвует вхождение)
                if (block_value == 0) {
                    sch2_obj_counter += 2;
                }
            }
            WriteLog(block_value);
        } else { //чтение типа 1 (строка)
            for (uint32_t i = 0; i < block_size; ++i) {
                WriteLog(buffer[i]);
            }
        }
        WriteLog("\n");
        sch2_obj_counter += 1;
    } else {
        SchemeFile.read(buffer, block_size);
        WriteLog(block_size, true, 15);
    }

    ClearBuffer();

}