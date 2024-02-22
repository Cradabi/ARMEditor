#include "SchemeFileParser.h"




// TODO Переписать в структуры
//struct SCHM_ITEM {
//    std::string name;
//    char type;
//};
//
//std::string current_named_section;
//
//
//char cach_obj_counter = 0;
//std::vector<SCHM_ITEM> cach_items{{"CacheObject.Count", 0}
//};
//
//char link_obj_counter = 0;
//std::vector<SCHM_ITEM> link_items{{"Links.Count", 0}
//};
//
//char sect_obj_counter = 0;
//std::vector<SCHM_ITEM> sect_items{{"NextSectionNumber",         0},
//                                  {"tmp1(counter of sections)", 0}
//};
//
//char objs_obj_counter = 0;
//std::vector<SCHM_ITEM> objs_items{{"Object.Count", 0}
//};
//
//char extd_obj_counter = 0;
//std::vector<SCHM_ITEM> extd_items{{"FWorkVariable", 0}
//};
//
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

}

void SchemeFileParser::ParseSCHM(){
    _schm schm_params;

    // TODO Переделать всё на...

}