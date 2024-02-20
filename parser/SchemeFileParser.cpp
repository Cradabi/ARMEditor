#include "SchemeFileParser.h"

//struct SCHM_ITEM {
//    std::string name;
//    char type;
//};
//
//std::string current_named_section;
//
//char schm_obj_counter = 0;
//std::vector<SCHM_ITEM> schm_items{{"Version",                                0},
//                                  {"name[1].length",                         2},
//                                  {"name[1]",                                1},
//                                  {"DBIP[1].length",                         2},
//                                  {"DBIP[1]",                                1},
//                                  {"DBAlias[1].length",                      2},
//                                  {"DBAlias",                                1},
//                                  {"width",                                  0},
//                                  {"height",                                 0},
//                                  {"tmp (none)",                             0},
//                                  {"tmp (none)",                             0},
//                                  {"WorkScale",                              0},
//                                  {"TColorToMColor(TColor(tmp))(BGColor):",  0},
//                                  {"TColorToMColor(TColor(tmp))(NetColor):", 0},
//                                  {"BitDepth",                               0},
//                                  {"Count Of Objects",                       0},
//                                  {"WindowsSize.x",                          0},
//                                  {"WindowsSize.y",                          0}
//};
//char cach_obj_counter = 0;
//std::vector<SCHM_ITEM> cach_items{{"CacheObject.Count", 0}
//};
//char link_obj_counter = 0;
//std::vector<SCHM_ITEM> link_items{{"Links.Count", 0}
//};
//char sect_obj_counter = 0;
//std::vector<SCHM_ITEM> sect_items{{"NextSectionNumber",         0},
//                                  {"tmp1(counter of sections)", 0}
//};
//char objs_obj_counter = 0;
//std::vector<SCHM_ITEM> objs_items{{"Object.Count", 0}
//};
//char extd_obj_counter = 0;
//std::vector<SCHM_ITEM> extd_items{{"FWorkVariable", 0}
//};
//char sch2_obj_counter = 0;
//std::vector<SCHM_ITEM> sch2_items{{"WindowSize.X",                  0},
//                                  {"WindowSize.Y",                  0},
//                                  {"tmpbool",                       2},
//                                  {"MS.SetSize(tmp)",               0},
//                                  {"BackBitmap.LoadFromStream(MS)", 0},
//                                  {"PixelsPerInchX",                0},
//                                  {"PixelsPerInchY",                0}
//
//};

void SchemeFileParser::ParseBlockData(const uint32_t& block_size) {

    // TODO при работе раскомментировать

    //    uint32_t bytes_counter = 0;
    //    while (bytes_counter < block_size) {
    //
    //        // Информация в байте начинается с типа данных группы байтов (первый байт группы байтов в блоке)
    //        ++bytes_counter;
    //        SchemeFile.get(byte);
    //        if (static_cast<uint8_t>(byte) == data_types.dtInteger) { // К примеру, если интеджер
    //
    //            // Далее идет кол-во параметров схемы/объекта этого типа данных, если = 0, значит ничего не будет
    //            // если >2 (3 и более) значит что-то пошло не так, нужно смотреть
    //            ++bytes_counter;
    //            SchemeFile.get(byte);
    //            uint8_t tmp_params_amount = static_cast<uint8_t>(byte);
    //        }
    //    }

    UpdateBuffer(block_size);            // TODO при работе закомментировать
    SchemeFile.read(buffer, block_size);    // TODO при работе закомментировать
    ClearBuffer();
}