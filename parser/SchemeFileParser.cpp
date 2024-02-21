#include "SchemeFileParser.h"

// TODO Придумать как идти по элементам структуры
struct _schm {
    uint8_t params_amount{18};

    int32_t Version{0};

    int32_t name_length{0};
    std::string name;

    int32_t DBIP_length{0};
    std::string DBIP;

    int32_t DBAlias_length{0};
    std::string DBAlias;

    int32_t width{0};
    int32_t height{0};

    int32_t reserved_1{0};
    int32_t reserved_2{0};

    double WorkScale{0};

    struct BGColor {
        uint8_t blue{0};
        uint8_t green{0};
        uint8_t red{0};
        uint8_t reserved{0};
    };

    struct NetColor {
        uint8_t blue{0};
        uint8_t green{0};
        uint8_t red{0};
        uint8_t reserved{0};
    };

    BGColor bg_color;
    NetColor net_color;

    bool BitDepth{0};

    int32_t Count_Of_Objects{0};

    int32_t WindowsSize_x{0};
    int32_t WindowsSize_y{0};
};


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