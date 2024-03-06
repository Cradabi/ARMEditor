#include <cinttypes>

#ifdef WIN32    // Подключаем библиотеку, только если компиляция происхоидит в ос windows

#include <windows.h>

#endif

#pragma once    // Сообщаем препроцессору, что данный заголовочный файл может быть подключен только 1 раз

// Пространство имен для структур, содержащих константые выражения, необходимые для парса файла схемы
namespace sce {          // Scheme Const Expressions

    // Структура, хранящая флаги секций и блоков, используемые в схеме
    struct SchemeFlags {
        static constexpr uint8_t section_flag = 0b00000000;      // Признак секции
        static constexpr uint8_t block_flag = 0b10000000;        // Признак блока

        static constexpr uint8_t size_6_bit = 0b11000000;        // Признак блока с длиной 6 бит "1 1 xxxxxx", xxxxxx - размер блока
        static constexpr uint8_t size_8_bit = 0b10000000;        // Признак блока с длиной 8 бит
        static constexpr uint8_t size_16_bit = 0b10000001;       // Признак блока с длиной 16 бит
        static constexpr uint8_t size_32_bit = 0b10000010;       // Признак блока с длиной 32 бит
    };

    // Структура, хранящая флаги типов объектов схем
    struct SchemeObjectsTypes {
        static constexpr uint8_t ptNone = 0;        // Multi
        static constexpr uint8_t ptGoBtn = 1;       // Кнопка перехода
        static constexpr uint8_t ptGoPoint = 2;     // Точка перехода
        static constexpr uint8_t ptGluePoint = 3;   // Контакт
        static constexpr uint8_t ptLine = 4;        // Линия
        static constexpr uint8_t ptText = 5;        // Текст
        static constexpr uint8_t ptPolygon = 6;     // Полигон
        static constexpr uint8_t ptEllipse = 7;     // Эллипс
        static constexpr uint8_t ptRectangle = 8;   // Прямоугольник
        static constexpr uint8_t ptDuga = 9;        // Дуга или сектор, в зависимости от наличия заливки
        static constexpr uint8_t ptTeleupr = 10;    // Объект телеуправления
        static constexpr uint8_t ptTeleizm = 11;    // Объект телеизмерения
        static constexpr uint8_t ptSignal = 12;     // Режимная сигнализация
        static constexpr uint8_t ptPicture = 13;    // Картинка
        static constexpr uint8_t ptShape = 14;      // Градиент
    };

//    // Структура, хранящая типы данных, используемых в схеме
//    struct SchemeDataTypes {
//        static constexpr uint8_t dtUnknown = 0x00;      // Неизвестный тип данных, нужен для поиска ошибок
//
//        // Записи фиксированной длины
//        static constexpr uint8_t dtInteger = 0x01;       // rtInteger (Целое число)
//        static constexpr uint8_t dtFloat = 0x02;         // rtFloat (Вещественное число)
//        static constexpr uint8_t dtPoint = 0x03;         // rtPoint (Точка)
//        static constexpr uint8_t dtFont = 0x04;          // rtFont (Шрифт)
//        static constexpr uint8_t dtByte = 0x05;          // rtByte (Байт)
//        static constexpr uint8_t dtRectangle = 0x06;     // rtRect (Прямоугольник)
//
//        // Записи переменной длины
//        static constexpr uint8_t dtString = 0x0A;        // rtString (Строка)
//        static constexpr uint8_t dtList = 0x1E;          // rtList (Список)
//        static constexpr uint8_t dtObject = 0x64;        // rtObject (Объект)
//        static constexpr uint8_t dtRecord = 0x65;        // rtRecord (Запись)
//        static constexpr uint8_t dtElement = 0x66;       // rtElement (Элемент контейнера)
//        static constexpr uint8_t dtLibraryObject = 0x67; // (Библиотечный объект)
//        static constexpr uint8_t dtLibrary = 0x96;       // rtLibrary (Библиотека (без сигнатуры))
//        static constexpr uint8_t dtBitmap = 0xC8;        // rtBitmap (Bitmap graphic)
//        static constexpr uint8_t dtJPEGImage = 0xC9;     // rtJPEG (JPEG graphic)
//    };
}

// Пространство имен для функций, предназначенных для работы с логами и исключениями
namespace lae {  // Logs And Exceptions
#ifdef WIN32
    // Настройка вывода консоли
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#endif

    // Функция записи в файл логов
    template<typename LogType>
    void WriteLog(std::ofstream& LogsFile, const LogType& report, bool new_string = false) {

        LogsFile << report;

        if (new_string) {
            LogsFile << '\n';
        }
    }

