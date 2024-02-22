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

    // Структура, хранящая типы данных, используемых в схеме
    struct SchemeDataTypes {
        static constexpr uint8_t dtUnknown = 0x00;      // Неизвестный тип данных, нужен для поиска ошибок

        // Записи фиксированной длины
        static constexpr uint8_t dtInteger = 0x01;       // rtInteger (Целое число)
        static constexpr uint8_t dtFloat = 0x02;         // rtFloat (Вещественное число)
        static constexpr uint8_t dtPoint = 0x03;         // rtPoint (Точка)
        static constexpr uint8_t dtFont = 0x04;          // rtFont (Шрифт)
        static constexpr uint8_t dtByte = 0x05;          // rtByte (Байт)
        static constexpr uint8_t dtRectangle = 0x06;     // rtRect (Прямоугольник)

        // Записи переменной длины
        static constexpr uint8_t dtString = 0x0A;        // rtString (Строка)
        static constexpr uint8_t dtList = 0x1E;          // rtList (Список)
        static constexpr uint8_t dtObject = 0x64;        // rtObject (Объект)
        static constexpr uint8_t dtRecord = 0x65;        // rtRecord (Запись)
        static constexpr uint8_t dtElement = 0x66;       // rtElement (Элемент контейнера)
        static constexpr uint8_t dtLibraryObject = 0x67; // (Библиотечный объект)
        static constexpr uint8_t dtLibrary = 0x96;       // rtLibrary (Библиотека (без сигнатуры))
        static constexpr uint8_t dtBitmap = 0xC8;        // rtBitmap (Bitmap graphic)
        static constexpr uint8_t dtJPEGImage = 0xC9;     // rtJPEG (JPEG graphic)
    };
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
    };

    // Структура параметров секции "schm", содержащая общую информацию о схеме
    struct schm {
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

        double work_scale{0};

        BGRColor bg_color;
        BGRColor net_color;

        bool BitDepth{0};

        int32_t count_of_objects{0};

        int32_t windowsSize_x{0};
        int32_t windowsSize_y{0};
    };

    struct cach {
        int32_t cache_count{0};
    };

    struct link {
        int32_t links_count{0};
    };

    struct sect {
        int32_t next_section_number{0};
        int32_t sect_count{0};
    };

    struct objs {
        int32_t objs_count{0};
        //тут должно лежать что-то для объектов
    };

    struct extd {
        int32_t f_work_variable{0};
    };

    struct sch2{
        int32_t window_size_X{0};
        int32_t window_size_Y{0};
        bool tmpbool{0};
        int32_t MS_size{0};
        int32_t back_bitmap_info{0};
        int32_t pixels_per_inch_X{0};
        int32_t pixels_per_inch_Y{0};

    };

    struct font{
        //тут должно лежать что-то для шрифтов
    };
}