    // Функция вывода логов в консоль
    template<typename LogType>
    void PrintLog(const LogType& report, bool new_string = false, int8_t colour = 15) {
#ifdef WIN32
        // Устанавливаем цвет вывода консоли
        SetConsoleTextAttribute(hConsole, colour);
#endif
        std::cout << report;

        if (new_string) {
            std::cout << '\n';
        }
    }
}

// Пространство имен для структур, содержащих параметры секций схемы
namespace ssp {          // Scheme Sections Params
    // Структура, содержащая в себе информацию о цвете
    struct BGRColor {
        uint8_t blue{0};
        uint8_t green{0};
        uint8_t red{0};
        uint8_t reserved{0};

        // Метод возращающий rgb vector для дальнейшей обработки
        std::vector<uint8_t> make_rgb_vector() {
            std::vector<uint8_t> color(3, 0);
            color[0] = red;
            color[1] = green;
            color[2] = blue;

            return color;
        }

    };

    // Структура параметров секции "schm", содержащая общую информацию о схеме
    struct schm {
        // uint8_t params_amount{18};

        static constexpr uint8_t version_flag{1};   // int32_t version{0};

        static constexpr uint8_t name_length_flag{2};   // int32_t name_length{0};
        static constexpr uint8_t scheme_name_flag{3};   // std::string scheme_name;

        static constexpr uint8_t DBIP_length_flag{4};   // int32_t DBIP_length{0};
        static constexpr uint8_t DBIP_flag{5};          // std::string DBIP;

        static constexpr uint8_t DBAlias_length_flag{6};    // int32_t DBAlias_length{0};
        static constexpr uint8_t DBAlias_flag{7};           // std::string DBAlias;

        static constexpr uint8_t width_flag{8};     // int32_t width{0};
        static constexpr uint8_t height_flag{9};    // int32_t height{0};

        static constexpr uint8_t reserved_1_flag{10};   // int32_t reserved_1{0};
        static constexpr uint8_t reserved_2_flag{11};   // int32_t reserved_2{0};

        static constexpr uint8_t work_scale_flag{12};   // double work_scale{0};

        static constexpr uint8_t bg_color_flag{13};     // BGRColor bg_color;
        static constexpr uint8_t net_color_flag{14};    // BGRColor net_color;

        static constexpr uint8_t BitDepth_flag{15};     // bool BitDepth{false};

        static constexpr uint8_t count_of_objects_flag{16}; // int32_t count_of_objects{0};

        static constexpr uint8_t windowsSize_x_flag{17};    // int32_t windowsSize_x{0};
        static constexpr uint8_t windowsSize_y_flag{18};    // int32_t windowsSize_y{0};
    };

    // Структура параметров секции "cach", содержащая общую информацию о кешэ схемы
    struct cach {
        // uint8_t params_amount{1};

        static constexpr uint8_t cache_count_flag{1};   // int32_t cache_count{0};
    };

    struct link {
        // uint8_t params_amount{1};

        static constexpr uint8_t links_count_flag{1};   // int32_t links_count{0};
    };

    struct sect {
        // uint8_t params_amount{2};

        static constexpr uint8_t next_section_number_flag{1};   // int32_t next_section_number{0};

        static constexpr uint8_t sect_count_flag{2};    // int32_t sect_count{0};
    };

    // Структура параметров секции "objs", содержащая общую информацию об объектах схемы
    struct objs {
        // uint8_t params_amount{1};

        static constexpr uint8_t objs_count_flag{1};    // int32_t objs_count{0};
    };

    struct extd {
        // uint8_t params_amount{1};

        static constexpr uint8_t f_work_variable_flag{1};   // int32_t f_work_variable{0};
    };

    struct sch2 {
        // uint8_t params_amount{7};

        static constexpr uint8_t window_size_X_flag{1};     // int32_t window_size_X{0};
        static constexpr uint8_t window_size_Y_flag{2};     // int32_t window_size_Y{0};

        static constexpr uint8_t tmpbool_flag{3};   // bool tmpbool{0};

        static constexpr uint8_t MS_size_flag{4};   // int32_t MS_size{0};

        static constexpr uint8_t back_bitmap_info_flag{5};  // int32_t back_bitmap_info{0};

        static constexpr uint8_t pixels_per_inch_X_flag{6};     // int32_t pixels_per_inch_X{0};
        static constexpr uint8_t pixels_per_inch_Y_flag{7};     // int32_t pixels_per_inch_Y{0};
    };

    struct font {
        //тут должно лежать что-то для шрифтов
    };
}